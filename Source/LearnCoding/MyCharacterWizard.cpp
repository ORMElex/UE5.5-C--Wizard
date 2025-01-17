
#include "MyCharacterWizard.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacterWizard::AMyCharacterWizard() : Super()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
}

// Called when the game starts or when spawned
void AMyCharacterWizard::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);

	HealthComponent->OnDeath.AddUObject(this, &AMyCharacterWizard::OnDeath);
	LandedDelegate.AddDynamic(this, &AMyCharacterWizard::LandedOnGround);

}

// Called to bind functionality to input
void AMyCharacterWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMyCharacterWizard::MoveForward);
	PlayerInputComponent->BindAxis("Straif", this, &AMyCharacterWizard::MoveSide);

	PlayerInputComponent->BindAxis("TurnX", this, &AMyCharacterWizard::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnY", this, &AMyCharacterWizard::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacterWizard::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacterWizard::JumpReleased);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacterWizard::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacterWizard::SprintStop);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, WeaponComponent, &UWeaponComponent::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, WeaponComponent, &UWeaponComponent::AttackStop);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AMyCharacterWizard::ToggleInventory);
}



void AMyCharacterWizard::AddControllerYawInput(float Value)
{
	if (Controller && Value != 0)
	{
		Value *= Sensitivity;

		Super::AddControllerYawInput(Value);
	}
}

void AMyCharacterWizard::MoveForward(float value)
{
	if (Controller && value)
	{
		FRotator ControlRotation = Camera->GetComponentRotation();
		ControlRotation.Pitch = 0.0f; 
		ControlRotation.Roll = 0.0f;


		FVector VForw = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
		/*FVector VForw = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);*/
		AddMovementInput(VForw, value);
		//SetActorRotation(ControlRotation);
	}
}

void AMyCharacterWizard::MoveSide(float value)
{
	FRotator ControlRotation = Controller->GetControlRotation();
	ControlRotation.Pitch = 0.0f; 
	ControlRotation.Roll = 0.0f;

	FVector VRight = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);
	/*FVector VRight = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);*/
	AddMovementInput(VRight, value);
}

void AMyCharacterWizard::Jump()
{
	bPressedJump = true;
}

void AMyCharacterWizard::JumpReleased()
{
	bPressedJump = false;
}

void AMyCharacterWizard::Sprint()
{
	if(GetCharacterMovement()) GetCharacterMovement()->MaxWalkSpeed = 1200; \
	else GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Unsuccess");
}

void AMyCharacterWizard::SprintStop()
{
	if (GetCharacterMovement()) GetCharacterMovement()->MaxWalkSpeed = 600;
	else GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Unsuccess");
}

void AMyCharacterWizard::ToggleInventory()
{

}

void AMyCharacterWizard::Pickup(APickupItem* Item)
{
	if (Backpack.Find(Item->itemName))
	{
		Backpack[Item->itemName] += Item->itemQuantity;
	}
	else
	{
		Backpack.Add(Item->itemName, Item->itemQuantity);
		itemsIcons.Add(Item->itemName, Item->itemIcon);
	}
}




void AMyCharacterWizard::OnDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("You died"));
	GetCharacterMovement()->DisableMovement();
}

void AMyCharacterWizard::LandedOnGround(const FHitResult& Hit)
{
	const auto FallVelocity = -GetCharacterMovement()->Velocity.Z;

	if (FallVelocity < LandedVelocityRange.X) return;

	const float FallDamage = FMath::GetMappedRangeValueClamped(LandedVelocityRange, LandedDamage, FallVelocity);
	TakeDamage(FallDamage, FDamageEvent{}, nullptr, this);
}