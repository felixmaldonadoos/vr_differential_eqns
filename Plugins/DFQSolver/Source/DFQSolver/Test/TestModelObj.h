

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Core/ModelData.h"
#include "../Core/DFQModelObject.h"
#include "TestModelObj.generated.h"

UCLASS()
class DFQSOLVER_API UTestModelObj : public UDFQModelObject {
	GENERATED_BODY()
	
public:	

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	FVector Pos = FVector::ZeroVector;

public:	

	virtual void Step() override {
		Super::Step();

		//float b = ModelData.GetParam("b", 0.208f); // thomas 
		float dt = ModelData.GetParam("dt", 0.001);
		float a = ModelData.GetParam("a",   1.4f); // halvorsen

		Pos.X = ModelData.GetParam("px", 0.0f);
		Pos.Y = ModelData.GetParam("py", 0.0f);
		Pos.Z = ModelData.GetParam("pz", 0.0f);

		/*float dx = FMath::Sin(Pos.Y) - b * Pos.X;
		float dy = FMath::Sin(Pos.Z) - b * Pos.Y;
		float dz = FMath::Sin(Pos.X) - b * Pos.Z;*/

		float dx = -a * Pos.X - 4 * Pos.Y - 4 * Pos.Z - FMath::Pow(Pos.Y, 2);
		float dy = -a * Pos.Y - 4 * Pos.Z - 4 * Pos.X - FMath::Pow(Pos.Z, 2);
		float dz = -a * Pos.Z - 4 * Pos.X - 4 * Pos.Y - FMath::Pow(Pos.X, 2);

		FVector dPos(dx, dy, dz);
		Pos += dPos * dt;

		ModelData.SetParam("px", Pos.X);
		ModelData.SetParam("py", Pos.Y);
		ModelData.SetParam("pz", Pos.Z);

		OnStep_Delegate.Broadcast(ModelData);
	};

	virtual void PostInitializeModelData() override {
		UE_LOG(LogTemp, Log, TEXT("[UTestModelObj::PostInitializeModelData]"));

		// 2. halvorsen
		ModelData.SetParam("a",   1.79);
		ModelData.SetParam("px",  2.24f*0.5);
		ModelData.SetParam("py",  3.83f*0.5);
		ModelData.SetParam("pz", -4.50f*0.5);

		Super::PostInitializeModelData();
	};

	virtual void Start() override {
		//InitializeModelData(0.05);

		Super::Start(); // creates modelobj, adds to root, initializes model (only if data is initialized)
		//InitializeModelData(0.05);
		UE_LOG(LogTemp, Log, TEXT("[UTestModelObj::Start] Start"));
	};
};