// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplicateVariableActor.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AReplicateVariableActor::AReplicateVariableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultParticle((TEXT("ParticleSystem'/Game/Blueprints/P_Fire.P_Fire'")));
	if(DefaultParticle.Succeeded())
	{
		ParticleSystemComponent->Template = DefaultParticle.Object;
		ParticleSystemComponent->SetRelativeLocation(FVector(0.f,0.f,0.f));
	}

	RootComponent = ParticleSystemComponent;

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	TextRenderComponent->SetText(TEXT("10"));
	TextRenderComponent->SetupAttachment(RootComponent);
	TextRenderComponent->SetRelativeLocation(FVector(0.f,0.f,200.f));
	TextRenderComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TextRenderComponent->SetXScale(4.f);
	TextRenderComponent->SetYScale(4.f);
	TextRenderComponent->SetTextRenderColor(FColor::Black);
}

// Called when the game starts or when spawned
void AReplicateVariableActor::BeginPlay()
{
	Super::BeginPlay();


	if(Role == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(fTimerHandle,this,&AReplicateVariableActor::UpdateTimer,1.f,true);
	}
	
}

// Called every frame
void AReplicateVariableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString message = FString::Printf(TEXT("%.0f"), CountDownTimer);
	TextRenderComponent->SetText(message);

}

void AReplicateVariableActor::UpdateTimer()
{
	if(CountDownTimer > 0.f)
	{
		CountDownTimer--;
	}
}

void AReplicateVariableActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health
	DOREPLIFETIME(AReplicateVariableActor,CountDownTimer);
}

