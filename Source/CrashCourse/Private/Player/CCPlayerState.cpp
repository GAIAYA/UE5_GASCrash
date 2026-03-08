// Copyright Gaia


#include "Player/CCPlayerState.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"
#include "AbilitySystem/CCAttributeSet.h"

ACCPlayerState::ACCPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UCCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UCCAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ACCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
