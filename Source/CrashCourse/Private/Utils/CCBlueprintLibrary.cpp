// Copyright Gaia


#include "Utils/CCBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/CCPlayerCharacter.h"
#include "GameplayTags/CCGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/CCAttributeSet.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"

EHitDirection UCCBlueprintLibrary::GetHitDirection(const FVector& targetForward, const FVector& toInstigator)
{// 目标向前向量，目标指向发起目标向量
	// 输入向量已经标准化
	const float dot = FVector::DotProduct(targetForward, toInstigator);

	if (dot < -0.5f)
	{
		return EHitDirection::Back;
	}
	if (dot < 0.5f)
	{
		const FVector cross = FVector::CrossProduct(targetForward, toInstigator);
		if (cross.Z > 0.f)
		{// UE是左手坐标系，前 叉乘 右是向上
			return EHitDirection::Right;
		}
		return EHitDirection::Left;
	}
	return EHitDirection::Front;
}

FName UCCBlueprintLibrary::GetHitDirectionName(const EHitDirection& hitDirection)
{
	switch (hitDirection)
	{
	case EHitDirection::Front:
		return FName("Front");
	case EHitDirection::Back:
		return FName("Back");
	case EHitDirection::Left:
		return FName("Left");
	case EHitDirection::Right:
		return FName("Right");
	default:
		return FName("None");
	}
}

FClosestActorForTagResult UCCBlueprintLibrary::FindColsestActorByTag(const UObject* wordContext, const FVector& origin, const FName& tag)
{
	if (!IsValid(wordContext)) return {};

	TArray<AActor*> outAllActors;
	UGameplayStatics::GetAllActorsWithTag(wordContext, tag, outAllActors);
	FClosestActorForTagResult result;

	float dis = TNumericLimits<float>::Max();
	for (const auto actor : outAllActors)
	{
		if (!IsValid(actor)) continue;

		ACCBaseCharacter* baseCharacter = Cast<ACCBaseCharacter>(actor);
		if (!baseCharacter || !baseCharacter->IsAlive()) continue;

		const float tempDis = FVector::Distance(origin, actor->GetActorLocation());
		if (tempDis < dis)
		{
			dis = tempDis;
			result.Actor = actor;
			result.Distance = dis;
		}
	}

	return result;
}

void UCCBlueprintLibrary::SendDamageEventToPlayer(AActor* actor, const TSubclassOf<UGameplayEffect> effectClass, 
	const FGameplayEventData& payLoad, const FGameplayTag& callerMagnitudeTag, const float damage)
{// 传入的damage为正数
	ACCPlayerCharacter* player = Cast<ACCPlayerCharacter>(actor);
	if (!IsValid(player) || !player->IsAlive()) return;
	const UCCAttributeSet* AS = Cast<UCCAttributeSet>(player->GetAttributeSet());
	UAbilitySystemComponent* ASC = player->GetAbilitySystemComponent();
	if (!IsValid(AS) || !IsValid(ASC)) return;
	// 这里apply gameplay effect之前先判断是否死亡，注意顺序
	const bool bDeath = AS->GetHealth() - damage <= 0.f;// 应用了当前伤害之后是否已经死亡

	FGameplayEffectContextHandle contextHandle = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle specHandle = ASC->MakeOutgoingSpec(effectClass, 1.f, contextHandle);
	specHandle.Data->SetSetByCallerMagnitude(callerMagnitudeTag, -damage);
	ASC->ApplyGameplayEffectSpecToSelf(*(specHandle.Data.Get()));

	const FGameplayTag eventTag = bDeath ? CCTags::Events::Player::Death : CCTags::Events::Player::HitReact;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(player, eventTag, payLoad);
}

FName UCCBlueprintLibrary::GetCCActorTagPlayer()
{
	return CCActorTags::Player;
}

FName UCCBlueprintLibrary::GetSocketMeleeWeapon_R_Trail_01_R()
{
	return CCSocket::Enemy::Melee::Weapon_R_Trail_01_R;
}


