// Copyright Gaia


#include "Characters/CCEnemyCharacter.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"
#include "AbilitySystem/CCAttributeSet.h"

ACCEnemyCharacter::ACCEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UCCAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ACCEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACCEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	OnASCInitializad.Broadcast(AbilitySystemComponent, AttributeSet);
	if (HasAuthority())
	{
		GiveStartupAbilities();
		InitializeAttributes();
	}
}
