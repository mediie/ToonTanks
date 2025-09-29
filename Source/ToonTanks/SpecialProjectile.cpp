

#include "SpecialProjectile.h"

ASpecialProjectile::ASpecialProjectile()
{
	// Example: higher damage
	// You can set unique particle/sound/camera shake here
	
	if (ProjectileMesh)
	{
		ProjectileMesh->SetCollisionProfileName(TEXT("Projectile"));
		ProjectileMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore); // Custom channel for projectiles
		ProjectileMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	}
}



void ASpecialProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}