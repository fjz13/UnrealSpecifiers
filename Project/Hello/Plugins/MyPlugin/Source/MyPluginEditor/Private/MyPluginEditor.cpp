// Copyright 2018 Jianzhao Fu. All Rights Reserved.

#include "MyPluginEditor.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FMyPluginEditorModule"

void FMyPluginEditorModule::StartupModule()
{

}

void FMyPluginEditorModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMyPluginEditorModule, MyPluginEditor)