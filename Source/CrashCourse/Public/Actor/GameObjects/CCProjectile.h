// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Actor/CCGameplayEffect.h"
#include "CCProjectile.generated.h"

class UProjectileMovementComponent;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACCProjectile : public ACCGameplayEffect
{
	GENERATED_BODY()

public:
	ACCProjectile();
	/**
	 * @brief 当该Actor与其他Actor重叠时会触发
	 * @param OtherActor 重叠的对象
	 */
	UFUNCTION(BlueprintCallable, Category = "CC|Projectile")
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION(BlueprintImplementableEvent, Category = "CC|Projectile")
	void SpawnImpactEffects();// 生成爆炸Practical特效
public:
	// 可以在GameplayEffect中把修改类型修改成SetByCaller并绑定一个Tag，可以通过GameplayEffectSpec来设置具体大小（SetSetByCallerMagnitude）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CC|Projectile", meta = (ExposeOnSpawn, ClampMin = "0.0"))
	float Damage{ 20.f };//  ExposeOnSpawn：蓝图中通过Spawn Actor节点创建该Actor时，允许直接设置该变量的初始值
protected:
	UPROPERTY(EditAnywhere, Category = "CC|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileComponent;
	UPROPERTY(EditAnywhere, Category = "CC|Projectile")
	TSubclassOf<UGameplayEffect> ProjectileEffectClass;
};
