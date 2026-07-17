#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetManager.generated.h"

UCLASS()
class FLOWPROTOTYPE_API ATargetManager : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<AActor*> VisibleTargets;

    UFUNCTION(BlueprintCallable)
    void AddTarget(AActor* Target);

    UFUNCTION(BlueprintCallable)
    void RemoveTarget(AActor* Target);

    UFUNCTION(BlueprintCallable)
    AActor* FindBestTarget(APlayerController* PlayerController, APawn* PlayerPawn);
};
