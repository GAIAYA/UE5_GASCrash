// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CCAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(BlueprintCallable, Category = "CC|Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> abilityClass, int32 level);// 通过Class找到对应的能力并设置Level
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> abilityClass, int32 level = 1);// 通过Class找到对应的能力并设置Level
private:
	void HandlAutoActivatedAbility(const FGameplayAbilitySpec& abilitySpec);
};
