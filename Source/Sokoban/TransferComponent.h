// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Array.h"
#include "BaseSokobanActor.h"
#include "TransferComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOKOBAN_API UTransferComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTransferComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY()
		float fSpeed;

	UPROPERTY()
		float fDistance;

	UPROPERTY()
		FVector vDirection;

	UPROPERTY()
		FVector vtarget;

	UPROPERTY()
		FVector vPreviousPosition;

	UPROPERTY()
		bool bHasTarget;

	UFUNCTION()
		void setTarget();

	UPROPERTY()
		bool bCanMoveWithoutFloor;

	UFUNCTION()
		bool checkFloor();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasPower;

	UFUNCTION(BlueprintCallable)
		void SetDistance(float distance);

	UFUNCTION(BlueprintCallable)
		void SetSpeed(float speed);

	UFUNCTION(BlueprintCallable)
		void SetDirection(FVector direction);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetSpeed() { return fSpeed; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetDistance() { return fDistance; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FVector GetDirection() { return vDirection; };

	virtual void Activate(bool bReset/* =false */) override;

	virtual void Deactivate() override;

	UFUNCTION(BlueprintCallable)
		void TransferActor(FVector direction);

	UFUNCTION(BlueprintCallable)
		void OnBeginOverlap(AActor *OtherActor);

	UFUNCTION(BlueprintCallable)
		void OnEndOverlap(AActor *OtherActor);

	UFUNCTION(BlueprintCallable)
		void transferBack();


};
