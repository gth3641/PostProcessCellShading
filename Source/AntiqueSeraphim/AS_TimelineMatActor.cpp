// Fill out your copyright notice in the Description page of Project Settings.


#include "AS_TimelineMatActor.h"


// Sets default values
AAS_TimelineMatActor::AAS_TimelineMatActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAS_TimelineMatActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	OnChangedProperty();
}

// Called when the game starts or when spawned
void AAS_TimelineMatActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAS_TimelineMatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR
void AAS_TimelineMatActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	OnChangedProperty();
}
#endif

void AAS_TimelineMatActor::SetUseBaseTex(float InUseBaseTex)
{
	UseBaseTex = InUseBaseTex;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("UseBaseTex"), InUseBaseTex);
}

void AAS_TimelineMatActor::SetUseDecoTex(float InUseDecoTex)
{
	UseDecoTex = InUseDecoTex;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("UseSecondTex"), InUseDecoTex);
}

void AAS_TimelineMatActor::SetOpacity(float InOpacity)
{
	Opacity = InOpacity;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("Opacity"), InOpacity);
}

void AAS_TimelineMatActor::SetTimelineScale(float InTimelineScale)
{
	TimelineScale = InTimelineScale;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("TimelineScale"), InTimelineScale);
}

void AAS_TimelineMatActor::SetBaseTextureMul(float InBaseTextureMul)
{
	BaseTextureMul = InBaseTextureMul;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("BaseColor_Mul"), InBaseTextureMul);
}

void AAS_TimelineMatActor::SetTexColorMulValue(float InTexColorMulValue)
{
	TexColorMulValue = InTexColorMulValue;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("Tex_Color_Mul_Value"), InTexColorMulValue);
}

void AAS_TimelineMatActor::SetEmissiveValue(float InEmissiveValue)
{
	EmissiveValue = InEmissiveValue;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("EmissiveValue"), InEmissiveValue);
}

void AAS_TimelineMatActor::SetBaseColor(FVector4 InBaseColor)
{
	BaseColor = InBaseColor;
	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetVectorParameterValue(TEXT("BaseColor"), InBaseColor);
}

void AAS_TimelineMatActor::OnChangedProperty()
{
	if (RootComponent == nullptr)
	{
		return;
	}

	TArray<UMaterialInterface*> matArray;
	USkeletalMeshComponent* skmComp = Cast<USkeletalMeshComponent>(RootComponent);
	if (skmComp != nullptr)
	{
		matArray = skmComp->GetMaterials();
		if (matArray.IsValidIndex(0) == false)
		{
			return;
		}

		UMaterialInstanceDynamic* matInstanceDynamic = Cast<UMaterialInstanceDynamic>(matArray[0]);
		if (matInstanceDynamic == nullptr)
		{
			skmComp->CreateDynamicMaterialInstance(0, nullptr);
		}
	}

	UStaticMeshComponent* smComp = Cast<UStaticMeshComponent>(RootComponent);
	if (smComp != nullptr)
	{
		matArray = smComp->GetMaterials();
		if (matArray.IsValidIndex(0) == false)
		{
			return;
		}

		UMaterialInstanceDynamic* matInstanceDynamic = Cast<UMaterialInstanceDynamic>(matArray[0]);
		if (matInstanceDynamic == nullptr)
		{
			smComp->CreateDynamicMaterialInstance(0, nullptr);
		}
	}

	UMaterialInstanceDynamic* materialInstanceDynamic = GetMaterialInstanceDynamic();
	if (materialInstanceDynamic == nullptr)
	{
		return;
	}

	materialInstanceDynamic->SetScalarParameterValue(TEXT("UseSecondTex"), UseDecoTex);
	materialInstanceDynamic->SetScalarParameterValue(TEXT("Opacity"), Opacity);
	materialInstanceDynamic->SetScalarParameterValue(TEXT("TimelineScale"), TimelineScale);
	materialInstanceDynamic->SetScalarParameterValue(TEXT("BaseColor_Mul"), BaseTextureMul);
	materialInstanceDynamic->SetVectorParameterValue(TEXT("BaseColor"), BaseColor);
	materialInstanceDynamic->SetScalarParameterValue(TEXT("Tex_Color_Mul_Value"), TexColorMulValue);
	materialInstanceDynamic->SetScalarParameterValue(TEXT("EmissiveValue"), EmissiveValue);
	materialInstanceDynamic->SetScalarParameterValue(TEXT("UseBaseTex"), UseBaseTex);
}

UMaterialInstanceDynamic* AAS_TimelineMatActor::GetMaterialInstanceDynamic()
{
	TArray<UMaterialInterface*> matArray;
	USkeletalMeshComponent* skmComp = Cast<USkeletalMeshComponent>(RootComponent);
	if (skmComp != nullptr)
	{
		matArray = skmComp->GetMaterials();
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

	UStaticMeshComponent* smComp = Cast<UStaticMeshComponent>(RootComponent);
	if (smComp != nullptr)
	{
		matArray = smComp->GetMaterials();
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
