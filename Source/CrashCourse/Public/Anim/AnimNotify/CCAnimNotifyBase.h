// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTags.h"
#include "CCAnimNotifyBase.generated.h"


/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCAnimNotifyBase : public UAnimNotify
{
	GENERATED_BODY()
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Events")
	FGameplayTag EventTag;// 需要触发的的Event标签
	
};
