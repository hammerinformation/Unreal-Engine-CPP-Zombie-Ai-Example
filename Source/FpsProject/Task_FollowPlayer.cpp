

#include "Task_FollowPlayer.h"

#include "FpsCharacter.h"
#include "ZombieAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Extension.h"

UTask_FollowPlayer::UTask_FollowPlayer()
{
	NodeName = "Task Follow Player";
	bNotifyTick = true;
	bCreateNodeInstance = true;

}
void UTask_FollowPlayer::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Player = Cast<AFpsCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ZombieAIController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	Pawn = ZombieAIController->GetPawn();
}
EBTNodeResult::Type UTask_FollowPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	if (ZombieAIController == nullptr || Player == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::InProgress;
}

void UTask_FollowPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const float Distance = FVector::Distance(Pawn->GetActorLocation(), Player->GetActorLocation());
	//HIExtension::Print(FColor::Magenta,Distance);
	ZombieAIController->MoveToActor(Player, 34, true);

	
	if(Distance<125.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}





