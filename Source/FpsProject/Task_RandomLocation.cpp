

#include "Task_RandomLocation.h"

#include "NavigationSystem.h"
#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Extension.h"
UTask_RandomLocation::UTask_RandomLocation() {
	NodeName = TEXT("Task_RandomLocation");
	bCreateNodeInstance=true;
}

EBTNodeResult::Type UTask_RandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	HIExtension::Print(FColor::Red,"ExecuteTask");
	
	if(!Pawn||!AIController)
	{
		return EBTNodeResult::Failed;
	}
	FNavLocation Loc;
	FVector const Origin = Pawn->GetActorLocation();
	const UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavigationSystem->GetRandomReachablePointInRadius(Origin, 2800.0f, Loc)) {
		AIController->GetBlackboardComponent()->SetValueAsVector("RandomLocation", Loc.Location);
		return EBTNodeResult::Succeeded;

	}
	else {
		return EBTNodeResult::Failed;

	}
}


void UTask_RandomLocation::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	HIExtension::Print(FColor::Red,"OnInstanceCreated");
	AIController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	Pawn = AIController->GetPawn();
}

