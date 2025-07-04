// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Interface.h"
#include "DFQModelObject.h"
#include "ModelData.h"
#include "SolverInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class USolverInterface : public UInterface {
	GENERATED_BODY()
};

/* Actual Interface declaration. */
class ISolverInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Add interface function declarations here
	
	UFUNCTION()
	virtual bool Test() {
		UE_LOG(LogTemp, Log, TEXT("[ISolverInterface] Test"))
	};

	virtual void Step();
};