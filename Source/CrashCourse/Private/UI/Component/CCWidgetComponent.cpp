// Copyright Gaia


#include "UI/Component/CCWidgetComponent.h"
#include "Characters/CCBaseCharacter.h"
#include "AbilitySystem/CCAbilitySystemComponent.h"
#include "AbilitySystem/CCAttributeSet.h"
#include "UI/Widget/CCAttributeWidget.h"
#include "Blueprint/WidgetTree.h"

UCCWidgetComponent::UCCWidgetComponent()
{

}

void UCCWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	// 这里尝试初始化ASC和AS，方便后续拿到属性数值计算结果并传递到UI控件上显示
	if (!InitAbilitySystemData())
	{// 如果初始化失败，那么等待初始化成功的广播
		CCCharacter->OnASCInitializad.AddDynamic(this, &UCCWidgetComponent::OnASCInitialized);
		return;
	}
	OnASCInitialized(AbilitySystemComponent.Get(), AttributeSet.Get());
}


bool UCCWidgetComponent::InitAbilitySystemData()
{
	CCCharacter = Cast<ACCBaseCharacter>(GetOwner());
	if (auto cha = CCCharacter.Get())
	{
		AbilitySystemComponent = Cast<UCCAbilitySystemComponent>(cha->GetAbilitySystemComponent());
		AttributeSet = Cast<UCCAttributeSet>(cha->GetAttributeSet());
	}
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UCCWidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// 如果在InitAbilitySystemData中初始化失败，那么会等待ASC和AS初始化成功后广播消息触发该回调
	// 这里初始化后应该初始化生命值，但是属性此时不一定已经初始化了，如果属性没有初始化，则依旧需要等待属性初始化成功后广播的消息
	AbilitySystemComponent = Cast<UCCAbilitySystemComponent>(ASC);
	AttributeSet = Cast<UCCAttributeSet>(AS);
	if (!AbilitySystemComponent.IsValid() || !AttributeSet.IsValid()) return;

	if (!AttributeSet->bAttributesInitialized)
		AttributeSet->OnAttributesInitializedDelegate.AddDynamic(this, &UCCWidgetComponent::OnAttributesInitialized);
	else
		OnAttributesInitialized();
}

void UCCWidgetComponent::OnAttributesInitialized()
{// 最终所有初始化成功，都会调用到这里
 //这里属性数值已经初始化

	// 遍历蓝图中初始化的属性和控件，FGameplayAttribute匹配上的会绑定到对应属性的修改回调上
	// 一旦对应的属性被修改，则触发回调，从而触发OnAttributeChange，里面又会触发蓝图UI的更新
	UUserWidget* widget = GetUserWidgetObject();
	if (!IsValid(widget)) return;

	for (const auto& pair : AttributesMap)
	{
		BindAttributeWidget(pair, widget);
		widget->WidgetTree->ForEachWidget([this, &pair](UWidget* childWidget) 
			{
				BindAttributeWidget(pair, childWidget);
			});
	}
}

void UCCWidgetComponent::BindAttributeWidget(const TPair<FGameplayAttribute, FGameplayAttribute>& pair, UWidget* inWidget)
{
	UCCAttributeWidget* widget = Cast<UCCAttributeWidget>(inWidget);
	if (!IsValid(widget)) return;
	if (!widget->MatchesAttributes(pair)) return;

	widget->OnAttributeChange(pair, AttributeSet.Get());

	// 绑定到对应属性数值改变的回调上
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Key).AddLambda(
		[this, widget, pair](const FOnAttributeChangeData& Data)
		{
			widget->OnAttributeChange(pair, AttributeSet.Get());
		});
}
