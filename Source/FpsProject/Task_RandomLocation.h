
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_RandomLocation.generated.h"


UCLASS(config = Game)
class  UTask_RandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_RandomLocation();
	virtual  EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
private:
	class AZombieAIController* AIController{};
	class APawn* Pawn{};
};
