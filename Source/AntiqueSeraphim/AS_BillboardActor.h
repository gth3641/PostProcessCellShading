// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AS_BillboardActor.generated.h"

UCLASS()
class ANTIQUESERAPHIM_API AAS_BillboardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAS_BillboardActor();

	virtual void OnConstruction(const FTransform& Transform) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

private:
	void SetBaseColor(const FVector4& InBaseColor);
	void SetOpacity(const float& InOpacity);
	void SetEmissive(const float& InEmissive);

	void OnChangedProperty();
	UMaterialInstanceDynamic* GetMaterialInstanceDynamic();

protected:
	
	UPROPERTY(EditAnywhere, Setter)
	FVector4 BaseColor = FVector4(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, Setter)
	float Opacity = 1.f;
	
	UPROPERTY(EditAnywhere, Setter)
	float Emissive = 1.f;
	
};
