// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"



ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(ThirdPersonMappingContext, 0);
		}
	}
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Cast to Enhanced Input Component
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind the move action
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
	}
}

void ATank::Move(const FInputActionValue& Value)
{
	FVector2D ValueVector = Value.Get<FVector2D>();

	if (Controller) 
	{


		FVector DeltaLocation = FVector::ZeroVector;
		DeltaLocation.X = ValueVector.X * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
		AddActorLocalOffset(DeltaLocation);

		UE_LOG(LogTemp, Warning, TEXT("x-Axis Value: %f, y-Axis Value: %f"), ValueVector.X, ValueVector.Y);
	}
}