#include "Task_RotateToVector.h"

#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "DrawDebugHelpers.h"
#include "Extension.h"
#include  "FpsCharacter.h"
#include "Zombie.h"
#include "Kismet/GameplayStatics.h"


UTask_RotateToVector::UTask_RotateToVector()
{
	NodeName = TEXT("Task RotateToVector");
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

void UTask_RotateToVector::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (Pawn)
	{
		const FVector Target = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetVector.SelectedKeyName);

		Pawn->SetActorRotation(FMath::Lerp(Pawn->GetActorRotation(), (Target - Pawn->GetActorLocation()).Rotation(),0.04f));
		const FVector ForwardVector = Pawn->GetActorForwardVector();
		const FVector TargetLocation = Target - Pawn->GetActorLocation();
		const float DotProduct = FVector::DotProduct(ForwardVector.GetUnsafeNormal(), TargetLocation.GetUnsafeNormal());
	//	HIExtension::Print(FColor::Red, DotProduct);

		if (DotProduct > 0.95f)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}


EBTNodeResult::Type UTask_RotateToVector::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}


void UTask_RotateToVector::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	AIController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	Pawn = Cast<AZombie> (AIController->GetPawn());
}
