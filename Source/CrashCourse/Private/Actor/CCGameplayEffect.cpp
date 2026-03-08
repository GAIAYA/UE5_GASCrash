// Copyright Gaia


#include "Actor/CCGameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void ACCGameplayEffect::ApplyEffectToTarget(AActor* target, TSubclassOf<UGameplayEffect> gameEffectClass)
{
	if (!IsValid(target) || !IsValid(gameEffectClass)) return;

	if (UAbilitySystemComponent* targetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(target))
	{

		FGameplayEffectContextHandle context = targetAsc->MakeEffectContext();
		context.AddSourceObject(this);
		/** Get an outgoing GameplayEffectSpec that is ready to be applied to other things. */
		// TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle Context
		FGameplayEffectSpecHandle specHandle = targetAsc->MakeOutgoingSpec(gameEffectClass, 1.f, context);
		FActiveGameplayEffectHandle activeHandle = targetAsc->ApplyGameplayEffectSpecToSelf(*(specHandle.Data.Get()));
		ActiveEffectHandlesMap.Add(activeHandle, targetAsc);
	}
}

void ACCGameplayEffect::RemoveEffectFromTarget(AActor* target)
{

}

void ACCGameplayEffect::ApplyEffect(AActor* target)
{

}

void ACCGameplayEffect::RemoveEffect(AActor* target)
{

}
