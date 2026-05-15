// WeaponBase.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	AssaultRifle = 0,
	Sniper = 1,
	SMG = 2,
	Shotgun = 3,
	Pistol = 4
};

UCLASS()
class MULTIPLAYERGAME_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Weapon Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MaxAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MagazineSize = 30;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Weapon")
	int32 CurrentAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float HeadshotMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Range = 5000.0f;

	// Firing
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Combat")
	void Server_Fire(FVector FireLocation, FVector FireDirection);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Combat")
	void Multicast_PlayFireEffects();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Reload();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	float LastFireTime = 0.0f;

	void DealDamage(FVector HitLocation, AActor* HitActor, bool bIsHeadshot);
};
