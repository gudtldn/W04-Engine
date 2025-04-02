#include "StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"


AStaticMeshActor::AStaticMeshActor()
{
    StaticMeshComponent = AddComponent<UStaticMeshComponent>();     // 실제 렌더될 static mesh component 붙임
    RootComponent = StaticMeshComponent;
}

UObject* AStaticMeshActor::Duplicate()
{
    ThisClass* DuplicatedObject = Cast<ThisClass>(Super::Duplicate());
    DuplicatedObject->StaticMeshComponent = Cast<UStaticMeshComponent>(StaticMeshComponent->Duplicate());
    return DuplicatedObject;
}
