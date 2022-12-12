// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_NeckBite.h"

UTask_NeckBite::UTask_NeckBite()
{
}

EBTNodeResult::Type UTask_NeckBite::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
