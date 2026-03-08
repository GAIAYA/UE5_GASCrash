// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Characters/CCBaseCharacter.h"
#include "CCEnemyCharacter.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACCEnemyCharacter : public ACCBaseCharacter
{
	GENERATED_BODY()
	
public:
	ACCEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	virtual void BeginPlay() override;
	
};
