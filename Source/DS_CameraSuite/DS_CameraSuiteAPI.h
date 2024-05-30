// Copyright 2024 Dark Slope Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#ifdef DS_CAMERASUITE_EXPORTS
	#define DSCAMERASUITE_API __declspec(dllexport)
#else
	#define DSCAMERASUITE_API __declspec(dllimport)
#endif
