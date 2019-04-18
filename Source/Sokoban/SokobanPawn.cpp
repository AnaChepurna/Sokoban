// Fill out your copyright notice in the Description page of Project Settings.

#include "SokobanPawn.h"

// Sets default values
ASokobanPawn::ASokobanPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trans = CreateDefaultSubobject<UTransferComponent>(TEXT("Transfer"));
	Trans->bHasPower = true;
	OnActorBeginOverlap.AddDynamic(this, &ASokobanPawn::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ASokobanPawn::OnOverlapEnd);
}

void ASokobanPawn::OnConstruction(const FTransform& Transform)
{
 	FTransform t = FTransform(Transform);
	FVector NewLocation = Transform.GetLocation();
	float Speed = 120.0f;
	if (Trans)
		Speed = Trans->GetDistance();
	NewLocation.X = FMath::RoundToInt(NewLocation.X / Speed) * Speed;
	NewLocation.Y = FMath::RoundToInt(NewLocation.Y / Speed) * Speed;
 	t.SetLocation(FVector(NewLocation.X, NewLocation.Y, 60.0f));
 	SetActorTransform(t);

	Super::OnConstruction(t);
}

// Called when the game starts or when spawned
void ASokobanPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASokobanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASokobanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void  ASokobanPawn::OnOverlapBegin(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if (Trans)
	{
		Trans->OnBeginOverlap(OtherActor);
	}
}

void  ASokobanPawn::OnOverlapEnd(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		Trans->OnEndOverlap(OtherActor);
	}
}



