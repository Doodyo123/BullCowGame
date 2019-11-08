#include "FBullCowGame.h"
#include <time.h>
#include <iostream>
#include <algorithm>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame(){Reset();}

int32 FBullCowGame::GetMaxTries() const{return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

void FBullCowGame::Reset()
{
	system("cls");
	constexpr int32 MAX_TRIES = 20;
	MyMaxTries = MAX_TRIES;
	// initialize random seed
	srand(time(NULL));

	//Generate secret number between 0 and the length of hidden word list
	const FString HIDDEN_WORDS[] = { "Derick","crazy", "laugh" };

	int32 RandomNumber = rand() % sizeof(HIDDEN_WORDS) / sizeof(HIDDEN_WORDS[0]);
	MyHiddenWord = HIDDEN_WORDS[RandomNumber];
	MyHiddenWord = ConvertToLowerCase(MyHiddenWord);
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat 0 and 1 letter Guesses as isogram
	if (Guess.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;// setup our map
	for (auto Letter : Guess) // for all letters in Guess 
	{
		// if the letter is in the map
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess isn't an isogram, return an error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength())// if the guess length is wrong, return an error
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

EGuessStatus FBullCowGame::CheckAnswerValidity(FString Answer) const
{
	if (Answer[0] != 'y' && Answer[0] != 'n')
	{
		return EGuessStatus::Wrong_Input;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		// loop through all letters in the guess
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			// if the letters match
			if (Guess[MHWChar] == MyHiddenWord[GChar]) {
				if (MHWChar == GChar) {// if they match spots
					BullCowCount.Bulls++; //increment Bulls
				}
				else {
					BullCowCount.Cows++; //increment cows.
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

FString FBullCowGame::ConvertToLowerCase(FString Guess)
{
	for_each(Guess.begin(), Guess.end(), [](char& c) {
		c = ::tolower(c);
		});
	return Guess;
}