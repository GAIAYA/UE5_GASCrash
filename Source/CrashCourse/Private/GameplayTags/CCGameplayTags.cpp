// Copyright Gaia


#include "GameplayTags/CCGameplayTags.h"

/*
* .h使用extern声明.cpp定义
* 访问方式示例：CCTags::Abilities::Primary
* 类型为FNativeGameplayTag，内部实现可以直接转换成FGameplayTag使用
* 可以通过FGameplayTag.GetSingleTagContainer()可以拿到一个FGameplayTagContainer，可以用于激活能力
* 
*/
namespace CCTags
{
	namespace Abilities
	{
		// Defines a native gameplay tag with a comment that is externally declared in a header to allow other modules or code to use the created tag variable.
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, TEXT("CCTags.Abilities.ActivateOnGiven"), "给予时激活标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, TEXT("CCTags.Abilities.Death"), "死亡能力标签")

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, TEXT("CCTags.Abilities.Primary"), "第一能力标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, TEXT("CCTags.Abilities.Secondary"), "第二能力标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, TEXT("CCTags.Abilities.Tertiary"), "第三能力标签")
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, TEXT("CCTags.Abilities.Enemy.HitReact"), "敌人受击标签")
		}
	}
	namespace Events
	{
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, TEXT("CCTags.Events.Player.Primary"), "第一能力AnimNofity通知事件标签")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, TEXT("CCTags.Events.Player.KillScored"), "得分通知事件标签")
		}
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, TEXT("CCTags.Events.Enemy.HitReact"), "敌人受击AnimNofity通知事件标签")
		}
	}
	namespace Status
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, TEXT("CCTags.Status.Death"), "死亡状态标签")
	}
}
