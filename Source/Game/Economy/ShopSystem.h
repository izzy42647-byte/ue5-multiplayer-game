// ShopSystem.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShopSystem.generated.h"

UENUM(BlueprintType)
enum class ECosmetics : uint8
{
	Skin_Commando = 0,
	Skin_Ghost = 1,
	Skin_Ninja = 2,
	Skin_Cyber = 3,
	Emote_Dance = 4,
	Emote_Wave = 5,
	WeaponSkin_Gold = 6,
	WeaponSkin_Diamond = 7
};

USTRUCT(BlueprintType)
struct FCosmetic
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	ECosmetics CosmeticID;

	UPROPERTY(BlueprintReadWrite)
	FString CosmeticName;

	UPROPERTY(BlueprintReadWrite)
	FString Description;

	UPROPERTY(BlueprintReadWrite)
	int32 Price;

	UPROPERTY(BlueprintReadWrite)
	bool bIsLimited;

	UPROPERTY(BlueprintReadWrite)
	FDateTime ExpirationDate;
};

USTRUCT(BlueprintType)
struct FPlayerInventory
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<ECosmetics> OwnedCosmetics;

	UPROPERTY(BlueprintReadWrite)
	int32 VBucks = 0; // In-game currency

	UPROPERTY(BlueprintReadWrite)
	int32 BattlePassLevel = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bHasActiveBattlePass = false;
};

UCLASS()
class MULTIPLAYERGAME_API AShopSystem : public AActor
{
	GENERATED_BODY()

public:
	AShopSystem();

	virtual void BeginPlay() override;

	// Shop Catalog
	UPROPERTY(BlueprintReadWrite, Category = "Shop")
	TArray<FCosmetic> ShopCatalog;

	UPROPERTY(BlueprintReadWrite, Category = "Shop")
	TArray<FCosmetic> DailyOffers;

	// Currencies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 VBucksPerDollar = 100; // Conversion rate

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void RefreshDailyOffers();

	UFUNCTION(BlueprintCallable, Category = "Shop")
	TArray<FCosmetic> GetFeaturedItems();

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void GetAllCosmetics(TArray<FCosmetic>& OutCosmetics);

	// Purchasing
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PurchaseCosmetic(APlayerState* Player, ECosmetics Cosmetic);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PurchaseBattlePass(APlayerState* Player);

	// Battle Pass
	UFUNCTION(BlueprintCallable, Category = "Battle Pass")
	void RewardBattlePassXP(APlayerState* Player, int32 XPAmount);

	UFUNCTION(BlueprintCallable, Category = "Battle Pass")
	void ClaimBattlePassReward(APlayerState* Player, int32 RewardLevel);

	// Player Inventory
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_GetPlayerInventory(APlayerState* Player, FPlayerInventory& OutInventory);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool PlayerOwnsCosmetic(APlayerState* Player, ECosmetics Cosmetic);

protected:
	UPROPERTY()
	TMap<APlayerState*, FPlayerInventory> PlayerInventories;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 DailyOffersCount = 3;

	void PopulateDailyOffers();
};
