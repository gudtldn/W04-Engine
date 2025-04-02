#include "Engine/Source/Runtime/CoreUObject/UObject/Object.h"

#include "ObjectFactory.h"
#include "UClass.h"
#include "UObjectArray.h"
#include "UObjectHash.h"


UClass* UObject::StaticClass()
{
    static UClass ClassInfo{
        TEXT("UObject"),
        sizeof(UObject),
        alignof(UObject),
        nullptr,
        []() -> UObject*
        {
            void* RawMemory = FPlatformMemory::Malloc<EAT_Object>(sizeof(UObject));
            ::new (RawMemory) UObject;
            return static_cast<UObject*>(RawMemory);
        }
    };
    return &ClassInfo;
}

UObject::UObject()
    : UUID(0)
    // TODO: Object를 생성할 때 직접 설정하기
    , InternalIndex(std::numeric_limits<uint32>::max())
    , NamePrivate("None")
{
}

bool UObject::IsA(const UClass* SomeBase) const
{
    const UClass* ThisClass = GetClass();
    return ThisClass->IsChildOf(SomeBase);
}

void UObject::MarkAsGarbage()
{
    GUObjectArray.MarkRemoveObject(this);
}

UObject* UObject::Duplicate()
{
    UClass* ClassInfo = GetClass();

    const uint32 Id = UEngineStatics::GenUUID();
    const FString Name = ClassInfo->GetName() + "_" + std::to_string(Id);

    void* RawMemory = FPlatformMemory::Malloc<EAT_Object>(ClassInfo->GetClassSize());
    std::memcpy(RawMemory, this, ClassInfo->GetClassSize());
    std::memset(static_cast<char*>(RawMemory)+8, 0, ClassInfo->GetClassSize()-8); // vtable 제외 나머지 메모리 초기화
    UObject* NewObject = static_cast<UObject*>(RawMemory);
    NewObject->ClassPrivate = ClassInfo;
    NewObject->NamePrivate = Name;
    NewObject->UUID = Id;

    GUObjectArray.AddObject(NewObject);
    return NewObject;
}
