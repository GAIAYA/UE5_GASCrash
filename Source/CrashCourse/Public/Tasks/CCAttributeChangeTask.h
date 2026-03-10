// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AttributeSet.h"
#include "CCAttributeChangeTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);


struct FOnAttributeChangeData;


/**
 * 属性修改的异步广播任务，传入需要被监听的属性和ASC
 * 激活监听属性能力时调用ListenForAttributeChange生成一个实例广播属性的改变，当能力失效时使用EndTask析构该异步监听实例
 * 也即该实例生命周期跟GameplayAbility声明周期一致
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))// 使该类的实例能够输出（默认蓝图是隐藏该类的实例）
class CRASHCOURSE_API UCCAttributeChangeTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChangedDelegate;

	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	FGameplayAttribute ListenAttribute;// 被监听的属性
	
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UCCAttributeChangeTask* ListenForAttributeChange(UAbilitySystemComponent* ASC, FGameplayAttribute Attribute);

	UFUNCTION(BlueprintCallable)
	void EndTask();

	//UFUNCTION()
	void OnAttributeChanged(const FOnAttributeChangeData& Data);
};
