// Copyright Gaia


#include "UI/Widget/CCAttributeWidget.h"

bool UCCAttributeWidget::MatchesAttributes(const TPair<FGameplayAttribute, FGameplayAttribute>& pair)
{
	return Attribute == pair.Key && MaxAttribute == pair.Value;
}

void UCCAttributeWidget::OnAttributeChange(const TPair<FGameplayAttribute, FGameplayAttribute>& pair, UAttributeSet* AS)
{
	if (!IsValid(AS)) return;

	Attribute = pair.Key;
	MaxAttribute = pair.Value;

	BEOnAttributeChange(Attribute.GetNumericValue(AS), MaxAttribute.GetNumericValue(AS));
}
