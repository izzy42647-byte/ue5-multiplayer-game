// MultiplayerGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	WaitingForPlayers = 0,
	Loading = 1,
	Playing = 2,
	EndGame = 3
};

USTRUCT(BlueprintType)
struct FPlayerScore
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	APlayerController* Player;

	UPROPERTY(BlueprintReadWrite)
	int32 Kills = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 Deaths = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 Eliminations = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 TotalPoints = 0;
};

UCLASS()
class MULTIPLAYERGAME_API AMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMultiplayerGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Game Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	EGameState CurrentGameState = EGameState::WaitingForPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 MaxPlayers = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 MinPlayersToStart = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float WaitTimeBeforeStart = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float GameDuration = 1200.0f; // 20 minutes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float ShrinkZoneInterval = 60.0f;

	// Scoring
	UPROPERTY(BlueprintReadWrite, Category = "Scoring")
	TArray<FPlayerScore> PlayerScoreboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	int32 KillPoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	int32 HeadshotBonus = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	int32 AssistPoints = 25;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	int32 SurvivalBonus = 10;

	// Play zone (Battle Royale shrinking zone)
	UPROPERTY(BlueprintReadWrite, Category = "PlayZone")
	FVector PlayZoneCenter = FVector(0, 0, 0);

	UPROPERTY(BlueprintReadWrite, Category = "PlayZone")
	float PlayZoneRadius = 5000.0f;

	UPROPERTY(BlueprintReadWrite, Category = "PlayZone")
	float NextZoneRadius = 5000.0f;

	// Game functions
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame(APlayerController* Winner);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RecordKill(APlayerController* Killer, APlayerController* Victim, bool bIsHeadshot = false);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RecordAssist(APlayerController* Assister, APlayerController* Victim);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdateScoreboard();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ShrinkPlayZone();

	UFUNCTION(BlueprintCallable, Category = "Game")
	FPlayerScore GetPlayerScore(APlayerController* Player);

	UFUNCTION(BlueprintCallable, Category = "Game")
	TArray<FPlayerScore> GetSortedScoreboard();

	// Player management
	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetActivePlayerCount();

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool IsGameFull();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	UPROPERTY()
	APlayerController* CurrentWinner;

	float GameStartTime = 0.0f;
	float LastZoneShrinkTime = 0.0f;

	void UpdateGameState();
	void CheckGameEnd();
};
