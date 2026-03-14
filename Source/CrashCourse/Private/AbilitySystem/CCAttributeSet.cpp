// Copyright Gaia


#include "AbilitySystem/CCAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags/CCGameplayTags.h"

void UCCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// REPNOTIFY_Always表示该属性如果  被修改之后的值  等于  修改之前的值  也依旧会被通知
	DOREPLIFETIME_CONDITION_NOTIFY(UCCAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UCCAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UCCAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UCCAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)

	DOREPLIFETIME(UCCAttributeSet, bAttributesInitialized)// 确保该成员变量能被Replicated
}

void UCCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() <= 0.f)
	{// 这里可以发送Character死亡委托，然后在各自的角色/敌人死亡委托里面处理应该发送什么事件（经验/道具/货币等）
		FGameplayEventData payLoad;
		payLoad.Instigator = Data.Target.GetAvatarActor();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.EffectSpec.GetContext().GetInstigator(), CCTags::Events::Player::KillScored, payLoad);
	}

	if (!bAttributesInitialized)
	{
		bAttributesInitialized = true;
		OnAttributesInitializedDelegate.Broadcast();
	}
}

void UCCAttributeSet::OnRep_AttributesInitialized(bool OldValue)
{
	if (bAttributesInitialized)
	{
		OnAttributesInitializedDelegate.Broadcast();
	}
}

void UCCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	// This is a helper macro that can be used in RepNotify functions to handle attributes that will be predictively modified by clients.
	// 本地客户端可以预测属性改变，然后服务器验证之后发现如果不对则会回滚
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCCAttributeSet, Health, OldValue)
}

void UCCAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCCAttributeSet, Mana, OldValue)
}

void UCCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCCAttributeSet, MaxHealth, OldValue)
}

void UCCAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCCAttributeSet, MaxMana, OldValue)
}
