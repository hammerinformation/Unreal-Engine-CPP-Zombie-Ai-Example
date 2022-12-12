
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"

class UWeaponAnimInstance;
class USkeletalMeshComponent;
class AFpsCharacter;
class UInputComponent;
class UParticleSystem;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPSPROJECT_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	USkeletalMeshComponent* WeaponMesh;
	AFpsCharacter* FpsCharacter;

	UInputComponent* InputComponent;

	void StartFire(void);
	void OnFire(void);
	void StopFire(void);
	void Reload(void);



	UPROPERTY(EditAnywhere)
		UAnimMontage* FireAnimMontage;

	UPROPERTY(EditAnywhere)
		UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditAnywhere)
		UAnimMontage* Hit;



	UPROPERTY(VisibleAnywhere)
		int Bullet = 5;
	UPROPERTY(VisibleAnywhere)
		int TotalBullet = 150;
	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;

	UWeaponAnimInstance* WeaponAnimInstance;




};
