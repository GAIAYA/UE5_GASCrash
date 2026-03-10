// Copyright Gaia


#include "Tasks/CCAttributeChangeTask.h"
#include "AbilitySystemComponent.h"

UCCAttributeChangeTask* UCCAttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* ASC, FGameplayAttribute Attribute)
{
	if (!IsValid(ASC)) return nullptr;

	UCCAttributeChangeTask* task = NewObject<UCCAttributeChangeTask>();
	task->AbilitySystemComponent = ASC;
	task->ListenAttribute = Attribute;

	ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(task, &UCCAttributeChangeTask::OnAttributeChanged);

	return task;
}

void UCCAttributeChangeTask::EndTask()
{
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ListenAttribute).RemoveAll(this);
	}
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UCCAttributeChangeTask::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChangedDelegate.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
