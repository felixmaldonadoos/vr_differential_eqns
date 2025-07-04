

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Core/ModelData.h"
#include "../Core/SimulationActor.h"
#include "../AizawaAttractor/AizawaAttractorModelObj.h"
#include "AizawaAttractorActor.generated.h"

UCLASS()
class DFQSOLVER_API AAizawaAttractorActor : public ASimulationActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAizawaAttractorActor() {};

protected:
	// Called when the game starts or when spawned

public:	
	// Called every frame

	UFUNCTION()
	virtual void OnStepReceived(FModelData InModelData) override {
		Super::OnStepReceived(InModelData);
		if (InModelData.frame % 10 != 0) return; // Skip rendering some steps
		UE_LOG(LogTemp, Log, TEXT("[AAizawaAttractorActor::OnStepReceived] Received: (%0.2f, %0.2f, %0.2f)"),
			InModelData.GetParam("px", -1),
			InModelData.GetParam("py", -1),
			InModelData.GetParam("pz", -1));
		// spawn here
		FVector PosTemp;
		PosTemp.X = InModelData.GetParam("px", -1);
		PosTemp.Y = InModelData.GetParam("py", -1);
		PosTemp.Z = InModelData.GetParam("pz", -1);
		PosTemp *= 1000; // scale up 
		PosTemp = GetActorLocation() + PosTemp;

		float Time = InModelData.t;
		uint8 Hue = static_cast<uint8>(FMath::Fmod(Time * 20.0f, 256));
		FLinearColor LinearHSVColor = FLinearColor::MakeFromHSV8(Hue, 255, 255);
		FColor SphereColor = LinearHSVColor.ToFColor(true); // 'true' = sRGB

		DrawDebugSphere(
			GetWorld(),
			PosTemp,
			2.5f,              // Radius
			3,                 // Segments
			SphereColor,
			true,             // Persistent lines?
			20.0f              // Lifetime in seconds
		);
	}

	void Start() override {
		UE_LOG(LogTemp, Log, TEXT("[ATestSimActor::Start] Setting up TestModelObj"));
		ModelObjClass = UAizawaAttractorModelObj::StaticClass(); // ✅ set specific subclass here
		Super::Start(); // initializes model and starts it 
	}
	
	virtual void BeginPlay() override {
		UE_LOG(LogTemp, Log, TEXT("[ATestSimActor::BeginPlay] Before super"))
		Super::BeginPlay();
		Start();
	}
	
	virtual void Tick(float DeltaTime) override {
		Super::Tick(DeltaTime);
	}
};
