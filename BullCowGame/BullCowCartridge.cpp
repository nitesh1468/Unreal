// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWords.h"
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ProcessGuess(Input);    
}

bool UBullCowCartridge::IsogramCheck(const FString& Guess) const
{
    for (int32 i=0;i<Guess.Len();i++)
    {
        for (int32 j=i+1;j<Guess.Len();j++)
        {
            if (Guess[j]==Guess[i])
            {
                return false;
            }
        }
    }
    return true;
}

bool UBullCowCartridge::EqualityCheck(const FString& Guess)
{
    if (Guess.Len()!=HiddenWord.Len())
    {
        return false;
    }   
    for (int32 i=0;i<Guess.Len();i++)
    {
        if (Guess[i]!=HiddenWord[i])
        {
            return false;
        }
    }
    return true;
}

void UBullCowCartridge::SetupGame()
{
    ClearScreen();
    HiddenWord=GetValidWord();
    Lives=HiddenWord.Len()*2;
    bGameOver=false;
    PrintLine(TEXT("Welcome to Bull Cow Game!"));
    PrintLine(TEXT("Guess the %i letters word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives left,Start Guessing"), Lives);
}

void UBullCowCartridge::EndGame()
{
    bGameOver=true;
    PrintLine(TEXT("Press Enter to continue"));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else 
    {
        if (Lives>0)
        {
            if(Guess.Len()!=HiddenWord.Len())
            {
                PrintLine(TEXT("Try Again with %i letter word"), HiddenWord.Len());
                return;
            }
            if (EqualityCheck(Guess.ToLower()))
            {
                PrintLine(TEXT("You won"));
                EndGame();
            }
            else
            {
                if(IsogramCheck(Guess.ToLower()))
                {
                    BullCowCalc(Guess);
                    PrintLine(TEXT("Your last guess had %i bull and %i cow"), Bull, Cow);
                    PrintLine(TEXT("Guess Again! You have %i lives left"), --Lives);
                }
                else
                {
                    PrintLine("No Repeating letters, Guess Again");
                }
            }
        }
        else
        {
            PrintLine(TEXT("You Lost :("));
            PrintLine(TEXT("The Hidden word was %s"), *HiddenWord);
            EndGame();
        }
        
    }
}

FString UBullCowCartridge::GetValidWord() const
{
    int32 WordCount=Words.Num();
    int32 Index=FMath::RandRange(0,WordCount-1);
    while (true)
    {
        if (Words[Index].Len()>=4 && Words[Index].Len()<=7)
        {
            if (IsogramCheck(Words[Index]))
            {
                return Words[Index].ToLower();
            }
        }
        Index++;
        Index%=WordCount-1;
    }
    return TEXT("trap");
}

void UBullCowCartridge::BullCowCalc(const FString& Guess) 
{
    Bull=0;
    Cow=0;
    for(int32 i=0;i<HiddenWord.Len();i++)
    {
        for(int32 j=0;j<HiddenWord.Len();j++)
        {
            if(Guess[i]==HiddenWord[j])
            {
                if(i==j)
                {
                    Bull++;
                }
                else
                {
                    Cow++;    
                }
                break;
            }
        }
    }
}