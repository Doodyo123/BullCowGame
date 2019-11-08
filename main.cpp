/* This is the console excecutable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is reponsible for all
user interaction. For game logic see the FBullCowGame class.
*/


#include <iostream>
#include <string>
#include <algorithm>
#include "FBullCowGame.h"

using FText = std::string;

void PlayGame();
void printIntro();
void printGameSumarry();
bool AskToPlayAgain();
FText GetValidGuess();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	do {
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

bool AskToPlayAgain()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	bool Value = true;
	FText Answer = "";

	do {
		std::cout << "\nWould you like to play again (y/n)?";
		std::getline(std::cin, Answer);

		Answer = BCGame.ConvertToLowerCase(Answer);
		Status = BCGame.CheckAnswerValidity(Answer);

		switch (Status)
		{
		case EGuessStatus::Wrong_Input:
			std::cout << "Please answer either yes or no. ";
			break;
		default:
			break;// assume the guess is valid
		}
		
	} while (Status != EGuessStatus::OK);

	if (Answer[0] == 'y') {
		Value = true;
	}
	else if (Answer[0] == 'n') {
		Value = false;
	}
	return Value;
}

void PrintGuess(FText Guess)
{
	std::cout << "Your guess: " << Guess;
	return;
}

// loop continually until user gets valid guess
FText GetValidGuess()	
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl;
		std::cout << "Try " << CurrentTry << ". Enter Your Guess:";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a  " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Word not an Isogram. Please input an isogram word";
			break;
		default:
			break;// assume the guess is valid
		}
	} while (Status != EGuessStatus::OK); // keepn looping until we get no errors

	return Guess;
}	

void PlayGame()
{	

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	int32 CurrentTry = BCGame.GetCurrentTry();
	printIntro();
	
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		Guess = BCGame.ConvertToLowerCase(Guess);

		// submit the valid guess and return bulls and cows
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}
	
	// TODO summarise game
	printGameSumarry();
	return;
}

void printIntro()
{
	// introduce the game
	const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH
		<< " letter isogram I'm thinking of?\n";
	return;
}

void printGameSumarry()
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME!\n";
	}
	return;
}
