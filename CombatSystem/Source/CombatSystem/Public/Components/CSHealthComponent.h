// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSHealthComponent.generated.h"

class ACSCharacter;
//class UProgressBar;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UCSHealthComponent*, HealthComp, float, CurrentHealth, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(CombatSystem), meta=(BlueprintSpawnableComponent) )
class COMBATSYSTEM_API UCSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSHealthComponent();

	UPROPERTY(EditAnywhere, Category = "HealthComponent")
	float HealthRestorePercentageOnAttack = 0.1f;

	UPROPERTY(EditAnywhere, Category = "HealthComponent")
	float StartingHealth;

	UPROPERTY(EditAnywhere, Category = "HealthComponent")
	float MaxHealth;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "HealthComponent")
	float HealthRecuperationPerSecond;

	

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	

	bool Invulnerable;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChanged;	

	ACSCharacter* Character;

	bool IsInvulnerable() const;
	
	UFUNCTION(BlueprintCallable)
	void SetInvulnerable(bool NewInvulnerable);

	float GetHealthPercentage(float Current, float Max);

	float GetCurrentHealth() const;
};
