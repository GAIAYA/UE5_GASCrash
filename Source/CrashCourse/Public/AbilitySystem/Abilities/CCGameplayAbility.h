// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CCGameplayAbility.generated.h"

/**
 * 可以认为角色和AI所有的行为都是能力赋予的，能力通过Tag激活:ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer())
 */
UCLASS()
class CRASHCOURSE_API UCCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	// 重写UGameplayAbility类中ActivateAbility函数，自定义想要触发的事情
	//virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	//	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CC|Debug")
	bool bDrawDebug = false;// 控制蓝图子类是否显示调试信息

public:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "CC|Abilities")
	virtual TArray<AActor*> HitBoxOverlapText() { return {}; };

	UFUNCTION(BlueprintCallable, Category = "CC|Abilities")
	virtual void SendHitRectEventToActors(const TArray<AActor*>& actors) {}

};
