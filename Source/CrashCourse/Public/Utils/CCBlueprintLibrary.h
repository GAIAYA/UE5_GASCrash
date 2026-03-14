// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CCBlueprintLibrary.generated.h"

class UGameplayEffect;
struct FGameplayEventData;
struct FGameplayTag;


UENUM(BlueprintType)// 必须继承uint8才能声明BlueprintType
enum class EHitDirection : uint8
{
	Front,		// 前
	Back,		// 后
	Left,		// 左
	Right,		// 右
};

USTRUCT(BlueprintType)
struct FClosestActorForTagResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor;

	UPROPERTY(BlueprintReadWrite)
	float Distance{0.f};
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


	/**
	 * @brief 找到所有包含tag的Actor中离出发点origin最近的Actor
	 * @param wordContext 
	 * @param origin 
	 * @param tag 
	 * @return 
	 */
	UFUNCTION(BlueprintPure)
	static FClosestActorForTagResult FindColsestActorByTag(const UObject* wordContext, const FVector& origin, const FName& tag);


	UFUNCTION(BlueprintPure)
	static void SendDamageEventToPlayer(AActor* actor, const TSubclassOf<UGameplayEffect> effectClass, 
		const FGameplayEventData& payLoad, const FGameplayTag& callerMagnitudeTag, const float damage);



	/* Begin 返回ActorTag */ 
	UFUNCTION(BlueprintPure)
	static FName GetCCActorTagPlayer();
	/* End 返回ActorTag */

	/* Begin 返回SocketName */
	UFUNCTION(BlueprintPure)
	static FName GetSocketMeleeWeapon_R_Trail_01_R();

	/* End 返回SocketName */
};
