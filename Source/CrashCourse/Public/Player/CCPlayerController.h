// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CCPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACCPlayerController();
	
protected:
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "CC|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;// 蓝图设置输入映射上下文

	UPROPERTY(EditDefaultsOnly, Category = "CC|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;// 蓝图设置InputAction，C++绑定函数实现具体操作

	UPROPERTY(EditDefaultsOnly, Category = "CC|Input|Movement")
	TObjectPtr<UInputAction> LookAction;// 蓝图设置InputAction，C++绑定函数实现具体操作

	UPROPERTY(EditDefaultsOnly, Category = "CC|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;// 蓝图设置InputAction，C++绑定函数实现具体操作

	UPROPERTY(EditDefaultsOnly, Category = "CC|Input|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;// 蓝图设置InputAction，C++绑定函数实现具体操作

	UPROPERTY(EditDefaultsOnly, Category = "CC|Input|Abilities")
	TObjectPtr<UInputAction> SecondaryAction;// 蓝图设置InputAction，C++绑定函数实现具体操作

	UPROPERTY(EditDefaultsOnly, Category = "CC|Input|Abilities")
	TObjectPtr<UInputAction> TertiaryAction;// 蓝图设置InputAction，C++绑定函数实现具体操作
private:

	void Jump();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Primary();
	void Secondary();
	void Tertiary();

	void ActivateAbilityByTag(const FGameplayTag& AbilityTag) const;
};
