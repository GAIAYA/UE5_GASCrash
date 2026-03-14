// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CCGameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "CCSearchForTarget.generated.h"

class ACCBaseCharacter;
class ACCEnemyCharacter;
class ACCAIController;
class UAbilityTask_WaitDelay;
struct FAIRequestID;
struct FGameplayAbilitySpecHandle;
struct FGameplayAbilityActorInfo;
struct FGameplayAbilityActivationInfo;
struct FGameplayEventData;

namespace EPathFollowingResult { enum Type : int; }

UENUM(BlueprintType)
enum EEnemyState : uint8
{// 表示当前敌人正在做什么
	Initializing,
	Searching,
	Moving,
	ReadyAttacking,
};

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCSearchForTarget : public UCCGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCCSearchForTarget();
	UFUNCTION(BlueprintCallable, Category = "CC|Ability")
	void InitProperties();
	UFUNCTION(BlueprintCallable, Category = "CC|Ability")
	void SearchTarget();
	UFUNCTION(BlueprintCallable, Category = "CC|Ability")
	void MoveToTarget();
	UFUNCTION(BlueprintCallable, Category = "CC|Ability")
	void ReadyAttack();
protected:

	UPROPERTY(BlueprintReadOnly, Category = "CC|Ability")
	TWeakObjectPtr<ACCBaseCharacter> SearchTargetActor;

	UPROPERTY(BlueprintReadOnly, Category = "CC|Ability")
	TWeakObjectPtr<ACCEnemyCharacter> OwningActor;

	UPROPERTY(BlueprintReadOnly, Category = "CC|Ability")
	TWeakObjectPtr<ACCAIController> AIController;

	EEnemyState CurrentState = EEnemyState::Initializing;
protected:
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID id, EPathFollowingResult::Type type);
	UFUNCTION()
	void OnWaitDelayCompleted();
	UFUNCTION()
	void OnGameplayEventReceived(FGameplayEventData Payload);
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
private:
	
	void WaitDelay(float time);

	TWeakObjectPtr<UAbilityTask_WaitGameplayEvent> WaitEndAttackTask = nullptr;
};
