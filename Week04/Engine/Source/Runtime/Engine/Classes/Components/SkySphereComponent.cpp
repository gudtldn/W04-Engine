#include "SkySphereComponent.h"

#include "World.h"
#include "Engine/Source/Runtime/Core/Math/JungleMath.h"
#include "LevelEditor/SLevelEditor.h"
#include "PropertyEditor/ShowFlags.h"
#include "UnrealEd/EditorViewportClient.h"
#include "UnrealEd/PrimitiveBatch.h"
#include "UObject/Casts.h"


USkySphereComponent::USkySphereComponent()
{
    SetType(StaticClass()->GetName());
}

UObject* USkySphereComponent::Duplicate()
{
    ThisClass* DuplicatedObject = Cast<ThisClass>(Super::Duplicate());
    DuplicatedObject->UOffset = UOffset;
    DuplicatedObject->VOffset = VOffset;
    return DuplicatedObject;
}

void USkySphereComponent::InitializeComponent()
{
    Super::InitializeComponent();
}

void USkySphereComponent::TickComponent(float DeltaTime)
{
    UOffset += 0.005f;
    VOffset += 0.005f;
    Super::TickComponent(DeltaTime);
}