
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

class UZombieAnimInstance;
class UCharacterMovementComponent;

UCLASS(config = Game)
class  AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	AZombie();

protected:
	virtual void BeginPlay() override;

private:
	int Healt{ 100 };
	void Check();
	UZombieAnimInstance* ZombieAnimInstance{};
	void StopMovement()const;
	void StartMovement( float) const;
	void Die()const;
	class AZombieAIController* AIController {};
public:
	void DecreaseHealth(const int);

	FORCEINLINE int GetHealt() const { return Healt; }
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Hit{};


private:
	class  AFpsCharacter* Player{};



};
