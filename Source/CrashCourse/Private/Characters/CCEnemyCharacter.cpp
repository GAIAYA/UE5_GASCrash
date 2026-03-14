// Copyright Gaia


#include "Characters/CCEnemyCharacter.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"
#include "AbilitySystem/CCAttributeSet.h"
#include "AIController.h"

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

float ACCEnemyCharacter::GetRandomAttackDelay() const
{
	return FMath::RandRange(MinAttackDelay, MinAttackDelay);
}

void ACCEnemyCharacter::Death()
{
	Super::Death();

	AAIController* AiController = GetController<AAIController>();
	if (!IsValid(AiController)) return;

	AiController->StopMovement();
}

void ACCEnemyCharacter::Respawn()
{
	Super::Respawn();


}

void ACCEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	OnASCInitializad.Broadcast(AbilitySystemComponent, AttributeSet);

	if (!HasAuthority()) return;


	GiveStartupAbilities();
	InitializeAttributes();
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCCAttributeSet::GetHealthAttribute()).AddUObject(this, &ACCEnemyCharacter::OnHealthChanged);

}
