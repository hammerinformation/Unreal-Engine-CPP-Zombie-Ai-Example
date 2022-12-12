
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_FollowPlayer.generated.h"

class AFpsCharacter;
class AZombieAIController;

UCLASS(config = Game)
class  UTask_FollowPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UTask_FollowPlayer();

	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	AFpsCharacter* Player{};
	AZombieAIController* ZombieAIController{};
	APawn* Pawn{};

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
