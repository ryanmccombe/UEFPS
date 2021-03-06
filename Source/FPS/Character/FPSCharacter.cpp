#include "FPSCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/// COMPONENTS
	// Third Person Camera setup for now - TODO: remove this eventually
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	// Enable Crouch
	ACharacter::GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AFPSCharacter::BeginPlay(){
	Super::BeginPlay();
}

void AFPSCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::Turn);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPSCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFPSCharacter::EndCrouch);
}

void AFPSCharacter::MoveForward(float Value) {
	AddMovementInput(GetActorForwardVector() * Value);
}

void AFPSCharacter::MoveRight(float Value) {
	AddMovementInput(GetActorRightVector() * Value);
}

void AFPSCharacter::LookUp(float Value) {
	AddControllerPitchInput(Value);
}

void AFPSCharacter::Turn(float Value) {
	AddControllerYawInput(Value);
}

void AFPSCharacter::StartCrouch() {
	Crouch();
}

void AFPSCharacter::EndCrouch() {
	UnCrouch();
}
