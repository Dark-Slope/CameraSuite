// Copyright 2024 Dark Slope Inc. All Rights Reserved.

#include "DS_GameMode.h"
#include "../Camera/DS_Camera.h"

ADS_GameMode::ADS_GameMode()
{
    // Set the default pawn class to your camera class
    DefaultPawnClass = ADS_Camera::StaticClass();
}