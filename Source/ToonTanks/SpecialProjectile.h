

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "SpecialProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ASpecialProjectile : public AProjectile
{
	GENERATED_BODY()
	
public:
	ASpecialProjectile();


private: 
	float SuperDamage = 100.f;

protected:
	virtual void BeginPlay() override;
};
