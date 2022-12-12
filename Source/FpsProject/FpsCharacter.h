// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FpsCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;

UCLASS(config = Game)
class  AFpsCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AFpsCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveRight(float Value);
	void MoveForward(float Value);


	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USkeletalMeshComponent* WeaponMesh;

};
