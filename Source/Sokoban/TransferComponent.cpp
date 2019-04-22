// Fill out your copyright notice in the Description page of Project Settings.

#include "TransferComponent.h"
#include "SokobanPawn.h"
#include "Kismet/KismetSystemLibrary.h"

FVector UTransferComponent::directions[4] = {FVector(1.0f, 0.0f, 0.0f), FVector(-1.0f, 0.0f, 0.0f),
												 FVector(0.0f, 1.0f, 0.0f), FVector(0.0f, -1.0f, 0.0f)};

// Sets default values for this component's properties
UTransferComponent::UTransferComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	fDistance = 120.0f;
	fSpeed = 200.0f;
	vDirection = FVector::ZeroVector;
	vtarget = FVector::ZeroVector;
	bAutoActivate = false;
	bHasTarget = false;
	bHasPower = false;
	bCanMoveWithoutFloor = false;
	bCanMove = true;
}


// Called when the game starts
void UTransferComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor *Owner = GetOwner();
	if (Owner) {
		vPreviousPosition = Owner->GetActorLocation();
	}
}


// Called every frame
void UTransferComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor *Owner = GetOwner();
	if (Owner && bHasTarget) {
		FVector OwnerLocation = Owner->GetActorLocation();
		FVector distance = vtarget - OwnerLocation;
		if (!distance.IsNearlyZero()) {
			FVector NewLocation = FMath::VInterpConstantTo(OwnerLocation, vtarget, DeltaTime, fSpeed);
			Owner->SetActorLocation(NewLocation);
			if (!checkFloor(vDirection))
				transferBack();
		}
		else {
			Owner->SetActorLocation(vtarget);
			Deactivate();
		}
	}
}

int UTransferComponent::NumBlockedDirections()
{
	int res = 0;
	if (checkDirection(directions[0]) || checkDirection(directions[1]))
		res += 1;
	if (checkDirection(directions[2]) || checkDirection(directions[3]))
		res += 1;
	return res;
}

void UTransferComponent::SetDistance(float distance)
{
	this->fDistance = distance;
}

void UTransferComponent::SetSpeed(float speed)
{
	this->fSpeed = speed;
}

void UTransferComponent::SetDirection(FVector direction)
{
	direction.Normalize();
	this->vDirection = direction;
}

void UTransferComponent::setTarget()
{
	if (!vDirection.IsZero()) {
		FVector Location = GetOwner()->GetActorLocation();
		FVector Destination = vDirection * fDistance;
		vtarget = Location + Destination;
	}
}

bool UTransferComponent::checkDirectionBlocked(FVector direction)
{
	AActor *Owner = GetOwner();
	if (Owner)
	{
		FVector Start = Owner->GetActorLocation();
		direction.Normalize();
		FVector End = Start + direction * 150.f;
		FHitResult HitOut;
		TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
		TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		if (!UKismetSystemLibrary::LineTraceSingleForObjects(Owner, Start, End, TraceObjects, false, TArray<AActor*>(), EDrawDebugTrace::None, HitOut, true))
			return false;
		if (Cast<ASokobanPawn>(HitOut.GetActor()))
			return false;
	}
	return true;
}

bool UTransferComponent::checkFloor(FVector direction)
{
	if (bCanMoveWithoutFloor)
		return true;
	return checkDirectionBlocked(direction + FVector(0.0f, 0.0f, -10.0f));
}

bool UTransferComponent::checkDirection(FVector const direction)
{
	FVector d = direction;
	d *= 15;
	if (!checkFloor(d))
		return true;
	d = direction;
	if (checkDirectionBlocked(d))
		return true;
	return false;
}

void UTransferComponent::Activate(bool bReset)
{
	if (!bReset || vDirection.IsZero())
		return;

	bHasTarget = true;
	Super::Activate(bReset);
	setTarget();
}

void UTransferComponent::Deactivate()
{
	Super::Deactivate();
	bHasTarget = false;
	vDirection = FVector::ZeroVector;
}

void UTransferComponent::TransferActor(FVector direction)
{
	if (!bCanMove)
		return;
	AActor *Owner = GetOwner();
	if (direction.IsNearlyZero() || bHasTarget || !Owner)
		return;
	vPreviousPosition = Owner->GetActorLocation();
	SetDirection(direction);
	Activate(!vDirection.IsZero());
}

void UTransferComponent::OnBeginOverlap(AActor *OtherActor)
{
	if ((OtherActor != NULL) && (OtherActor != GetOwner()))
	{
		UTransferComponent *transfer = Cast<UTransferComponent>(OtherActor->GetComponentByClass(UTransferComponent::StaticClass()));
		FVector direction = GetDirection();
		if (!transfer || (bHasTarget && transfer->bHasTarget &&
			(transfer->GetDirection() != direction)) ||
			(!bHasPower && bHasTarget && transfer->GetDirection() != direction && !transfer->bHasPower) ||
			bHasTarget && transfer->bHasTarget && transfer->GetDirection() != direction && transfer->vtarget == transfer->vPreviousPosition)
		{
			transferBack();
		}
		else
		{
			transfer->TransferActor(direction);
		}
	}
}

void UTransferComponent::OnEndOverlap(AActor *OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
}

void UTransferComponent::transferBack()
{
	if (vtarget == vPreviousPosition)
		return;
	vtarget = vPreviousPosition;
	SetDirection(vDirection * -1.0f);
}

void UTransferComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//throw std::logic_error("The method or operation is not implemented.");
	//check(0);
}

