// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_BillboardActor.h"
#include "Components/MaterialBillboardComponent.h"

// Sets default values
AAS_BillboardActor::AAS_BillboardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAS_BillboardActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	OnChangedProperty();
}

// Called when the game starts or when spawned
void AAS_BillboardActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAS_BillboardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAS_BillboardActor::SetBaseColor(const FVector4& InBaseColor)
{
	BaseColor = InBaseColor;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetVectorParameterValue(TEXT("BaseColor"), InBaseColor);
}

void AAS_BillboardActor::SetOpacity(const float& InOpacity)
{
	Opacity = InOpacity;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("Opacity"), InOpacity);
}

void AAS_BillboardActor::SetEmissive(const float& InEmissive)
{
	Emissive = InEmissive;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("Emissive"), InEmissive);
}

void AAS_BillboardActor::OnChangedProperty()
{
	if (RootComponent == nullptr)
	{
		return;
	}

	TArray<UMaterialInterface*> matArray;
	UMaterialBillboardComponent* mbbComp = Cast<UMaterialBillboardComponent>(RootComponent);
	if (mbbComp != nullptr)
	{
		mbbComp->GetUsedMaterials(matArray);
		if (matArray.IsValidIndex(0) == false)
		{
			return;
		}

		UMaterialInstanceDynamic* matInstanceDynamic = Cast<UMaterialInstanceDynamic>(matArray[0]);
		if (matInstanceDynamic == nullptr)
		{
			mbbComp->CreateDynamicMaterialInstance(0, nullptr);
		}
	}

	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("Emissive"), Emissive);
	materialInstanceDynamic->SetScalarParameterValue(TEXT("Opacity"), Opacity);
	materialInstanceDynamic->SetVectorParameterValue(TEXT("BaseColor"), BaseColor);
}


UMaterialInstanceDynamic* AAS_BillboardActor::GetMaterialInstanceDynamic()
{
	TArray<UMaterialInterface*> matArray;
	UMaterialBillboardComponent* mbbComp = Cast<UMaterialBillboardComponent>(RootComponent);
	if (mbbComp != nullptr)
	{
		mbbComp->GetUsedMaterials(matArray);
		if (matArray.IsValidIndex(0) == false)
		{
			return nullptr;
		}

		UMaterialInstanceDynamic* matInstanceDynamic = Cast<UMaterialInstanceDynamic>(matArray[0]);
		if (matInstanceDynamic != nullptr)
		{
			return matInstanceDynamic;
		}
	}

	return nullptr;
}

