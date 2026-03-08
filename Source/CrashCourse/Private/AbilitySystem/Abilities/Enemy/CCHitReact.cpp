// Copyright Gaia


#include "AbilitySystem/Abilities/Enemy/CCHitReact.h"

void UCCHitReact::CacheHitDirectionVectors(AActor* instigator)
{// 这里计算两个向量AvatarForward和ToInstigator
	AActor* avatarActor = GetAvatarActorFromActorInfo();
	if (!IsValid(instigator) || !IsValid(avatarActor)) return;

	AvatarForward = avatarActor->GetActorForwardVector();

	const FVector instigatorLoc = instigator->GetActorLocation();
	const FVector avatarLoc = avatarActor->GetActorLocation();

	ToInstigator = (instigatorLoc - avatarLoc).GetSafeNormal();
}
