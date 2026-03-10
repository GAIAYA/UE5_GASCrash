// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

//#define CCTAG_PRIMARY CCTags::Abilities::Primary
namespace CCTags
{
	namespace Abilities
	{
		// Declares a native gameplay tag that is defined in a cpp with UE_DEFINE_GAMEPLAY_TAG to allow other modules or code to use the created tag variable.
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death)

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tertiary)
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact)
		}
	}
	namespace Events
	{
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(KillScored)
		}
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact)
		}
	}
	namespace Status
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death)
	}
}

