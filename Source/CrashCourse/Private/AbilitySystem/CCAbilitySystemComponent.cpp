// Copyright Gaia


#include "AbilitySystem/CCAbilitySystemComponent.h"
#include "GameplayTags/CCGameplayTags.h"

void UCCAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	// 服务端给予能力
	HandlAutoActivatedAbility(AbilitySpec);
}

void UCCAbilitySystemComponent::OnRep_ActivateAbilities()
{
	// 客户端收到能力激活的消息
	FScopedAbilityListLock lock(*this);// 当访问激活能力时是不安全的，存在异步删除能力或取消能力，所以访问时上范围锁
	for (const auto& spec : GetActivatableAbilities()/** Returns the list of all activatable abilities. */)
	{
		HandlAutoActivatedAbility(spec);
	}
}

void UCCAbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> abilityClass, int32 level)
{
	if (!IsValid(abilityClass) || !IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;

	FGameplayAbilitySpec* spec = FindAbilitySpecFromClass(abilityClass);
	if (!spec) return;

	spec->Level = level;
	MarkAbilitySpecDirty(*spec);
}

void UCCAbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> abilityClass, int32 level)
{
	if (!IsValid(abilityClass) || !IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;

	FGameplayAbilitySpec* spec = FindAbilitySpecFromClass(abilityClass);
	if (!spec) return;
	spec->Level += level;
	MarkAbilitySpecDirty(*spec);
}

void UCCAbilitySystemComponent::HandlAutoActivatedAbility(const FGameplayAbilitySpec& abilitySpec)
{
	// 当能力被给予的时候，发现能力带有CCTags::Abilities::ActivateOnGiven（能力被给予时就激活）
	// 尝试激活能力
	if (!IsValid(abilitySpec.Ability)) return;

	const FGameplayTagContainer& tagContainer = abilitySpec.Ability->GetAssetTags();
	/**
	 * Determine if TagToCheck is present in this container, also checking against parent tags
	 * {"A.1"}.HasTag("A") will return True, {"A"}.HasTag("A.1") will return False
	 * If TagToCheck is not Valid it will always return False
	 *
	 * @return True if TagToCheck is in this container, false if it is not
	 */
	//if (tagContainer.HasTag(CCTags::Abilities::ActivateOnGiven))
	//{
	//	TryActivateAbility(abilitySpec.Handle);
	//}
	for (const FGameplayTag& tag : tagContainer)
	{
		if (tag.MatchesTagExact(CCTags::Abilities::ActivateOnGiven))
		{
			TryActivateAbility(abilitySpec.Handle);
			return;
		}
	}
}
