#include "DS_Camera.h"

ADS_Camera::ADS_Camera(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer),
      CameraMovementSpeed(10.0f),
      bIsMovingForward(false),
      bIsMovingBackward(false),
      bIsMovingRight(false),
      bIsMovingLeft(false),
      bIsMovingUp(false),
      bIsMovingDown(false),
      bIsIncrementing(false),
      bIsDecrementing(false)
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    RootComponent = SpringArmComponent; // Set SpringArmComponent as the root component

    CineCameraComponent = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCameraComponent"));
    CineCameraComponent->SetupAttachment(SpringArmComponent);

    FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void ADS_Camera::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("ADS_Camera BeginPlay called"));

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
            UE_LOG(LogTemp, Warning, TEXT("InputMappingContext added to subsystem"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to get UEnhancedInputLocalPlayerSubsystem"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get APlayerController"));
    }
}

void ADS_Camera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Continuous movement logic
    FVector MovementVector = FVector::ZeroVector;

    if (bIsMovingForward)
    {
        MovementVector += GetActorForwardVector();

        bIsMovingForward = false;
    }
    if (bIsMovingBackward)
    {
        MovementVector -= GetActorForwardVector();

        bIsMovingBackward = false;
    }
    if (bIsMovingRight)
    {
        MovementVector += GetActorRightVector();

        bIsMovingRight = false;
    }
    if (bIsMovingLeft)
    {
        MovementVector -= GetActorRightVector();

        bIsMovingLeft = false;
    }
    if (bIsMovingUp)
    {
        MovementVector += GetActorUpVector();

        bIsMovingUp = false;
    }
    if (bIsMovingDown)
    {
        MovementVector -= GetActorUpVector();

        bIsMovingDown = false;
    }

    if (!MovementVector.IsZero())
    {
        AddMovementInput(MovementVector, CameraMovementSpeed * DeltaTime);
    }

    // Continuous increment/decrement logic
    if (bIsIncrementing)
    {
        IncrementValue(DeltaTime);
    }
    if (bIsDecrementing)
    {
        DecrementValue(DeltaTime);
    }
}

void ADS_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UE_LOG(LogTemp, Warning, TEXT("ADS_Camera SetupPlayerInputComponent called"));

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Started, this, &ADS_Camera::MoveForwardStarted);
        EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Completed, this, &ADS_Camera::MoveForwardCompleted);
        EnhancedInputComponent->BindAction(MoveBackwardsAction, ETriggerEvent::Started, this, &ADS_Camera::MoveBackwardStarted);
        EnhancedInputComponent->BindAction(MoveBackwardsAction, ETriggerEvent::Completed, this, &ADS_Camera::MoveBackwardCompleted);
        EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Started, this, &ADS_Camera::MoveRightStarted);
        EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Completed, this, &ADS_Camera::MoveRightCompleted);
        EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Started, this, &ADS_Camera::MoveLeftStarted);
        EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Completed, this, &ADS_Camera::MoveLeftCompleted);
        EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Started, this, &ADS_Camera::MoveUpStarted);
        EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Completed, this, &ADS_Camera::MoveUpCompleted);
        EnhancedInputComponent->BindAction(MoveDownAction, ETriggerEvent::Started, this, &ADS_Camera::MoveDownStarted);
        EnhancedInputComponent->BindAction(MoveDownAction, ETriggerEvent::Completed, this, &ADS_Camera::MoveDownCompleted);
        
        EnhancedInputComponent->BindAction(IncrementValueAction, ETriggerEvent::Started, this, &ADS_Camera::IncrementValueStarted);
        EnhancedInputComponent->BindAction(IncrementValueAction, ETriggerEvent::Completed, this, &ADS_Camera::IncrementValueCompleted);
        EnhancedInputComponent->BindAction(DecrementValueAction, ETriggerEvent::Started, this, &ADS_Camera::DecrementValueStarted);
        EnhancedInputComponent->BindAction(DecrementValueAction, ETriggerEvent::Completed, this, &ADS_Camera::DecrementValueCompleted);

        UE_LOG(LogTemp, Warning, TEXT("Input actions bound successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to cast to UEnhancedInputComponent"));
    }
}

void ADS_Camera::MoveForwardStarted(const FInputActionValue& Value)
{
    bIsMovingForward = true;
}

void ADS_Camera::MoveForwardCompleted(const FInputActionValue& Value)
{
    bIsMovingForward = false;
    UE_LOG(LogTemp, Warning, TEXT("MoveForward Completed"));

    // Debug logging for location
    UE_LOG(LogTemp, Warning, TEXT("ADS_Camera location: %s"), *GetActorLocation().ToString());
}

void ADS_Camera::MoveBackwardStarted(const FInputActionValue& Value)
{
    bIsMovingBackward = true;
}

void ADS_Camera::MoveBackwardCompleted(const FInputActionValue& Value)
{
    bIsMovingBackward = false;
    UE_LOG(LogTemp, Warning, TEXT("MoveBackward Completed"));

    // Debug logging for location
    UE_LOG(LogTemp, Warning, TEXT("ADS_Camera location: %s"), *GetActorLocation().ToString());
}

void ADS_Camera::MoveRightStarted(const FInputActionValue& Value)
{
    bIsMovingRight = true;
}

void ADS_Camera::MoveRightCompleted(const FInputActionValue& Value)
{
    bIsMovingRight = false;
    UE_LOG(LogTemp, Warning, TEXT("MoveRight Completed"));

    // Debug logging for location
    UE_LOG(LogTemp, Warning, TEXT("ADS_Camera location: %s"), *GetActorLocation().ToString());
}

void ADS_Camera::MoveLeftStarted(const FInputActionValue& Value)
{
    bIsMovingLeft = true;
}

void ADS_Camera::MoveLeftCompleted(const FInputActionValue& Value)
{
    bIsMovingLeft = false;
    UE_LOG(LogTemp, Warning, TEXT("MoveLeft Completed"));

    // Debug logging for location
    UE_LOG(LogTemp, Warning, TEXT("ADS_Camera location: %s"), *GetActorLocation().ToString());
}

void ADS_Camera::MoveUpStarted(const FInputActionValue& Value)
{
    bIsMovingUp = true;
}

void ADS_Camera::MoveUpCompleted(const FInputActionValue& Value)
{
    bIsMovingUp = false;
    UE_LOG(LogTemp, Warning, TEXT("MoveUp Completed"));

    // Debug logging for location
    UE_LOG(LogTemp, Warning, TEXT("ADS_Camera location: %s"), *GetActorLocation().ToString());
}

void ADS_Camera::MoveDownStarted(const FInputActionValue& Value)
{
    bIsMovingDown = true;
}

void ADS_Camera::MoveDownCompleted(const FInputActionValue& Value)
{
    bIsMovingDown = false;
    UE_LOG(LogTemp, Warning, TEXT("MoveDown Completed"));

    // Debug logging for location
    UE_LOG(LogTemp, Warning, TEXT("ADS_Camera location: %s"), *GetActorLocation().ToString());
}

void ADS_Camera::IncrementValueStarted()
{
    bIsIncrementing = true;
}

void ADS_Camera::IncrementValueCompleted()
{
    bIsIncrementing = false;
    UE_LOG(LogTemp, Warning, TEXT("IncrementValue Completed"));
}

void ADS_Camera::DecrementValueStarted()
{
    bIsDecrementing = true;
}

void ADS_Camera::DecrementValueCompleted()
{
    bIsDecrementing = false;
    UE_LOG(LogTemp, Warning, TEXT("DecrementValue Completed"));
}

void ADS_Camera::LogCurrentMode()
{
    UE_LOG(LogTemp, Warning, TEXT("Current Edit Mode: Movement"));
}

void ADS_Camera::LogCurrentValues()
{
    UE_LOG(LogTemp, Warning, TEXT("CameraMovementSpeed: %f"), CameraMovementSpeed);
}

void ADS_Camera::IncrementValue(float DeltaTime)
{
    float IncrementAmount = GetIncrementAmount();
    CameraMovementSpeed += IncrementAmount * DeltaTime;
    LogCurrentValues();
}

void ADS_Camera::DecrementValue(float DeltaTime)
{
    float DecrementAmount = GetIncrementAmount();
    CameraMovementSpeed -= DecrementAmount * DeltaTime;
    LogCurrentValues();
}

float ADS_Camera::GetIncrementAmount() const
{
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (PlayerController->IsInputKeyDown(EKeys::LeftShift) || PlayerController->IsInputKeyDown(EKeys::RightShift))
        {
            if (PlayerController->IsInputKeyDown(EKeys::LeftControl) || PlayerController->IsInputKeyDown(EKeys::RightControl))
            {
                return 150.0f;
            }
            return 150.0f;
        }
    }
    return 100.0f;
}
