// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_Actor.h"


static FName HaloSocketName = TEXT("HaloSocket");

constexpr float UE_DF_MIN_PRECISION1 = 1.0f / (1 << 2);
// Max value of a float before it's precision is lower than UE_DF_MIN_PRECISION
// (there may be 1 more implicit bit available in the significant, but this works as a safe upper bound)
constexpr float UE_DF_FLOAT_MAX_VALUE1 = ((float)(1 << 23) * UE_DF_MIN_PRECISION1 - 1.0f);


// Sets default values
AAS_Actor::AAS_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RootSkeletalMeshComponent"));

	HaloMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HaloMeshComponent"));

	if (RootSkeletalMeshComponent == nullptr)
	{
		return;
	}

	RootComponent = RootSkeletalMeshComponent;
	if (HaloMeshComponent == nullptr)
	{
		return;
	}

	if (RootSkeletalMeshComponent->GetSocketByName(HaloSocketName) == nullptr)
	{
		return;
	}

	HaloMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FTransform haloSocketTrans = RootSkeletalMeshComponent->GetSocketTransform(HaloSocketName, ERelativeTransformSpace::RTS_Actor);
	if (haloSocketTrans.IsValid() == true)
	{
		return;
	}

	HaloMeshComponent->SetRelativeTransform(haloSocketTrans);
}

void AAS_Actor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (HaloMeshComponent == nullptr || RootSkeletalMeshComponent == nullptr)
	{
		return;
	}

	/// 머티리얼 설정.
	int32 eyeMouthIndex = RootSkeletalMeshComponent->GetMaterialIndex(TEXT("EyeMouth"));
	if (eyeMouthIndex != INDEX_NONE)
	{
		UMaterialInstanceDynamic* DynMID = RootSkeletalMeshComponent->CreateDynamicMaterialInstance(eyeMouthIndex, nullptr);
	}

	if (RootSkeletalMeshComponent->GetSocketByName(HaloSocketName) == nullptr)
	{
		return;
	}

	HaloMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FTransform haloSocketTrans = RootSkeletalMeshComponent->GetSocketTransform(HaloSocketName, ERelativeTransformSpace::RTS_Actor);
	if (haloSocketTrans.IsValid() == true)
	{
		return;
	}

	HaloMeshComponent->SetRelativeTransform(haloSocketTrans);
}


// Called when the game starts or when spawned
void AAS_Actor::BeginPlay()
{
	Super::BeginPlay();

	if (RootSkeletalMeshComponent == nullptr || RootSkeletalMeshComponent->GetSocketByName(HaloSocketName) == nullptr)
	{
		return;
	}

	if (HaloMeshComponent != nullptr)
	{
		HaloMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		FTransform haloSocketTrans = RootSkeletalMeshComponent->GetSocketTransform(HaloSocketName, ERelativeTransformSpace::RTS_Actor);
		if (haloSocketTrans.IsValid() == true)
		{
			return;
		}

		HaloMeshComponent->SetRelativeTransform(haloSocketTrans);
	}
}

void AAS_Actor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AAS_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HaloMeshComponent == nullptr || RootSkeletalMeshComponent == nullptr)
	{
		return;
	}

	FTransform haloSocketTrans = RootSkeletalMeshComponent->GetSocketTransform(HaloSocketName, ERelativeTransformSpace::RTS_Actor);
	FTransform curHaloTrans = HaloMeshComponent->GetRelativeTransform();
	if (haloSocketTrans.IsValid() == false)
	{
		return;
	}
	if (curHaloTrans.IsValid() == false)
	{
		HaloMeshComponent->SetRelativeTransform(haloSocketTrans);
		return;
	}

	FVector haloDistance = haloSocketTrans.GetLocation() - curHaloTrans.GetLocation();
	if (HaloIntervalDistance <= UE_KINDA_SMALL_NUMBER || HaloFollowSpeed <= UE_KINDA_SMALL_NUMBER)
	{
		HaloMeshComponent->SetRelativeTransform(haloSocketTrans);
		return;
	}
	float distance = haloDistance.Size();
	if (distance >= 500.f)
	{
		HaloMeshComponent->SetRelativeTransform(haloSocketTrans);
		return;
	}
	float distanceRatio = distance / HaloIntervalDistance;
	distanceRatio = distanceRatio * distanceRatio;
	distanceRatio += 1.f;
	distanceRatio = FMath::Clamp(distanceRatio, 0.f, 500.f);

	haloSocketTrans.SetLocation(FMath::Lerp(curHaloTrans.GetLocation(), haloSocketTrans.GetLocation(), DeltaTime * HaloFollowSpeed * distanceRatio));
	if (haloSocketTrans.IsValid() == false)
	{
		return;
	}
	HaloMeshComponent->SetRelativeTransform(haloSocketTrans);
}

void AAS_Actor::SetMouthPosX(const int32& InMouthPosX)
{
	MouthPosX = InMouthPosX;

	SetMouthParam();
}


void AAS_Actor::SetMouthPosY(const int32& InMouthPosY)
{
	MouthPosY = InMouthPosY;

	SetMouthParam();
}

void AAS_Actor::SetMouthParam()
{
	UMaterialInterface* eyeMouthInterface = RootSkeletalMeshComponent->GetMaterialByName(TEXT("EyeMouth"));
	if (eyeMouthInterface == nullptr)
	{
		return;
	}

	UMaterialInstanceDynamic* eyeMouthMatInstance = Cast<UMaterialInstanceDynamic>(eyeMouthInterface);
	if (eyeMouthMatInstance == nullptr)
	{
		return;
	}

	eyeMouthMatInstance->SetVectorParameterValue(TEXT("MouthIndex"), FVector4(MouthPosX, MouthPosY, 0, 0));
}
