// Copyright Gaia


#include "Characters/CCBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "UI/Component/CCWidgetComponent.h"
#include "AbilitySystem/CCAttributeSet.h"
#include "Net/UnrealNetwork.h"

ACCBaseCharacter::ACCBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	/*
	* 无论该网格体是否在屏幕上可见，引擎都会始终计算它的动画姿势（Tick Pose）并刷新所有骨骼的变换矩阵
	*/
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void ACCBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACCBaseCharacter, bAlive);
}

void ACCBaseCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{// 这个回调绑定在Health属性修改上，所以当Health属性被修改时广播，会触发该回调
	if (Data.NewValue <= 0.f)
	{
		Death();
	}
}

void ACCBaseCharacter::Death()
{
	bAlive = false;
}

void ACCBaseCharacter::Respawn()
{
	bAlive = true; 
}

void ACCBaseCharacter::OnRep_Alive(bool alive)
{

}

void ACCBaseCharacter::ResetAttributes()
{
	if (!HasAuthority() || !IsValid(ResetAttributesClass)) return;

	FGameplayEffectContextHandle context = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle specHandle = AbilitySystemComponent->MakeOutgoingSpec(ResetAttributesClass, 1.f, context);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());
}

//void ACCBaseCharacter::ActivateStartupAbilities()
//{
//	if (!IsValid(AbilitySystemComponent)) return;
//	for (const auto& sa : StartupAbilities)
//	{
//		AbilitySystemComponent->TryActivateAbilityByClass(sa);
//	}
//}

void ACCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCBaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(AbilitySystemComponent) || !HasAuthority()) return;// 必须是Authority端才能给予能力
	for (const auto& sa : StartupAbilities)
	{
		FGameplayAbilitySpec spec(sa);
		AbilitySystemComponent->GiveAbility(spec);
	}
}

void ACCBaseCharacter::InitializeAttributes()
{
	check(InitializeAttributesClass);

	// 创建一个GameplayEffectContext，能够携带关于这个Effect的信息数据并传递出去
	FGameplayEffectContextHandle contextHandle = AbilitySystemComponent->MakeEffectContext();
	contextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle specHandle = AbilitySystemComponent->MakeOutgoingSpec(InitializeAttributesClass, 1.f, contextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*(specHandle.Data.Get()));// 这里是同步的，因为会返回FActiveGameplayEffectHandle
}

