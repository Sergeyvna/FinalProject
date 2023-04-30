#include "ControlSettingsMenu.h"
#include "InputCoreTypes.h"
#include "GameFramework/InputSettings.h"


void UControlSettingsMenu::ChangeControls()
{
    // Update the current control scheme
    CurrentControlScheme = static_cast<EControlScheme>((static_cast<int32>(CurrentControlScheme) + 1) % 3);

    UInputSettings* InputSettings = UInputSettings::GetInputSettings();

    if (!InputSettings)
    {
        return;
    }

    // Remove existing mappings
    TArray<FKey> MoveForwardKeysToRemove = { EKeys::Gamepad_LeftY, EKeys::Gamepad_RightY };
    TArray<FKey> MoveRightKeysToRemove = { EKeys::Gamepad_LeftX, EKeys::Gamepad_RightX };
    TArray<FKey> SprintKeysToRemove = { EKeys::Gamepad_LeftThumbstick, EKeys::Gamepad_RightThumbstick };
    TArray<FKey> RollingKeysToRemove = { EKeys::Gamepad_FaceButton_Bottom, EKeys::Gamepad_DPad_Down };
    TArray<FKey> WeakAttackKeysToRemove = { EKeys::Gamepad_LeftShoulder, EKeys::Gamepad_RightShoulder };
    TArray<FKey> BlockKeysToRemove = { EKeys::Gamepad_LeftTrigger, EKeys::Gamepad_RightTrigger };

    // Remove camera mappings
    TArray<FKey> TurnKeysToRemove = { EKeys::Gamepad_RightX, EKeys::Gamepad_LeftX };
    TArray<FKey> LookUpKeysToRemove = { EKeys::Gamepad_RightY, EKeys::Gamepad_LeftY };


    // For loop to remove each key in the arrays
    for (FKey Key : MoveForwardKeysToRemove)
    {
        InputSettings->RemoveAxisMapping(FInputAxisKeyMapping("MoveForward", Key), false);
    }
    for (FKey Key : MoveRightKeysToRemove)
    {
        InputSettings->RemoveAxisMapping(FInputAxisKeyMapping("MoveRight", Key), false);
    }
    for (FKey Key : SprintKeysToRemove)
    {
        InputSettings->RemoveAxisMapping(FInputAxisKeyMapping("Sprinting", Key, 5.0f), false);
    }

    for (FKey Key : RollingKeysToRemove)
    {
        InputSettings->RemoveActionMapping(FInputActionKeyMapping("Rolling", Key), false);
    }
    for (FKey Key : WeakAttackKeysToRemove)
    {
        InputSettings->RemoveActionMapping(FInputActionKeyMapping("WeakAttack", Key), false);
    }
    for (FKey Key : BlockKeysToRemove)
    {
        InputSettings->RemoveActionMapping(FInputActionKeyMapping("Blocking", Key), false);
    }

    // for loop to remove camera keys
    for (FKey Key : TurnKeysToRemove)
    {
        InputSettings->RemoveAxisMapping(FInputAxisKeyMapping("Turn", Key), false);
    }
    for (FKey Key : LookUpKeysToRemove)
    {
        InputSettings->RemoveAxisMapping(FInputAxisKeyMapping("LookUp", Key), false);
    }

    // Adding new input mappings according to the control scheme
    FKey NewMoveForwardKey, NewMoveRightKey, NewSprintKey, NewRollingKey, NewWeakAttackKey, NewBlockKey, NewTurnKey, NewLookUpKey;
    switch (CurrentControlScheme)
    {
    case EControlScheme::CS_BothHands:
        NewMoveForwardKey = EKeys::Gamepad_LeftY;
        NewMoveRightKey = EKeys::Gamepad_LeftX;
        NewSprintKey = EKeys::Gamepad_LeftThumbstick;
        NewRollingKey = EKeys::Gamepad_FaceButton_Bottom;
        NewWeakAttackKey = EKeys::Gamepad_RightShoulder;
        NewBlockKey = EKeys::Gamepad_LeftTrigger;
        NewTurnKey = EKeys::Gamepad_RightX;
        NewLookUpKey = EKeys::Gamepad_RightY;
        break;

    case EControlScheme::CS_LeftHand:
        NewMoveForwardKey = EKeys::Gamepad_LeftY;
        NewMoveRightKey = EKeys::Gamepad_LeftX;
        NewSprintKey = EKeys::Gamepad_LeftThumbstick;
        NewRollingKey = EKeys::Gamepad_DPad_Down;
        NewWeakAttackKey = EKeys::Gamepad_LeftShoulder;
        NewBlockKey = EKeys::Gamepad_LeftTrigger;
        NewTurnKey = EKeys::Gamepad_RightX;
        NewLookUpKey = EKeys::Gamepad_RightY;
        break;

    case EControlScheme::CS_RightHand:
        NewMoveForwardKey = EKeys::Gamepad_RightY;
        NewMoveRightKey = EKeys::Gamepad_RightX;
        NewSprintKey = EKeys::Gamepad_RightThumbstick;
        NewRollingKey = EKeys::Gamepad_FaceButton_Bottom;
        NewWeakAttackKey = EKeys::Gamepad_RightShoulder;
        NewBlockKey = EKeys::Gamepad_RightTrigger;
        NewTurnKey = EKeys::Gamepad_LeftX;
        NewLookUpKey = EKeys::Gamepad_LeftY;

        break;

    default:
        return;
    }


    float MoveForwardScale = 1.f;
    if (CurrentControlScheme == EControlScheme::CS_RightHand)
    {
        MoveForwardScale = -1.f;
    }

    InputSettings->AddAxisMapping(FInputAxisKeyMapping("MoveForward", NewMoveForwardKey, MoveForwardScale), false);
    InputSettings->AddAxisMapping(FInputAxisKeyMapping("MoveRight", NewMoveRightKey, 1.f), false);
    InputSettings->AddAxisMapping(FInputAxisKeyMapping("MoveRight", NewSprintKey, 5.f), false);

    InputSettings->AddActionMapping(FInputActionKeyMapping("Rolling", NewRollingKey), false);
    InputSettings->AddActionMapping(FInputActionKeyMapping("WeakAttack", NewWeakAttackKey), false);
    InputSettings->AddActionMapping(FInputActionKeyMapping("Blocking", NewBlockKey), false);

    InputSettings->AddAxisMapping(FInputAxisKeyMapping("Turn", NewTurnKey, 1.f), false);
    InputSettings->AddAxisMapping(FInputAxisKeyMapping("LookUp", NewLookUpKey, 1.f), false);

    InputSettings->SaveKeyMappings();


    // Update the text on the button
    if (ControlSchemeText)
    {
        FString NewText;

        switch (CurrentControlScheme)
        {
        case EControlScheme::CS_RightHand:
            NewText = TEXT("Right Hand");
            break;
        case EControlScheme::CS_LeftHand:
            NewText = TEXT("Left Hand");
            break;
        default:
            NewText = TEXT("Both Hands");
            break;
        }
        ControlSchemeText->SetText(FText::FromString(NewText));
    }

    
}
