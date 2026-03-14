// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Anim/AnimNotifyState/CCAnimNotifyStateBase.h"
#include "CCANMeleeAttack.generated.h"


class USkeletalMeshComponent;
class UAnimSequenceBase;
class ACCEnemyCharacter;
//enum ECollisionChannel;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCANMeleeAttack : public UCCAnimNotifyStateBase
{
	GENERATED_BODY()
	
public:
	UCCANMeleeAttack();
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
		float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "CC|Melee")
	TWeakObjectPtr<ACCEnemyCharacter> MeleeActor;
	UPROPERTY(BlueprintReadOnly, Category = "CC|Melee")
	TWeakObjectPtr<USkeletalMeshComponent> MeleeSkeletalMesh;
	UPROPERTY(BlueprintReadOnly, Category = "CC|Melee")
	FVector TraceStart;// SweepMultiByChannel检测起点
	UPROPERTY(BlueprintReadOnly, Category = "CC|Melee")
	FVector TraceEnd;// SweepMultiByChannel检测终点
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Melee")
	float TraceRadius = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Melee")
	float TraceOffset = -25.f;// 扫描的起点和终点之间的距离

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Melee")
	bool bDebugDraw = false;

private:
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility;// 可见碰撞通道

private:
	bool GetTraceMultiHitResults(TArray<FHitResult>& OutHits);// 碰撞检测
	void SendHitEventToActor(const TArray<FHitResult>& OutHits);
};
