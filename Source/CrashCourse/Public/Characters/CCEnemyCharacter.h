// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Characters/CCBaseCharacter.h"
#include "CCEnemyCharacter.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACCEnemyCharacter : public ACCBaseCharacter
{
	GENERATED_BODY()
	// 想要AIController中的Move to节点生效，需要在Map中添加导航网格Nav Mesh Bounds Volume
	// 寻敌GA能力中负责执行搜寻Player并发起攻击能力
	// 攻击GA能力中负责执行攻击并发起寻敌能力
public:
	ACCEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure)
	virtual float GetRandomAttackDelay() const;
	virtual void Death() override;
	virtual void Respawn() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CC|AI")
	float AcceptanceRadius = 500.f;// AI距离角色范围

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CC|AI")
	float MinAttackDelay = 0.3f;// AI索敌最小间隔

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CC|AI")
	float MaxAttackDelay = 0.8f;// AI索敌最大间隔
protected:
	virtual void BeginPlay() override;
	
};
