
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"

#include "Service_ChangeSpeed.generated.h"

class AZombieAIController;
class UCharacterMovementComponent;
class AZombie;
UCLASS(config = Game)
class  UService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UService_ChangeSpeed();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
private:
	AZombieAIController* ZombieAIController;
	UCharacterMovementComponent* CharacterMovementComponent;
	AZombie* Zombie;

	UPROPERTY(EditAnywhere)
		float ActiveMaxWalkSpeed{-1.f};
	UPROPERTY(EditAnywhere)
		float DeactivatedMaxWalkSpeed{-1.f};
	UPROPERTY(EditAnywhere)
		float ActiveMaxAcceleration{-1.f};
	UPROPERTY(EditAnywhere)
		float DeactivatedMaxAcceleration{-1.f};
};
