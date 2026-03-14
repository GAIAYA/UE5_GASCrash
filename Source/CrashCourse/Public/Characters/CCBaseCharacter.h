// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CCBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UAttributeSet;
class UGameplayEffect;
struct FOnAttributeChangeData;
class FLifetimeProperty;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);// 广播ASC和AS已经初始化的消息
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitializeAttributesSet);// 广播初始属性已经初始化的消息

namespace CCActorTags
{// 用于攻击时碰撞检测的Tag
	extern CRASHCOURSE_API const FName Player;// 模块名_API宏表示外部模块可以使用这个变量
};

UCLASS(Abstract)
class CRASHCOURSE_API ACCBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; };
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "CC|Character")
	bool IsAlive() const { return bAlive; }
	void SetAlive(bool live) { bAlive = live; }

	void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void Death();
	UFUNCTION(BlueprintCallable, Category = "CC|Character")
	virtual void Respawn();

	UFUNCTION()
	void OnRep_Alive(bool alive);
	UFUNCTION(BlueprintCallable, Category = "CC|Character")
	void ResetAttributes();
	UFUNCTION(BlueprintImplementableEvent, Category = "CC|Character")
	void RotateToTarget(AActor* target);
public:
	//void ActivateStartupAbilities();
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitializad;// ASC和AS被初始化时广播的委托 
protected:
	virtual void BeginPlay() override;
	void GiveStartupAbilities();// 赋予初始能力
	void InitializeAttributes();// 初始化属性

	//UFUNCTION(BlueprintCallable, Category = "CC|WidgetComponent")
	//void InitializeBarWidgetComponent(UWidgetComponent* component) { HealthManaBarWidgetComponent = component; };
protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;// 角色的ASC，敌人在子类构造函数创建并记录，玩家则在playerstate创建，在玩家角色子类记录
	UPROPERTY();
	TObjectPtr<UAttributeSet> AttributeSet;// 角色的属性集，敌人在子类构造函数创建并记录，玩家则在playerstate创建，在玩家角色子类记录
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "CC|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;// 角色拥有的初始化GameplayAbility
	
	UPROPERTY(EditDefaultsOnly, Category = "CC|Effect")
	TSubclassOf<UGameplayEffect> InitializeAttributesClass;// 使用GameplayEffect初始化角色属性

	UPROPERTY(EditDefaultsOnly, Category = "CC|Effect")
	TSubclassOf<UGameplayEffect> ResetAttributesClass;// 使用GameplayEffect重置角色属性

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Alive", meta = (AllowPrivateAccess = "true"))// 允许蓝图访问私有成员
	bool bAlive = true;
};
