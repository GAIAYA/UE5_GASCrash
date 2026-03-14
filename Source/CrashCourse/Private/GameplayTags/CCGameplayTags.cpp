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
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Projectile, TEXT("CCTags.SetByCaller.Projectile"), "设置GameEffect中SetByCaller的Tag，能通过EffectHandle修改数值")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Melee, TEXT("CCTags.SetByCaller.Melee"), "设置GameEffect中SetByCaller的Tag，能通过EffectHandle修改数值")
	}
	namespace Abilities
	{
		// Defines a native gameplay tag with a comment that is externally declared in a header to allow other modules or code to use the created tag variable.
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, TEXT("CCTags.Abilities.ActivateOnGiven"), "给予时激活标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, TEXT("CCTags.Abilities.Death"), "死亡能力标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ReBorn, TEXT("CCTags.Abilities.ReBorn"), "重生能力标签")

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, TEXT("CCTags.Abilities.Primary"), "第一能力标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, TEXT("CCTags.Abilities.Secondary"), "第二能力标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, TEXT("CCTags.Abilities.Tertiary"), "第三能力标签")
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, TEXT("CCTags.Abilities.Enemy.HitReact"), "敌人受击标签")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, TEXT("CCTags.Abilities.Enemy.Attack"), "敌人攻击标签")
		}
	}
	namespace Events
	{// tag负责发送事件，具体怎么表现通过把数据设置到FGameplayEventData payload进行传递，payload中contextHandle可以添加很多数据包括HitResult
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, TEXT("CCTags.Events.Player.Primary"), "第一能力AnimNofity通知事件标签")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, TEXT("CCTags.Events.Player.KillScored"), "得分通知事件标签")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, TEXT("CCTags.Events.Player.HitReact"), "玩家受击通知事件标签")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, TEXT("CCTags.Events.Player.Death"), "玩家死亡通知事件标签")
		}
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, TEXT("CCTags.Events.Enemy.HitReact"), "敌人受击AnimNofity通知事件标签")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack, TEXT("CCTags.Events.Enemy.EndAttack"), "敌人攻击结束通知事件标签")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MeleeTraceHit, TEXT("CCTags.Events.Enemy.MeleeTraceHit"), "Melee攻击检测事件")
		}
	}
	namespace Status
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, TEXT("CCTags.Status.Death"), "死亡状态标签")
	}
}
namespace CCSocket
{
	namespace Player
	{

	}
	namespace Enemy
	{
		namespace Melee
		{
			const FName Weapon_R_Trail_01_R(TEXT("FX_Trail_01_R"));
		}
		namespace Ranged
		{

		}
	}
}