#include "MyCustomAssetEditorToolkit.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/SCanvas.h"
#include "Modules/ModuleManager.h"
#include "Customization/MyCommonObjectCustomization.h"


void FMyCustomAssetEditorToolkit::InitEditor(const TArray<UObject*>& InObjects)
{
	MyCustomAsset = Cast<UMyCustomAsset>(InObjects[0]);

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("MyCustomAssetEditorLayout")
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewSplitter()
			->SetSizeCoefficient(0.6f)
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.8f)
				->AddTab("MyCustomAssetSummaryTab", ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab("MyCustomAssetDetailsTab", ETabState::OpenedTab)
			)
		)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.4f)
			->AddTab("OutputLog", ETabState::OpenedTab)
		)
	);

	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, {}, "MyCustomAssetEditor", Layout, true, true, InObjects);
}

void FMyCustomAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("MyCustomAssetEditor"));
	
	//summary
	InTabManager->RegisterTabSpawner("MyCustomAssetSummaryTab", FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)
		[
			SNew(STextBlock).Text(INVTEXT("Summary of Object, just for demo."))
		];
	}))
	.SetDisplayName(INVTEXT("Summary"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	//details
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObjects(TArray<UObject*>{ MyCustomAsset });



	InTabManager->RegisterTabSpawner("MyCustomAssetDetailsTab", FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)
		[
			DetailsView
		];
	}))
	.SetDisplayName(INVTEXT("Details"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	//register custom layout

	DetailsView->RegisterInstancedCustomPropertyLayout(UMyCommonObject::StaticClass(),FOnGetDetailCustomizationInstance::CreateStatic(&FMyCommonObjectDetailsCustomization::MakeInstance));
}

void FMyCustomAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner("MyCustomAssetSummaryTab");
	InTabManager->UnregisterTabSpawner("MyCustomAssetDetailsTab");
}

