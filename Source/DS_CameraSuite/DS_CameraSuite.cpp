// Copyright 2024 Dark Slope Inc. All Rights Reserved.

#include "DS_CameraSuite.h"

#define LOCTEXT_NAMESPACE "FDS_CameraSuiteModule"

void FDS_CameraSuiteModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FDS_CameraSuiteModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDS_CameraSuiteModule, DS_CameraSuite)