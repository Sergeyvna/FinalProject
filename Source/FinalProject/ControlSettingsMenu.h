// ControlSettingsMenu.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ControlSettingsMenu.generated.h"

UENUM(BlueprintType)
enum class EControlScheme : uint8
{
    CS_BothHands UMETA(DisplayName = "Both Hands"),
    CS_LeftHand  UMETA(DisplayName = "Left Hand"),
    CS_RightHand UMETA(DisplayName = "Right Hand")
};

UCLASS()
class FINALPROJECT_API UControlSettingsMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Input")
        void ChangeControls();

   

protected:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* ControlSchemeText;

private:
    UPROPERTY(BlueprintReadWrite, Category = "Controls", meta = (AllowPrivateAccess = "true"))
        EControlScheme CurrentControlScheme;
};
