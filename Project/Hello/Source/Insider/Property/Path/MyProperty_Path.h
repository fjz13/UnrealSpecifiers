// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Path.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Path :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath)
	FDirectoryPath MyDirectory_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath, meta = (ContentDir))
	FDirectoryPath MyDirectory_ContentDir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath, meta = (LongPackageName))
	FDirectoryPath MyDirectory_LongPackageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath, meta = (RelativeToGameContentDir))
	FDirectoryPath MyDirectory_RelativeToGameContentDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DirectoryPath, meta = (RelativePath))
	FDirectoryPath MyDirectory_RelativePath;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath)
	FFilePath MyFilePath_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath, meta = (LongPackageName))
	FFilePath MyFilePath_LongPackageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath, meta = (RelativeToGameDir))
	FFilePath MyFilePath_RelativeToGameDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath, meta = (FilePathFilter = "umap"))
	FFilePath MyFilePath_FilePathFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FilePath, meta = (FilePathFilter = "My Config Files|*.ini"))
	FFilePath MyFilePath_FilePathFilter_INI;

public:
	UFUNCTION(CallInEditor)
	void PrintValues();
};

