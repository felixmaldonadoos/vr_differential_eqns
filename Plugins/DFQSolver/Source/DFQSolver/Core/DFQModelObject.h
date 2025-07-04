// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ModelData.h"
#include "Engine/TimerHandle.h"
#include "DFQModelObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepDelegate, FModelData, ModelData);

UCLASS()
class UDFQModelObject : public UObject {
	GENERATED_BODY()

public: 
	
	UDFQModelObject() {
		UE_LOG(LogTemp, Log, TEXT("[UDFQModelObject::UDFQModelObject] "), ModelData.frame)

	};

	bool bRunning = false;
	bool bInitializedData = false;
	bool bInitializedModel = false;

	FModelData ModelData; 
	FTimerHandle StepTimerHandle; 

	FOnStepDelegate OnStep_Delegate;

	// 1. set timers to call step
	// 2. set event delegate of values after Step() --> out: FModelData
	// 3. and initial parameters 
	
	UFUNCTION()
	virtual void PostInitializeModelData() {
		UE_LOG(LogTemp, Log, TEXT("[UDFQModelObject::PostInitializeModelData]"));
		bInitializedData = true;
	};

	UFUNCTION()
	virtual void InitializeModelData(const float dt = 0.01) {
		UE_LOG(LogTemp, Log, TEXT("[DFQModelObject::InitializeModelData] dt: %f"), dt)
		ModelData = FModelData();
		ModelData.frame = 0;
		ModelData.SetParam("dt", dt);
		PostInitializeModelData();
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float fs_broadcast = 100;
	float dt_broadcast = 1/fs_broadcast;

	UFUNCTION()
	virtual void InitializeModel() {
		if (UWorld* World = GetWorld()) {
			if (!bInitializedData) {
				UE_LOG(LogTemp, Error, TEXT("[DFQModelObject::InitializeModel] ModelData not initialized."));
				return;
			};
			UE_LOG(LogTemp, Log, TEXT("[DFQModelObject::InitializeModel] starting with dt_broadcast: %f"), dt_broadcast);
			World->GetTimerManager().SetTimer(StepTimerHandle, this, &ThisClass::Step, dt_broadcast, true);
			bInitializedModel = true;
		}
		else { UE_LOG(LogTemp, Error, TEXT("[DFQModelObject::InitializeModel] UWorld NULL")) }
	}

	UFUNCTION()
	virtual void Start() {

		if (!bInitializedData) {
			UE_LOG(LogTemp, Error, TEXT("[DFQModelObject::Start] ModelData not initialized."));
			return;
		};

		if (bInitializedModel) bRunning = true;
	}

	UFUNCTION()
	virtual void Stop() {
		if (bRunning) {
			if (UWorld* World = GetWorld()) {
				if (World->GetTimerManager().IsTimerActive(StepTimerHandle)) {
					World->GetTimerManager().ClearTimer(StepTimerHandle);
				}
			}

			// Unbind any delegates here (example placeholder):
			// OnStep.Clear();

			UE_LOG(LogTemp, Log, TEXT("[UDFQModelObject::Stop] Timer cleared and model stopped."));
			bRunning = false;
		}
	}

	UFUNCTION()
	virtual void Step() {
		ModelData.frame += 1;
		ModelData.t		+= ModelData.GetParam("dt",0.0);
	}
};