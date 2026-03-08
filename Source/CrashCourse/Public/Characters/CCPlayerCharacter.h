// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "Characters/CCBaseCharacter.h"
#include "CCPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACCPlayerCharacter : public ACCBaseCharacter
{
	GENERATED_BODY()
	
public:
	ACCPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
public:

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

private:
	void SetAbilitySystemComponentInfo();
};
