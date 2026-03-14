// Copyright Gaia


#include "Anim/AnimNotifyState/CCANMeleeAttack.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/CCEnemyCharacter.h"
#include "Characters/CCPlayerCharacter.h"
#include "Utils/CCBlueprintLibrary.h"
#include "KismetTraceUtils.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags/CCGameplayTags.h"
#include "AbilitySystemComponent.h"

UCCANMeleeAttack::UCCANMeleeAttack()
{

}

void UCCANMeleeAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	MeleeSkeletalMesh = MeshComp;
	if (!MeleeSkeletalMesh.IsValid()) return;
	MeleeActor = Cast<ACCEnemyCharacter>(MeshComp->GetOwner());
	if (!MeleeActor.IsValid() || !MeleeActor->IsAlive()) return;
	TArray<FHitResult> OutHits;
	if (GetTraceMultiHitResults(OutHits))
	{
		SendHitEventToActor(OutHits);
	}
}

bool UCCANMeleeAttack::GetTraceMultiHitResults(TArray<FHitResult>& OutHits)
{
	FTransform tf = MeleeSkeletalMesh->GetSocketTransform(UCCBlueprintLibrary::GetSocketMeleeWeapon_R_Trail_01_R());
	// 假设蓝图中已经设置了这个Socket的X轴是正确的，垂直于武器挥舞（指向武器攻击的方向）
	TraceEnd = tf.GetLocation();
	TraceStart = TraceEnd + tf.GetRotation().GetForwardVector() * TraceOffset;
	/*
	* 	bool SphereTraceMulti(const UObject * WorldContextObject, const FVector Start, const FVector End,
	*	float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>&ActorsToIgnore,
	*	EDrawDebugTrace::Type DrawDebugType, TArray<FHitResult>&OutHits, bool bIgnoreSelf, FLinearColor TraceColor = FLinearColor::Red,
	*	FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 5.0f);
	*/
	TArray<AActor*> ActorsToIgnore{ MeleeActor.Get() };
	//UKismetSystemLibrary::SphereTraceMulti(MeleeActor.Get(), TraceStart, TraceEnd, TraceRadius, ETraceTypeQuery::TraceTypeQuery1, 
	//	false, ActorToIgnore, EDrawDebugTrace::Type::None, OutHits, true);// 碰撞检测

	// SphereTraceMulti这个是给蓝图用的，里面最终调用的是SweepMultiByChannel
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(ActorsToIgnore);
	Params.bTraceComplex = false;
	const bool bHit = MeleeActor->GetWorld()->SweepMultiByChannel(OutHits, TraceStart, TraceEnd, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeSphere(TraceRadius), Params);



	if (bDebugDraw)
	{
		DrawDebugSphereTraceMulti(MeleeActor->GetWorld(), TraceStart, TraceEnd, TraceRadius, EDrawDebugTrace::Type::ForDuration, bHit, OutHits, FLinearColor::Red, FLinearColor::Green, 5.f);
	}
	return bHit;
}

void UCCANMeleeAttack::SendHitEventToActor(const TArray<FHitResult>& OutHits)
{
	for (const auto& hit : OutHits)
	{
		ACCPlayerCharacter* player = Cast<ACCPlayerCharacter>(hit.GetActor());
		if (!IsValid(player) || !player->IsAlive()) continue;
		
		// 这里如果成功检测到了攻击到了玩家，发送一个事件给Melee（自己）
		UAbilitySystemComponent* meleeASC = MeleeActor->GetAbilitySystemComponent();
		if (!meleeASC) break;
		FGameplayEffectContextHandle contextHandle = meleeASC->MakeEffectContext();
		contextHandle.AddHitResult(hit);

		FGameplayEventData payload;// payload里面的ContextHandle能传递HitResult，这样接收到事件的对象可以解析HitResult
		payload.Instigator = MeleeActor.Get();
		payload.Target = player;
		payload.ContextHandle = contextHandle;
		// 蓝图在攻击能力发送了Event:EndAttack，因为是学习，所以杂糅使用
		// 这里发送击中的消息（接收勾选了OnlyTriggerOnce），也即接收一次就会销毁
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeleeActor.Get(), CCTags::Events::Enemy::MeleeTraceHit, payload);
	}
}

