// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Buest.h"

#include "Misc/Paths.h"
#include "ShaderCore.h"

#define LOCTEXT_NAMESPACE "FBuestModule"

void FBuestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// FString ShaderDirectory = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("Buest/Shaders/Public"));
	// AddShaderSourceDirectoryMapping("/Plugin/Buest/Public", ShaderDirectory);
}

void FBuestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBuestModule, Buest)