#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values intialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid,
	OK, 
	Not_Isogram, 
	Wrong_Length,
	Wrong_Input
};

class FBullCowGame
{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const; 
	EGuessStatus CheckAnswerValidity(FString) const;

	FString ConvertToLowerCase(FString);

	void Reset(); // TODO make a more rich return value

	//count bulls & cows, and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

// Please try and ignore this and focus on the interface above
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
};