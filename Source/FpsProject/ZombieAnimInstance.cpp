
#include "ZombieAnimInstance.h"
#include "Zombie.h"
void UZombieAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (TryGetPawnOwner()) {
		Speed = TryGetPawnOwner()->GetVelocity().Size();

		AZombie* Zombie = Cast<AZombie>(TryGetPawnOwner());
		if(Zombie)
		{
			Healt = Zombie->GetHealt();
		}

	}
}