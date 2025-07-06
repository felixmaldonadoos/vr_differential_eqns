#include "SimulationActor.h"


// Sets default values
ASimulationActor::ASimulationActor() {
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASimulationActor::Start() {
	UE_LOG(LogTemp, Log, TEXT("[ASimulationActor::Start]"))
	//if (ModelObj) { ModelObj->InitializeModel(); }

	if (ModelObjClass) {
		ModelObj = NewObject<UDFQModelObject>(this, ModelObjClass);
		if (ModelObj) {
			ModelObj->AddToRoot();
			ModelObj->InitializeModelData(dt);
			ModelObj->InitializeModel();
			ModelObj->OnStep_Delegate.AddDynamic(this, &ThisClass::OnStepReceived);
			ModelObj->Start();
			UE_LOG(LogTemp, Log, TEXT("[ASimulationActor::Start] ModelObj VALID"))
		}
		else { UE_LOG(LogTemp, Error, TEXT("[ASimulationActor::Start] ModelObj NULL")) }
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("[ASimulationActor::Start] ModelObjClass NULL"))
	}
}

void ASimulationActor::SpawnEmitterFX() {
	UE_LOG(LogTemp, Log, TEXT("[ASimulationActor::SpawnEmitterFX]"));

	if (NiagaraFX) {
		UE_LOG(LogTemp, Error, TEXT("[ASimulationActor::SpawnEmitterFX] NiagaraFX Already spawned"));
		return;
	}

	if (!NiagaraSystemAsset) {
		UE_LOG(LogTemp, Error, TEXT("[ASimulationActor::SpawnEmitterFX] NiagaraSystemAsset NULL"));
		return;
	}

	NiagaraFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
		NiagaraSystemAsset,   // use your UPROPERTY
		RootComponent,
		NAME_None,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::KeepRelativeOffset,
		true, true
	);
}

void ASimulationActor::OnStepReceived(FModelData InModelData) {
}

void ASimulationActor::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("[ASimulationActor::BeginPlay]"));
	UE_LOG(LogTemp, Log, TEXT("[ASimulationActor::BeginPlay] Calling SpawnEmitterFX"));
	SpawnEmitterFX();
}

void ASimulationActor::EndPlay(EEndPlayReason::Type EndPlayReason) {

	if (ModelObj) {
		ModelObj->RemoveFromRoot();
		ModelObj->MarkAsGarbage();
		ModelObj->Stop();
		ModelObj = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ASimulationActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}