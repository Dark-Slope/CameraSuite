#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CineCameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "../DS_CameraSuiteAPI.h"
#include "DS_Camera.generated.h"

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
    Forward,
    Backward,
    Right,
    Left,
    Up,
    Down
};

UCLASS()
class DSCAMERASUITE_API ADS_Camera : public APawn
{
    GENERATED_BODY()

public:    
    ADS_Camera(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float CameraMovementSpeed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCineCameraComponent* CineCameraComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveForwardAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveBackwardsAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveRightAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveLeftAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveUpAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveDownAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* SwitchEditModeAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IncrementValueAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* DecrementValueAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    UFloatingPawnMovement* FloatingPawnMovement;

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveForwardStarted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveForwardCompleted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveBackwardStarted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveBackwardCompleted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveRightStarted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveRightCompleted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveLeftStarted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveLeftCompleted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveUpStarted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveUpCompleted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveDownStarted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void MoveDownCompleted(const FInputActionValue& Value);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void IncrementValueStarted();

    UFUNCTION(BlueprintCallable, Category = "Input")
    void IncrementValueCompleted();

    UFUNCTION(BlueprintCallable, Category = "Input")
    void DecrementValueStarted();

    UFUNCTION(BlueprintCallable, Category = "Input")
    void DecrementValueCompleted();

private:
    bool bIsMovingForward;
    bool bIsMovingBackward;
    bool bIsMovingRight;
    bool bIsMovingLeft;
    bool bIsMovingUp;
    bool bIsMovingDown;
    bool bIsIncrementing;
    bool bIsDecrementing;
    
    void LogCurrentMode();
    void LogCurrentValues();
    void StopAllOtherMovements(EMovementDirection ExcludeDirection);
    void IncrementValue(float DeltaTime);
    void DecrementValue(float DeltaTime);
    float GetIncrementAmount() const;
};
