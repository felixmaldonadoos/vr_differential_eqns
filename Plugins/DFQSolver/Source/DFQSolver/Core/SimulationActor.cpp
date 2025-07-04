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

void ASimulationActor::OnStepReceived(FModelData InModelData) {
}

void ASimulationActor::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("[ASimulationActor::BeginPlay]"))
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