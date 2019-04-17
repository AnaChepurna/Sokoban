// Fill out your copyright notice in the Description page of Project Settings.

#include "SokobanPlayerController.h"

void ASokobanPlayerController::MoveForward()
{
	MoveVector(FVector(1.0f, 0.0f, 0.0f));
}

void ASokobanPlayerController::MoveBackward()
{
	MoveVector(FVector(-1.0f, 0.0f, 0.0f));
}

void ASokobanPlayerController::MoveRight()
{
	MoveVector(FVector(0.0f, 1.0f, 0.0f));
}

void ASokobanPlayerController::MoveLeft()
{
	MoveVector(FVector(0.0f, -1.0f, 0.0f));
}

void ASokobanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("MoveForward", IE_Pressed, this, &ASokobanPlayerController::MoveForward);
		InputComponent->BindAction("MoveBackward", IE_Pressed, this, &ASokobanPlayerController::MoveBackward);
		InputComponent->BindAction("MoveRight", IE_Pressed, this, &ASokobanPlayerController::MoveRight);
		InputComponent->BindAction("MoveLeft", IE_Pressed, this, &ASokobanPlayerController::MoveLeft);
	}
}

void ASokobanPlayerController::MoveVector(FVector vector)
{
	APawn *Owner = GetPawn();
	if (Owner) {
		UTransferComponent *transfer = Cast<UTransferComponent>(Owner->GetComponentByClass(UTransferComponent::StaticClass()));
		if (NULL != transfer)
		{
			transfer->TransferActor(vector);
		}
	}
}
