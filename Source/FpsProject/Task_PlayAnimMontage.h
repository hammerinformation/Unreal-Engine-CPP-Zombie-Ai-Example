// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_PlayAnimMontage.generated.h"

UCLASS(config=Game)
class  UTask_PlayAnimMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTask_PlayAnimMontage();
	UPROPERTY(EditAnywhere)
	class UAnimMontage* AnimMontage{};
	virtual  EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual  void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
private:
	class UZombieAnimInstance* AnimInstance{};
	void FinishTaskWithTime(const float& Time,UBehaviorTreeComponent& OwnerComp) const;
};
