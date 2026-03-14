// Copyright Gaia


#include "AbilitySystem/Abilities/Enemy/CCSearchForTarget.h"
#include "Characters/CCEnemyCharacter.h"
#include "AI/CCAIController.h"
#include "Utils/CCBlueprintLibrary.h"
#include "GameplayTags/CCGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Navigation/PathFollowingComponent.h"
#include "AbilitySystemComponent.h"

UCCSearchForTarget::UCCSearchForTarget()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	SetAssetTags(FGameplayTag(CCTags::Abilities::ActivateOnGiven).GetSingleTagContainer());
	//AbilityTags.AddTag(FGameplayTag(CCTags::Abilities::ActivateOnGiven));
}

void UCCSearchForTarget::InitProperties()
{// 初始化数据（需要外部确保使用该能力的一定继承自ACCEnemyCharacter，且Controller继承自ACCAIController，否则会宕机）
	OwningActor = Cast<ACCEnemyCharacter>(GetAvatarActorFromActorInfo());
	if (OwningActor.IsValid())
	{
		AIController = Cast<ACCAIController>(OwningActor->GetController<AAIController>());
		if (!AIController.IsValid())
		{
			CurrentState = EEnemyState::Initializing;
			WaitDelay(0.5f);
		}
		else
		{
			// 监听攻击结束发出的事件
			// UAbilityTask_WaitGameplayEvent必须传入GameplayAbility（也即跟GameplayAbility绑定）
			// 有一个跟Actor的AbilitySystemComponent绑定的UAbilityAsync_WaitGameplayEvent（这个需要新建一个子类，不然无法调用Active函数）
			if (!WaitEndAttackTask.IsValid())
			{
				UAbilityTask_WaitGameplayEvent* Task = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag(CCTags::Events::Enemy::EndAttack));
				Task->EventReceived.AddUniqueDynamic(this, &UCCSearchForTarget::OnGameplayEventReceived);
				Task->ReadyForActivation();
			}
			// FAIRequestID, RequestID, EPathFollowingResult::Type, Result
			AIController->ReceiveMoveCompleted.AddUniqueDynamic(this, &UCCSearchForTarget::OnMoveCompleted);
			CurrentState = EEnemyState::Searching;
			//WaitDelay(OwningActor->GetRandomAttackDelay());
			OnWaitDelayCompleted();// 成功时不用wait，直接发起
		}
	}
}

void UCCSearchForTarget::SearchTarget()
{// 寻找最近Player
	if (!OwningActor.IsValid() || !AIController.IsValid())
	{
		CurrentState = EEnemyState::Initializing;
		WaitDelay(0.5f);
		return;
	}
	if (!OwningActor->IsAlive())
	{
		CurrentState = EEnemyState::Searching;
		WaitDelay(OwningActor->GetRandomAttackDelay());
		return;
	}
	FClosestActorForTagResult searchResult = UCCBlueprintLibrary::FindColsestActorByTag(this, OwningActor->GetActorLocation(), UCCBlueprintLibrary::GetCCActorTagPlayer());
	if (!searchResult.Actor.IsValid())
	{
		CurrentState = EEnemyState::Searching;
		WaitDelay(OwningActor->GetRandomAttackDelay());
		return;
	}
	SearchTargetActor = Cast<ACCBaseCharacter>(searchResult.Actor);
	CurrentState = EEnemyState::Moving;
	//WaitDelay(OwningActor->GetRandomAttackDelay());
	OnWaitDelayCompleted();// 成功时不用wait，直接发起
}

void UCCSearchForTarget::MoveToTarget()
{// 移向Player
	if (!OwningActor.IsValid() || !AIController.IsValid())
	{
		CurrentState = EEnemyState::Initializing;
		WaitDelay(0.5f);
		return;
	}
	if (!SearchTargetActor.IsValid())
	{
		CurrentState = EEnemyState::Searching;
		WaitDelay(OwningActor->GetRandomAttackDelay());
		return;
	}

	// 敌人转向朝向Player在蓝图中实现了，或者可以通过#include "Components/TimelineComponent.h"中UTimelineComponent实现

	// 	AIMODULE_API EPathFollowingRequestResult::Type MoveToActor(AActor* Goal, float AcceptanceRadius = -1, bool bStopOnOverlap = true,
	// bool bUsePathfinding = true, bool bCanStrafe = true,
	// TSubclassOf<UNavigationQueryFilter> FilterClass = NULL, bool bAllowPartialPath = true);
	AIController->MoveToActor(SearchTargetActor.Get(), OwningActor->AcceptanceRadius);
}

void UCCSearchForTarget::ReadyAttack()
{// 尝试发起攻击能力
	if (!OwningActor.IsValid() || !OwningActor->IsAlive())
	{
		CurrentState = EEnemyState::Searching;
		WaitDelay(OwningActor->GetRandomAttackDelay());
		return;
	}
	FGameplayTag tag = CCTags::Abilities::Enemy::Attack;
	GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(tag.GetSingleTagContainer());
}

void UCCSearchForTarget::OnMoveCompleted(FAIRequestID id, EPathFollowingResult::Type type)
{// 成功移动则发起攻击
	if (type == EPathFollowingResult::Type::Success)
	{
		OwningActor->RotateToTarget(SearchTargetActor.Get());
		CurrentState = EEnemyState::ReadyAttacking;
		//WaitDelay(OwningActor->GetRandomAttackDelay());
		OnWaitDelayCompleted();// 成功时不用wait，直接发起
	}
	else
	{
		CurrentState = EEnemyState::Searching;
		WaitDelay(OwningActor->GetRandomAttackDelay());
	}
}

void UCCSearchForTarget::OnWaitDelayCompleted()
{
	switch (CurrentState)
	{
	case EEnemyState::Initializing:
	{
		InitProperties();
		break;
	}
	case EEnemyState::Searching:
	{
		SearchTarget();
		break;
	}
	case EEnemyState::Moving:
	{
		MoveToTarget();
		break;
	}
	case EEnemyState::ReadyAttacking:
	{
		ReadyAttack();
		break;
	}
	default:
	{
		break;
	}
	}
}

void UCCSearchForTarget::OnGameplayEventReceived(FGameplayEventData Payload)
{
	CurrentState = EEnemyState::Searching;
	SearchTarget();
}

void UCCSearchForTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	InitProperties();
}

void UCCSearchForTarget::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	//if (AIController.IsValid())
	//{
	//	AIController->ReceiveMoveCompleted.RemoveDynamic(this, &UCCSearchForTarget::OnMoveCompleted);
	//	// 停止当前移动
	//	AIController->StopMovement();
	//}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	// 这里可以不用手动调用WaitGameplayEvent的EndTask，GameplayAbility结束时会自动销毁，除非想提前销毁Task，那就调用EndTask
	//if (WaitEndAttackTask.IsValid())
	//{
	//	WaitEndAttackTask->EndTask();
	//}
}

void UCCSearchForTarget::WaitDelay(float time)
{
	UAbilityTask_WaitDelay* delay = UAbilityTask_WaitDelay::WaitDelay(this, time);
	delay->OnFinish.AddUniqueDynamic(this, &UCCSearchForTarget::OnWaitDelayCompleted);
	delay->Activate();
}
