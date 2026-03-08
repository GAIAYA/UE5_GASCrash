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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);// 广播ASC和AS已经初始化的消息
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitializeAttributesSet);// 广播初始属性已经初始化的消息

UCLASS(Abstract)
class CRASHCOURSE_API ACCBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; };
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }

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
};
