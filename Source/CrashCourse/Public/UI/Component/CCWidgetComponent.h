// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem//CCAttributeSet.h"
#include "CCWidgetComponent.generated.h"


class ACCBaseCharacter;
class UCCAbilitySystemComponent;
//class UCCAttributeSet;

/**
 * 
 */
UCLASS(ClassGroup=(CC), meta=(BlueprintSpawnableComponent))
class CRASHCOURSE_API UCCWidgetComponent : public UWidgetComponent
{
	// meta=(BlueprintSpawnableComponent)表示允许在编辑器中添加该组件，不具备继承性，也就是父类声明了如果该子类也想在蓝图中添加该组件，那么需要显式声明
	// Blueprintable则具备继承性，允许编辑器继承该C++类创建蓝图类
	// ClassGroup=(CC)表示添加组件（AActor蓝图类以及相关子类有添加组件）在哪个分组下

	// 这个类只能包含一个UUserWidget，也即自定义自己想要显示的数据（渲染到3D中）
	// 但是一个UUserWidget里面可以嵌套其他的UUserWidget
	// 或者使用多个UWidgetComponent来控制多个UUserWidget

	// 如果是2DUI-数据交互，可以借助UE插件MVVM（Model-View-ViewModel）实现
	// 也可以通过UI绑定一个继承自UObject的WidgetController，UI负责接收回调广播，WidgetController负责获取数据并广播
	// 针对贴图等加载实现可以通过UDataAsset把GameplayTag映射到资产，然后借助TSoftObjectPtr异步加载
	GENERATED_BODY()

public:
	UCCWidgetComponent();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CC|WidgetComponent")
	TMap<FGameplayAttribute, FGameplayAttribute> AttributesMap;// 蓝图初始化，需要去初始化和更新UI

protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY()
	TWeakObjectPtr<ACCBaseCharacter> CCCharacter;// 拥有这个Component的AActor
	UPROPERTY()
	TWeakObjectPtr<UCCAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TWeakObjectPtr<UCCAttributeSet> AttributeSet;
private:

	bool InitAbilitySystemData();// 初始化类内成员变量
	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);// 接收ASC和AS初始化后的回调
	UFUNCTION()
	void OnAttributesInitialized();

	void BindAttributeWidget(const TPair<FGameplayAttribute, FGameplayAttribute>& pair, UWidget* inWidget);
};
