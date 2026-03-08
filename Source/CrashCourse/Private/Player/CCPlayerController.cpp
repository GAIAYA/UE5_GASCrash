// Copyright Gaia


#include "Player/CCPlayerController.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/CCPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayTags/CCGameplayTags.h"

ACCPlayerController::ACCPlayerController()
{

}

void ACCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// #include "EnhancedInputSubsystems.h"
	// 有了增强输入Map，需要设置到UEnhancedInputLocalPlayerSubsystem中
	UEnhancedInputLocalPlayerSubsystem* inputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(inputSubSystem)) return;

	for (const auto& mapContext : InputMappingContexts)
	{
		inputSubSystem->AddMappingContext(mapContext, 0);
		
	}
	// #include "EnhancedInputComponent.h"
	// 需要为InputAction绑定函数，根据输入执行对应的操作
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACCPlayerController::Jump);
	enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACCPlayerController::StopJumping);
	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACCPlayerController::Move);
	enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACCPlayerController::Look);
	enhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &ACCPlayerController::Primary);
	enhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Started, this, &ACCPlayerController::Secondary);
	enhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Started, this, &ACCPlayerController::Tertiary);
}

void ACCPlayerController::Jump()
{
	// character自带跳跃的虚函数，可以自行重写实现
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->Jump();
}
void ACCPlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->StopJumping();
}
void ACCPlayerController::Move(const FInputActionValue& Value)
{// 二维坐标系下正X表示右，正Y表示前
//	输入是在二维坐标下，角色移动方向是在三维坐标下，所以计算方向向量方式中X轴表示向前向量
	APawn* pawn = GetPawn();
	if (!IsValid(pawn)) return;

	FVector2D inputVector2D = Value.Get<FVector2D>();
	
	// 找到前后方向向量和左右方向向量
	const FRotator controlRotation = GetControlRotation();
	const FRotator yawRotation = FRotator(0.f, controlRotation.Yaw, 0.f);
	FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);// 这里是三维坐标系下的前面，即x轴
	FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);// 这里是三维坐标系下的右边，即y轴

	pawn->AddMovementInput(forwardDirection, inputVector2D.Y);
	pawn->AddMovementInput(rightDirection, inputVector2D.X);
}
void ACCPlayerController::Look(const FInputActionValue& Value)
{
	// 第三人称下是弹簧臂跟随控制器旋转，这里修改控制器旋转，弹簧臂自动跟随旋转（相机旋转始终相对弹簧臂不变，也即相机不要设置跟随控制器旋转）
	// 第一人称下是设置相机跟随控制器旋转bUsePawnControlRotation
	const FVector2D inputVector2D = Value.Get<FVector2D>();
	AddPitchInput(inputVector2D.Y);
	AddYawInput(inputVector2D.X);
}

void ACCPlayerController::Primary()
{
	// 通过这种方式也可以获取tag
	// FGameplayTag::RequestGameplayTag("CCTags.Abilities.Primary");
	ActivateAbilityByTag(CCTags::Abilities::Primary);
}

void ACCPlayerController::Secondary()
{
	// 通过这种方式也可以获取tag
	// FGameplayTag::RequestGameplayTag("CCTags.Abilities.Secondary");
	ActivateAbilityByTag(CCTags::Abilities::Secondary);
}

void ACCPlayerController::Tertiary()
{
	// 通过这种方式也可以获取tag
	// FGameplayTag::RequestGameplayTag("CCTags.Abilities.Tertiary");
	ActivateAbilityByTag(CCTags::Abilities::Tertiary);
}

void ACCPlayerController::ActivateAbilityByTag(const FGameplayTag& AbilityTag) const
{
	ACCPlayerCharacter* character = Cast<ACCPlayerCharacter>(GetCharacter());
	if (!IsValid(character)) return;
	
	// 这里也可以使用全局静态库获取asc
	// UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetCharacter()/* GetPawn() */);
	UAbilitySystemComponent* asc = character->GetAbilitySystemComponent();
	asc->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}
