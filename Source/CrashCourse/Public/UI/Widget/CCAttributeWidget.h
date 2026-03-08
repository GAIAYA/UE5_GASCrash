// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/CCUserWidget.h"
#include "AttributeSet.h"
#include "CCAttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCAttributeWidget : public UCCUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Attribute")
	FGameplayAttribute Attribute;// 蓝图初始化

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|Attribute")
	FGameplayAttribute MaxAttribute;// 蓝图初始化

public:

	bool MatchesAttributes(const TPair<FGameplayAttribute, FGameplayAttribute>& pair);// 是否与当前控件的属性匹配
	void OnAttributeChange(const TPair<FGameplayAttribute, FGameplayAttribute>& pair, UAttributeSet* AS);// 更新属性成员
	
	UFUNCTION(BlueprintImplementableEvent)
	void BEOnAttributeChange(float value, float maxValue);// 蓝图事件，更新UI
};
