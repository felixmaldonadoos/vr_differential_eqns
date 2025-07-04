

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DFQModelObject.h"
#include "ModelData.h"
#include "SolverInterface.h"
#include "SimulationActor.generated.h"


UCLASS()
class DFQSOLVER_API ASimulationActor : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulationActor();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStepDelegate OnStep_Delegate;

	UPROPERTY(EditAnywhere, Category = "Model")
	TSubclassOf<UDFQModelObject> ModelObjClass;
	
	UPROPERTY()
	TObjectPtr<UDFQModelObject> ModelObj;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float dt = 0.001; 

	virtual void OnStepReceived(FModelData InModelData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void Start(); 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
