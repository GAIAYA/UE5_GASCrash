// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

//#define CCTAG_PRIMARY CCTags::Abilities::Primary
namespace CCTags
{
	namespace SetByCaller
	{// 自由设置GameplayEffect的数值Tag
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Projectile)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Melee)
	}
	namespace Abilities
	{
		// Declares a native gameplay tag that is defined in a cpp with UE_DEFINE_GAMEPLAY_TAG to allow other modules or code to use the created tag variable.
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ReBorn)

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tertiary)
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack)
		}
	}
	namespace Events
	{
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(KillScored)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death)
		}
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(EndAttack)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MeleeTraceHit)
		}
	}
	namespace Status
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death)
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
			extern CRASHCOURSE_API const FName Weapon_R_Trail_01_R;
		}
		namespace Ranged
		{

		}
	}
}