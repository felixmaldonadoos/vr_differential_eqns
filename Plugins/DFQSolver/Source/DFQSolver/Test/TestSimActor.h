

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestModelObj.h"
#include "Math/Color.h"
#include "../Core/SimulationActor.h"
#include "TestSimActor.generated.h"

UCLASS()
class DFQSOLVER_API ATestSimActor : public ASimulationActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	ATestSimActor() {
		
	}
protected:

	void Start() override {
		UE_LOG(LogTemp, Log, TEXT("[ATestSimActor::Start] Setting up TestModelObj"));
		ModelObjClass = UTestModelObj::StaticClass(); // ✅ set specific subclass here
		Super::Start(); // initializes model and starts it 
	}

	UFUNCTION()
	virtual void OnStepReceived(FModelData InModelData) override {
		Super::OnStepReceived(InModelData);
		UE_LOG(LogTemp, Log, TEXT("[UTestModelObj::OnStepReceived] Received: (%0.2f, %0.2f, %0.2f)"),
			InModelData.GetParam("px", -1),
			InModelData.GetParam("py", -1),
			InModelData.GetParam("pz", -1))

		// spawn here 
		FVector PosTemp; 
		PosTemp.X = InModelData.GetParam("px", -1);
		PosTemp.Y = InModelData.GetParam("py", -1);
		PosTemp.Z = InModelData.GetParam("pz", -1);
		PosTemp *= 100; // scale up 
		PosTemp   = GetActorLocation() + PosTemp;


		float Time = InModelData.t;
		uint8 Hue = static_cast<uint8>(FMath::Fmod(Time * 20.0f, 256));
		// Generate color in HSV space
		FLinearColor LinearHSVColor = FLinearColor::MakeFromHSV8(Hue, 255, 255);
		// Convert to FColor (sRGB) for drawing
		FColor SphereColor = LinearHSVColor.ToFColor(true); // 'true' = sRGB

		DrawDebugSphere(
			GetWorld(),
			PosTemp,
			5.0f,              // Radius
			3,                 // Segments
			SphereColor,
			false,             // Persistent lines?
			20.0f              // Lifetime in seconds
		);
	}
	
	virtual void BeginPlay() override {
		UE_LOG(LogTemp, Log, TEXT("[ATestSimActor::BeginPlay] Before super"))
		Super::BeginPlay();

		Start();
	}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override {
		Super::Tick(DeltaTime);
	}
};