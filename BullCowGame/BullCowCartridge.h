// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives, Bull, Cow;
	bool bGameOver;
	bool IsogramCheck(const FString& Guess) const;
	bool EqualityCheck(const FString& Guess);
	void EndGame();
	void ProcessGuess(const FString &Guess);
	FString GetValidWord() const;
	void BullCowCalc(const FString& Guess);
};
