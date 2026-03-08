// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "CCPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACCPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ACCPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() { return AttributeSet; }
private:

	UPROPERTY(VisibleAnywhere, Category = "CC|Abilities");
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY();
	TObjectPtr<UAttributeSet> AttributeSet;
};
