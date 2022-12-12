#include "Service_ChangeSpeed.h"
#include "ZombieAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Zombie.h"

UService_ChangeSpeed::UService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bCreateNodeInstance = true;
	NodeName="Service_ChangeSpeed";
}

void UService_ChangeSpeed::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	ZombieAIController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	Zombie = Cast<AZombie>(ZombieAIController->GetPawn());

	CharacterMovementComponent = Zombie->GetCharacterMovement();
}

void UService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ActiveMaxWalkSpeed != -1.f)
	{
		CharacterMovementComponent->MaxWalkSpeed = ActiveMaxWalkSpeed;
	}
	if (ActiveMaxAcceleration != -1.f)
	{
		CharacterMovementComponent->MaxAcceleration = ActiveMaxAcceleration;
	}
}

void UService_ChangeSpeed::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (DeactivatedMaxWalkSpeed != -1.f)
	{
		CharacterMovementComponent->MaxWalkSpeed = DeactivatedMaxWalkSpeed;
	}
	if (DeactivatedMaxAcceleration != -1.f)
	{
		CharacterMovementComponent->MaxAcceleration = DeactivatedMaxAcceleration;
	}
}
