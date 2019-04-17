// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseSokobanActor.h"

// Sets default values
ABaseSokobanActor::ABaseSokobanActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSokobanActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseSokobanActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseSokobanActor::CPPConstruction()
{
	FTransform t = GetTransform();
	FVector NewLocation = t.GetLocation();
	float Speed = 120.0f;
	NewLocation.X = FMath::RoundToInt(NewLocation.X / Speed) * Speed;
	NewLocation.Y = FMath::RoundToInt(NewLocation.Y / Speed) * Speed;
	t.SetLocation(NewLocation);
	SetActorTransform(t);
}

void ABaseSokobanActor::OnConstruction(const FTransform& Transform)
{
	CPPConstruction();
}

