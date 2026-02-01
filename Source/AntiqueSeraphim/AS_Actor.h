// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AS_Actor.generated.h"

UCLASS()
class ANTIQUESERAPHIM_API AAS_Actor : public AActor
{
	GENERATED_BODY()
	
public:	// Static & Override
	// Sets default values for this actor's properties
	AAS_Actor();

	virtual void OnConstruction(const FTransform& Transform) override;

protected: // Static & Override
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	 // Static & Override
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: // Functions

private: // Functions

	void SetMouthPosX(const int32& InMouthPosX);
	void SetMouthPosY(const int32& InMouthPosY);

	void SetMouthParam();

public: // Properties

	UPROPERTY(VisibleAnywhere, Setter)
	int32 MouthPosX = 0;
	UPROPERTY(VisibleAnywhere, Setter)
	int32 MouthPosY = 0;

protected: // Properties

	/// @brief Root mesh component for the actor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> RootSkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> HaloMeshComponent;


	/// @brief 헤일로 컴포넌트
	UPROPERTY(EditAnywhere, Category = "Halo")
	TObjectPtr<UStaticMesh> HaloMesh;
	/// @brief 헤일로가 따라다닐 수 있는 최대 거리
	UPROPERTY(EditAnywhere, Category = "Halo")
	float HaloIntervalDistance = 0.f;
	/// @brief 헤일로가 따라다니는 보간 속도
	UPROPERTY(EditAnywhere, Category = "Halo")
	float HaloFollowSpeed = 0.f;

private:
	FVector HaloLocalPosition = FVector();

};
