// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "ActiveGameplayEffectHandle.h"
#include "CCGameplayEffect.generated.h"

class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectApplyPolicy : uint8
{
	NotApply,
	ApplyInstant,
	ApplyOnOverlap,
	ApplyOnEndOverlap,
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy : uint8
{
	NotRemove,
	RemoveInstant,
	RemoveOnOverlap,
	RemoveOnEndOverlap,
};

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACCGameplayEffect : public AActor
{// 对于GameEffect，有初始化属性的，有来自陷阱Actor，有来自敌人Actor
	// GameplayEffect持续类型分三种：
	// 立刻生效（修改属性的BaseValue和CurrentValue）
	// 持续生效（如果不设置Period的话，仅修改CurrentValue，如果设置了Period，则会修改属性BaseValue和CurrentValue）
	// 永久生效（修改属性BaseValue和CurrentValue）

	// 对于赋予Effect，则根据具体情况决定何时赋予，如何赋予，赋予什么持续类型
	// 因为存在持续和永久，所以会有移除策略，决定何时移除GameplayEffect

	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CC|Effect")
	void ApplyEffectToTarget(AActor* target, TSubclassOf<UGameplayEffect> gameEffectClass);
	UFUNCTION(BlueprintCallable, Category = "CC|Effect")
	void RemoveEffectFromTarget(AActor* target);
	
	UFUNCTION(BlueprintCallable, Category = "CC|Effect")
	void ApplyEffect(AActor* target);
	
	UFUNCTION(BlueprintCallable, Category = "CC|Effect")
	void RemoveEffect(AActor* target);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Effect")
	EEffectApplyPolicy InstantApplyPolicy = EEffectApplyPolicy::NotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Effect")
	EEffectApplyPolicy DurationApplyPolicy = EEffectApplyPolicy::NotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Effect")
	EEffectRemovePolicy DurationRemovePolicy = EEffectRemovePolicy::NotRemove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Effect")
	EEffectApplyPolicy InfiniteApplyPolicy = EEffectApplyPolicy::NotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Effect")
	EEffectRemovePolicy InfiniteRemovePolicy = EEffectRemovePolicy::NotRemove;

private:

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandlesMap;
};
