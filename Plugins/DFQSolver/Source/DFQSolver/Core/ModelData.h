#pragma once
#include "CoreMinimal.h"
#include "ModelData.generated.h"

USTRUCT(BlueprintType)
struct FModelData
{
    GENERATED_BODY()

public:
    // Optional metadata
    FModelData() {
        frame = 0; 
        t = 0;
    }
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
    FString ModelName;

    // Dynamic parameter map (dictionary-style)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
    TMap<FString, float> Parameters;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
    int frame = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
    float t = 0;

    // Get a parameter value, or default if missing
    float GetParam(const FString& Key, float Default = 0.0f) const {
        if (const float* Found = Parameters.Find(Key)) {
            return *Found;
        }
        return Default;
    }

    /*
    * Usage:    ModelData.SetParam("b", 0.21f);
                ModelData.SetParam("dt", 0.015f);
    */
    void SetParam(const FString& Key, float Value) {
        Parameters.Add(Key, Value);
    }
};
