#include "WriteSaveFile.h"
#include "Misc/FileHelper.h"
#include "Serialization/BufferArchive.h"
#include "Engine/Engine.h"

AWriteSaveFile::AWriteSaveFile()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AWriteSaveFile::BeginPlay()
{
    Super::BeginPlay();

    if (Write)
    {
        WriteSaveDataToFile();
    }

    if (Read)
    {
        ReadSaveDataFile();
    }
}

void AWriteSaveFile::WriteSaveDataToFile()
{
    FString SaveDirectory = FPaths::ProjectDir() + "GameSaves/";
    FString SaveFileName = "Save.sav";

    FString FullPath = SaveDirectory + SaveFileName;

    bool TutorialDone = true;

    FBufferArchive BufferArchive;

    BufferArchive << TutorialDone;

    if (FFileHelper::SaveArrayToFile(BufferArchive, *FullPath))
    {
        FString Message = FString::Printf(TEXT("Save made at: %s"), *FullPath);
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, Message);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Failed to save file"));
    }
}

void AWriteSaveFile::ReadSaveDataFile()
{
    FString SaveDirectory = FPaths::ProjectDir() + "GameSaves/";
    FString SaveFileName = "Save.sav";

    FString FullPath = SaveDirectory + SaveFileName;

    if (!FPaths::FileExists(FullPath))
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Save file not found: %s"), *FullPath));
        return;
    }

    TArray<uint8> FileData;
    if (FFileHelper::LoadFileToArray(FileData, *FullPath))
    {
        FMemoryReader MemoryReader(FileData, true);

        bool TutorialDone;
        MemoryReader << TutorialDone;

        if (TutorialDone)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Tutorial is done")));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Tutorial is not done")));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Failed to load file: %s"), *FullPath));
    }
}

bool AWriteSaveFile::ReadSaveDataFileBool()
{
    FString SaveDirectory = FPaths::ProjectDir() + "GameSaves/";
    FString SaveFileName = "Save.sav";

    FString FullPath = SaveDirectory + SaveFileName;

    if (!FPaths::FileExists(FullPath))
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Save file not found: %s"), *FullPath));
        return false;
    }

    TArray<uint8> FileData;
    if (FFileHelper::LoadFileToArray(FileData, *FullPath))
    {
        FMemoryReader MemoryReader(FileData, true);

        bool TutorialDone;
        MemoryReader << TutorialDone;

        if (TutorialDone)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Tutorial is done")));
            return true;
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Tutorial is not done")));
            return false;
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("Failed to load file: %s"), *FullPath));
        return false;
    }
    return false;
}