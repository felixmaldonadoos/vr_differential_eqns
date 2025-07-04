#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Core/ModelData.h"
#include "../Core/DFQModelObject.h"
#include "AizawaAttractorModelObj.generated.h"

UCLASS()
class DFQSOLVER_API UAizawaAttractorModelObj : public UDFQModelObject {
	GENERATED_BODY()

public:

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;


public:

	virtual void Step() override {
		Super::Step();

		float dt = ModelData.GetParam("dt", 0.01f);

		// Parameters
		float a = ModelData.GetParam("a", 0.95f);
		float b = ModelData.GetParam("b", 0.7f);
		float c = ModelData.GetParam("c", 0.6f);
		float d = ModelData.GetParam("d", 3.5f);
		float e = ModelData.GetParam("e", 0.25f);
		float f = ModelData.GetParam("f", 0.1f);


		FVector P;
		P.X = ModelData.GetParam("px", 0.1f);
		P.Y = ModelData.GetParam("py", 0.1f);
		P.Z = ModelData.GetParam("pz", 0.1f);

		// Aizawa Equations
		float dx = (P.Z - b) * P.X - d * P.Y;
		float dy = d * P.X + (P.Z - b) * P.Y;
		float dz = c + a * P.Z - FMath::Pow(P.Z, 3) / 3.0f
			- (P.X * P.X + P.Y * P.Y) * (1 + e * P.Z)
			+ f * P.Z * FMath::Pow(P.X, 3);

		FVector dPos(dx, dy, dz);
		P += dPos * dt;
		
		ModelData.SetParam("px", P.X);
		ModelData.SetParam("py", P.Y);
		ModelData.SetParam("pz", P.Z);

		OnStep_Delegate.Broadcast(ModelData);
	}

	virtual void PostInitializeModelData() override {

		ModelData.SetParam("a", 0.95f);
		ModelData.SetParam("b", 0.7f);
		ModelData.SetParam("c", 0.6f);
		ModelData.SetParam("d", 3.5f);
		ModelData.SetParam("e", 0.25f);
		ModelData.SetParam("f", 0.1f);

		ModelData.SetParam("px", 0.1f);
		ModelData.SetParam("py", 0.0f);
		ModelData.SetParam("pz", 0.0f);

		Super::PostInitializeModelData();
	}

	virtual void Start() override {

		Super::Start(); // creates modelobj, adds to root, initializes model (only if data is initialized)
		//InitializeModelData(0.05);
		UE_LOG(LogTemp, Log, TEXT("[AizawaAttractorModelObj::Start] Start"));
	};
};