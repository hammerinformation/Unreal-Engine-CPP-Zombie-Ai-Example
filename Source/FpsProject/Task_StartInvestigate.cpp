

#include "Task_StartInvestigate.h"




#include "Zombie.h"
#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_StartInvestigate::UTask_StartInvestigate()
{
	NodeName = "Task_Start Investigate ";
	bCreateNodeInstance = true;
}

void UTask_StartInvestigate::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	AIController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	Pawn = Cast<AZombie> (AIController->GetPawn());
}

EBTNodeResult::Type UTask_StartInvestigate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}
