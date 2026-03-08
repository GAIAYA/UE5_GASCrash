// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CCBlueprintLibrary.generated.h"


UENUM(BlueprintType)// 必须继承uint8才能声明BlueprintType
enum class EHitDirection : uint8
{
	Front,		// 前
	Back,		// 后
	Left,		// 左
	Right,		// 右
};
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static EHitDirection GetHitDirection(const FVector& targetForward, const FVector& toInstigator);
	
	UFUNCTION(BlueprintPure)
	static FName GetHitDirectionName(const EHitDirection& hitDirection);
};
