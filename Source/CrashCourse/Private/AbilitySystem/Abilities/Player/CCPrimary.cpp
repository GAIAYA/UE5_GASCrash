// Copyright Gaia


#include "AbilitySystem/Abilities/Player/CCPrimary.h"
#include "Engine/OverlapResult.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags/CCGameplayTags.h"
#include "Characters/CCEnemyCharacter.h"

TArray<AActor*> UCCPrimary::HitBoxOverlapText()
{
	AActor* avatarActor = GetAvatarActorFromActorInfo();
	if (!IsValid(avatarActor)) return {};
	TArray<AActor*> ignoreActors;
	ignoreActors.Add(avatarActor);// 忽略对自身的碰撞

	// GetWorld()->OverlapMultiByChannel碰撞检测需要七个参数（如下）
	// 对于碰撞检测发生在通过控制器触发CCPrimary能力后，触发蒙太奇动画，在动画中某几帧，例如攻击动画的最远处的几帧发送GameplayNotify通知
	// GameplayNotify通知中使用UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(AActor * Actor, FGameplayTag EventTag, FGameplayEventData Payload)
	// 通过GameplayTag来传播Event
	// 在UAbilityTask_WaitGameplayEvent::WaitGameplayEvent中编写接受回调逻辑

	// 那么该函数HitBoxOverlapText可以用于蓝图节点的WaitGameplayEvent，当Received之后触发该函数进行碰撞检测
	
	// 第一个参数：返回值Array of components found to overlap supplied box
	TArray<FOverlapResult> outOverlaps;
	// 第二个参数：碰撞形状的中心Location of center of shape to test against the world
	FVector pos = avatarActor->GetActorLocation() + FVector(0.f, 0.f, HitBoxElevationOffset) + avatarActor->GetActorForwardVector() * HitBoxForwardOffset;
	// 第三个参数：碰撞形状的旋转四元数
	//FQuat rot = FQuat::Identity;
	
	// 第四个参数：碰撞检测通道
	// ECollisionChannel::ECC_Visibility

	// 第五个参数：碰撞形状 FCollisionShape
	// FCollisionShape::MakeSphere(HitBoxRadius)
	
	// 第六个参数：额外的碰撞配置参数FCollisionQueryParams
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActors(ignoreActors);
	//queryParams.

	// 第七个参数：碰撞来源的参数配置（即将被碰撞的检测物体）
	// 只碰撞响应ECC_Pawn中的ECR_Block，一种优化，仅限于C++，蓝图不支持
	FCollisionResponseParams responseParams;
	responseParams.CollisionResponse.SetAllChannels(ECollisionResponse::ECR_Ignore);// 关闭所有的碰撞
	responseParams.CollisionResponse.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);// 仅开启ECC_Pawn的Block
	/**
	 *  Test the collision of a shape at the supplied location using a specific channel, and determine the set of components that it overlaps
	 *  @param  OutOverlaps     Array of components found to overlap supplied box
	 *  @param  Pos             Location of center of shape to test against the world
	 *  @param  TraceChannel    The 'channel' that this query is in, used to determine which components to hit
	 *  @param	CollisionShape	CollisionShape - supports Box, Sphere, Capsule
	 *  @param  Params          Additional parameters used for the trace
	 * 	@param 	ResponseParam	ResponseContainer to be used for this trace
	 *  @return TRUE if OutOverlaps contains any blocking results
	 */
	// bool OverlapMultiByChannel(TArray<struct FOverlapResult>&OutOverlaps, const FVector & Pos, const FQuat & Rot, ECollisionChannel TraceChannel, 
	// const FCollisionShape & CollisionShape, const FCollisionQueryParams & Params = FCollisionQueryParams::DefaultQueryParam, 
	// const FCollisionResponseParams & ResponseParam = FCollisionResponseParams::DefaultResponseParam) const;

	GetWorld()->OverlapMultiByChannel(outOverlaps, pos, FQuat::Identity, ECollisionChannel::ECC_Visibility, 
		FCollisionShape::MakeSphere(HitBoxRadius), queryParams, responseParams);

	TArray<AActor*> outActors;
	// 收集返回值
	for (const FOverlapResult& res : outOverlaps)
	{
		if (!IsValid(res.GetActor())) continue;
		if (!Cast<ACCEnemyCharacter>(res.GetActor())) continue;

		outActors.Add(res.GetActor());
	}

	if (bDrawDebug) DrawDebugHitBoxOverlap(outOverlaps, pos);

	return outActors;
}

void UCCPrimary::SendHitRectEventToActors(const TArray<AActor*>& actors)
{
	// 这里发送给被碰撞Actor一个受击GameplayTag，受击能力里会监听这个Tag（WaitGameplayEvent）并做出相应的逻辑
	for (AActor* ac : actors)
	{
		if (!IsValid(ac)) continue;

		FGameplayEventData payLoad;
		payLoad.Instigator = GetAvatarActorFromActorInfo();// 设置发起者
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ac, CCTags::Events::Enemy::HitReact, payLoad);
	}
}

void UCCPrimary::DrawDebugHitBoxOverlap(const TArray<FOverlapResult>& overlaps, const FVector& hitBoxCenter)
{
	DrawDebugSphere(GetWorld(), hitBoxCenter, HitBoxRadius, 16, FColor::White, false, 3.f, 0, 1.f);
	for (const FOverlapResult& res : overlaps)
	{
		UPrimitiveComponent* comp = res.GetComponent();
		if (comp)
		{
			DrawDebugSphere(GetWorld(), comp->GetComponentLocation(), HitBoxRadius * 0.25f, 8, FColor::Red, false, 3.f, 0, 2);
		}
	}
}
