// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AS_TimelineMatActor.generated.h"

UCLASS()
class ANTIQUESERAPHIM_API AAS_TimelineMatActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAS_TimelineMatActor();

	virtual void OnConstruction(const FTransform& Transform) override;

public:

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private: // 
	void SetUseBaseTex(float InUseBaseTex);
	void SetUseDecoTex(float InUseDecoTex);
	void SetOpacity(float InOpacity);
	void SetTimelineScale(float InTimelineScale);
	void SetBaseTextureMul(float InBaseTextureMul);
	void SetTexColorMulValue(float InTexColorMulValue);
	void SetEmissiveValue(float InEmissiveValue);
	void SetBaseColor(FVector4 InBaseColor);

	void OnChangedProperty();

	UMaterialInstanceDynamic* GetMaterialInstanceDynamic();

public: // Properties
	UPROPERTY(EditAnywhere, Setter)
	float UseBaseTex = 0.0f;

	UPROPERTY(EditAnywhere, Setter)
	float UseDecoTex = 1.0f;

	UPROPERTY(EditAnywhere, Setter)
	float Opacity = 1.0f;

	UPROPERTY(EditAnywhere, Setter)
	float TimelineScale = 1.0f;

	UPROPERTY(EditAnywhere, Setter)
	float BaseTextureMul = 1.0f;

	UPROPERTY(EditAnywhere, Setter)
	float TexColorMulValue = 0.3f;

	UPROPERTY(EditAnywhere, Setter)
	float EmissiveValue = 0.1f;

	UPROPERTY(EditAnywhere, Setter)
	FVector4 BaseColor = FVector4();

};
