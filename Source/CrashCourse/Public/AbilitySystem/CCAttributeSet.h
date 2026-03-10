// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CCAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttributesInitialized);

/**
 * 使用方式：ATTRIBUTE_ACCESSORS(UMyHealthSet, Health)
 * This defines a set of helper functions for accessing and initializing attributes, to avoid having to manually write these functions.
 * It would creates the following functions, for attribute Health
 *
 *	static FGameplayAttribute UMyHealthSet::GetHealthAttribute();
 *	FORCEINLINE float UMyHealthSet::GetHealth() const;
 *	FORCEINLINE void UMyHealthSet::SetHealth(float NewVal);
 *	FORCEINLINE void UMyHealthSet::InitHealth(float NewVal);
 */

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCAttributeSet : public UAttributeSet
{// 对于AttributSet第一步就是定义能够为属性生成基本函数的宏ATTRIBUTE_ACCESSORS
	// 属性类型FGameplayAttributeData
	// 属性复制声明ReplicatedUsing = OnRep_xxxxx，该函数需要带有参数const FGameplayAttributeData& OldValue
	// 在OnRep_xxxx(const FGameplayAttributeData& OldValue)函数中使用宏GAMEPLAYATTRIBUTE_REPNOTIFY注册通知
	// #define GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, OldValue)


	GENERATED_BODY()

public:
	/** Returns properties that are replicated for the lifetime of the actor channel */
	// 对于任何能够被复制的变量（比如下面的Health），都需要重写函数GetLifetimeReplicatedProps
	// 在函数里使用DOREPLIFETIME_CONDITION_NOTIFY等宏确定如何复制变量
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/**
	 *	Called just after a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made.
	 *	Note this is only called during an 'execute'. 
	 *	E.g., a modification to the 'base value' of an attribute. It is not called during an application of a GameplayEffect, such as a 5 ssecond +10 movement speed buff.
	 */
	// 当修改属性中BaseValue的GameplayEffect会调用，执行时调用一次
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data);

public:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttributesInitialized, Category = "CC|Attributes")
	bool bAttributesInitialized = false;// 表示属性数值是否被初始化

	UPROPERTY(BlueprintAssignable)
	FAttributesInitialized OnAttributesInitializedDelegate;
protected:
	// 最好的方式是使用GameplayEffect来初始化这些属性，而不是在构造函数中使用硬编码
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "CC|Attributes")
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "CC|Attributes")
	FGameplayAttributeData Mana;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "CC|Attributes")
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "CC|Attributes")
	FGameplayAttributeData MaxMana;

public:
	ATTRIBUTE_ACCESSORS(UCCAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UCCAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UCCAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UCCAttributeSet, MaxMana)

protected:


public:
	UFUNCTION()
	void OnRep_AttributesInitialized(bool OldValue);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
};
