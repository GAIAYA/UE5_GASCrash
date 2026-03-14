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
{// 这个是某一帧触发通知，如果想要在某一段攻击动画中通知则使用AnimNotifyState类
	GENERATED_BODY()
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Events")
	FGameplayTag EventTag;// 需要触发的的Event标签
	
};
