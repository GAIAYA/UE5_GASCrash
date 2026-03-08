// Copyright Gaia


#include "Utils/CCBlueprintLibrary.h"

EHitDirection UCCBlueprintLibrary::GetHitDirection(const FVector& targetForward, const FVector& toInstigator)
{// 目标向前向量，目标指向发起目标向量
	// 输入向量已经标准化
	const float dot = FVector::DotProduct(targetForward, toInstigator);

	if (dot < -0.5f)
	{
		return EHitDirection::Back;
	}
	if (dot < 0.5f)
	{
		const FVector cross = FVector::CrossProduct(targetForward, toInstigator);
		if (cross.Z > 0.f)
		{// UE是左手坐标系，前 叉乘 右是向上
			return EHitDirection::Right;
		}
		return EHitDirection::Left;
	}
	return EHitDirection::Front;
}

FName UCCBlueprintLibrary::GetHitDirectionName(const EHitDirection& hitDirection)
{
	switch (hitDirection)
	{
	case EHitDirection::Front:
		return FName("Front");
	case EHitDirection::Back:
		return FName("Back");
	case EHitDirection::Left:
		return FName("Left");
	case EHitDirection::Right:
		return FName("Right");
	default:
		return FName("None");
	}
}

