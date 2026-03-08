// Copyright Gaia


#include "AbilitySystem/Abilities/CCGameplayAbility.h"

void UCCGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (bDrawDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("%s Activated!"), *GetName()));
	}

}
