
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZombieAnimInstance.generated.h"

UCLASS(config=Game)
class  UZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
		float Speed;
	UPROPERTY(BlueprintReadOnly)
		int Healt;
};
