// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CCGameplayAbility.h"
#include "CCPrimary.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCPrimary : public UCCGameplayAbility
{
	GENERATED_BODY()
	
public:
	// 对于虚函数，如果基类写了UFUNCTION(...)，则子类不能再声明UFUNCTION
	virtual TArray<AActor*> HitBoxOverlapText() override;
	void SendHitRectEventToActors(const TArray<AActor*>& actors) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Abilities")
	float AbilityLevel = 1.f;

private:
	UPROPERTY(EditDefaultsOnly, Category = "CC|Abilities")
	float HitBoxRadius = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "CC|Abilities")
	float HitBoxForwardOffset = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "CC|Abilities")
	float HitBoxElevationOffset = 20.f;


private:
	void DrawDebugHitBoxOverlap(const TArray<FOverlapResult>& overlaps, const FVector& hitBoxCenter);
};
