// Copyright Gaia


#include "Actor/GameObjects/CCProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/CCPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayTags/CCGameplayTags.h"
#include "Utils/CCBlueprintLibrary.h"

ACCProjectile::ACCProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	
	bReplicates = true;
}

void ACCProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!IsValid(OtherActor) ||!HasAuthority()) return;

	ACCPlayerCharacter* playerCharacter = Cast<ACCPlayerCharacter>(OtherActor);
	if (!IsValid(playerCharacter) || !playerCharacter->IsAlive()) return;

	UAbilitySystemComponent* playerASC = playerCharacter->GetAbilitySystemComponent();
	if (!playerASC) return;
	
	// 这里需要把Damage数值设置到GameEffect上

	//FGameplayEffectContextHandle context = playerASC->MakeEffectContext();
	//FGameplayEffectSpecHandle specHandle = playerASC->MakeOutgoingSpec(ProjectileEffectClass, 1.f, context);
	//specHandle.Data->SetSetByCallerMagnitude(CCTags::SetByCaller::Projectile, Damage);
	//playerASC->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());

	FGameplayEventData payLoad;
	payLoad.Instigator = /*this*/GetOwner();// 这里的Owner需要在Spwan这个Actor的时候设置上，否则为nullptr
	payLoad.Target = OtherActor;
	UCCBlueprintLibrary::SendDamageEventToPlayer(playerCharacter, ProjectileEffectClass, payLoad, CCTags::SetByCaller::Projectile, Damage);


	SpawnImpactEffects();
	Destroy();
}
