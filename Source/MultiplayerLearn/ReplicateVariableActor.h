// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicateVariableActor.generated.h"

/**
 * Um simples ator para testar replicação de variaveis
 */
UCLASS()
class MULTIPLAYERLEARN_API AReplicateVariableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReplicateVariableActor();

	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* TextRenderComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere,Replicated)
	float CountDownTimer = 10.f;

	FTimerHandle fTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdateTimer();

	/** Property replication **/
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
