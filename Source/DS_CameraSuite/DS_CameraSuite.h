// Copyright 2024 Dark Slope Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "DS_CameraSuiteAPI.h"

class DSCAMERASUITE_API FDS_CameraSuiteModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};