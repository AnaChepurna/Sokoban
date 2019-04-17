// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SokobanPawn.h"
#include "SokobanPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOKOBAN_API ASokobanPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();

	virtual void SetupInputComponent() override;

private:

	void MoveVector(FVector vector);

};
