
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_RotateToVector.generated.h"


UCLASS(config = Game)
class  UTask_RotateToVector : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_RotateToVector();
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetVector;


	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
private:
	class AZombieAIController* AIController{};
	class APawn* Pawn{};
	
};
