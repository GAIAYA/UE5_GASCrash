// Copyright Gaia


#include "Characters/CCPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Player/CCPlayerState.h"

ACCPlayerCharacter::ACCPlayerCharacter()
{
	UCapsuleComponent* capsuleComp = GetCapsuleComponent();// #include "Components/CapsuleComponent.h"
	capsuleComp->InitCapsuleSize(42.f, 96.f);
	
	// 禁止控制器旋转角色
	bUseControllerRotationYaw = false;// Yaw偏航角
	bUseControllerRotationPitch = false;// Pitch俯仰角
	bUseControllerRotationRoll = false;// Roll翻滚角

	UCharacterMovementComponent* characterMovement = GetCharacterMovement();// #include "GameFramework/CharacterMovementComponent.h"
	characterMovement->bOrientRotationToMovement = true;// 角色朝向移动方向
	characterMovement->RotationRate = FRotator(0.f, 540.f, 0.f);// 角色旋转速率
	characterMovement->JumpZVelocity = 500.f;// 跳跃初速度
	characterMovement->AirControl = 0.35f;// 空中控制能力
	characterMovement->MaxWalkSpeed = 500.f;// 最大行走速度
	characterMovement->MinAnalogWalkSpeed = 20.f;// 最小模拟行走速度
	characterMovement->BrakingDecelerationWalking = 2000.f;// 行走时（不施加加速度）的减速力。这是一个持续的反作用力，它会直接降低速度一个恒定的值。
	characterMovement->BrakingDecelerationFalling = 1500.f;// 下落且未施加加速度时的横向减速度。

	/*
	*	头文件：SceneComponent.h
	*	void SetupAttachment(USceneComponent* InParent, FName InSocketName = NAME_None);
	*	virtual bool AttachToComponent(USceneComponent* InParent, const FAttachmentTransformRules& AttachmentRules, FName InSocketName = NAME_None );
	*	AttachToComponent必须传入附加规则（FAttachmentTransformRules），告诉引擎在附加时如何处理位置、旋转和缩放

	*				SetupAttachment			AttachToComponent
	*	调用时机		仅限构造函数				仅限于运行时
	*	性能消耗		极低						较高
	*	变换规则		不需要					需要提供FAttachmentTransformRules
	*	是否触发事件	否						会触发OnAttachmentChanged等事件
	*	物理状态更新	不涉及					会打断或更新物理模拟状态
	*
	*	常见错误：尽量不要在构造函数中调用AttachToComponent，可能会出问题，更不要出现在运行时调用SetupAttachment。
	*
	*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));// #include "GameFramework/SpringArmComponent.h"
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));// #include "Camera/CameraComponent.h"
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

void ACCPlayerCharacter::PossessedBy(AController* NewController)
{
	// 服务端调用，当角色被控制器控制时
	Super::PossessedBy(NewController);
	SetAbilitySystemComponentInfo();
	// 这里可以不用调用if (HasAuthority())，因为PossessedBy只会在服务端调用，服务端必定是Authority
	GiveStartupAbilities();
	InitializeAttributes();
}

void ACCPlayerCharacter::OnRep_PlayerState()
{
	// 客户端调用，当PlayerState从服务端复制过来时
	Super::OnRep_PlayerState();
	SetAbilitySystemComponentInfo();
}

void ACCPlayerCharacter::SetAbilitySystemComponentInfo()
{
	ACCPlayerState* playerState = Cast<ACCPlayerState>(GetPlayerState());
	if (!IsValid(playerState)) return;

	AbilitySystemComponent = playerState->GetAbilitySystemComponent();
	// 这个函数十分重要
	// 确保关联OwnedActor和AvatarActor，能正确处理数据
	AbilitySystemComponent->InitAbilityActorInfo(playerState, this);
	AttributeSet = playerState->GetAttributeSet();
	OnASCInitializad.Broadcast(AbilitySystemComponent, AttributeSet);
}
