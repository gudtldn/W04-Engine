#include "GizmoCircleComponent.h"

#include "World.h"
#include "Math/JungleMath.h"
#include "Actors/Player.h"
#include "UnrealEd/EditorViewportClient.h"
#include "LevelEditor/SLevelEditor.h"
#define DISC_RESOLUTION 128


UObject* UGizmoCircleComponent::Duplicate()
{
    ThisClass* DuplicatedObject = Cast<ThisClass>(Super::Duplicate());
    DuplicatedObject->inner = inner;
    return DuplicatedObject;
}

bool UGizmoCircleComponent::IntersectsRay(const FVector& rayOrigin, const FVector& rayDir, float& dist)
{
    if (rayDir.Y == 0) return false; // normal to normal vector of plane

    dist = -rayOrigin.Y / rayDir.Y;

    FVector intersectionPoint = rayOrigin + rayDir * dist;
    float intersectionToDiscCenterSquared = intersectionPoint.Length();

    return (inner * inner < intersectionToDiscCenterSquared && intersectionToDiscCenterSquared < 1);
}
