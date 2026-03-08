// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CCGameplayAbility.h"
#include "CCHitReact.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCHitReact : public UCCGameplayAbility
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "CC|Abilities")
	FVector AvatarForward;// 当前avataractor的forward向量，单位向量
	UPROPERTY(BlueprintReadWrite, Category = "CC|Abilities")
	FVector ToInstigator;// 当前avataractor朝向instigator的向量，单位向量

public:
	UFUNCTION(BlueprintCallable, Category = "CC|Abilities")
	void CacheHitDirectionVectors(AActor* instigator);


};
