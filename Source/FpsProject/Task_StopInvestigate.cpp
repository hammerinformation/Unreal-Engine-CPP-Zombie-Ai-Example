

#include "Task_StopInvestigate.h"

#include "Zombie.h"
#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_StopInvestigate::UTask_StopInvestigate()
{
	NodeName = "Task_StopInvestigate ";
	bCreateNodeInstance = true;
}

void UTask_StopInvestigate::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	AIController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	Pawn = Cast<AZombie> (AIController->GetPawn());
}

EBTNodeResult::Type UTask_StopInvestigate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController->GetBlackboardComponent()->SetValueAsVector("InvestigateLocation", FVector::ZeroVector);
	AIController->GetBlackboardComponent()->SetValueAsBool("Investigate", false);
	return EBTNodeResult::Succeeded;
}
