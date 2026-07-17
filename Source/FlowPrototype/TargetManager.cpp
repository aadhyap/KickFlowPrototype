#include "TargetManager.h"

void ATargetManager::AddTarget(AActor* Target)
{
    if (IsValid(Target))
    {
        VisibleTargets.AddUnique(Target);
    }
}

void ATargetManager::RemoveTarget(AActor* Target)
{
    if (IsValid(Target))
    {
        VisibleTargets.Remove(Target);
    }
}

AActor* ATargetManager::FindBestTarget(APlayerController* PlayerController, APawn* PlayerPawn)
{
    if (!PlayerController || !PlayerPawn) return nullptr;

    int32 ViewX = 0;
    int32 ViewY = 0;
    PlayerController->GetViewportSize(ViewX, ViewY);

    const FVector2D ScreenCenter(ViewX * 0.5f, ViewY * 0.5f);

    AActor* BestTarget = nullptr;
    float BestScore = TNumericLimits<float>::Max();

    for (AActor* Target : VisibleTargets)
    {
        if (!IsValid(Target)) continue;

        FVector2D ScreenPosition;
        const bool bOnScreen = PlayerController->ProjectWorldLocationToScreen(
            Target->GetActorLocation(),
            ScreenPosition
        );

        if (!bOnScreen) continue;

        const float ScreenDistance = FVector2D::Distance(ScreenPosition, ScreenCenter);
        const float WorldDistance = FVector::Distance(PlayerPawn->GetActorLocation(), Target->GetActorLocation());

        const float Score = (ScreenDistance * 2.0f) + (WorldDistance * 0.2f);

        if (Score < BestScore)
        {
            BestScore = Score;
            BestTarget = Target;
        }
    }

    return BestTarget;
}
