/*
 * Zachary Berry and Patrick Willett (BerWil)
 * Project 1a
 * This project will simulate the game Mastermind. As of know it will ask the user for the length of the code
 * and the maximum number of digits. It will then have the user guess the code and print out the correct code
 * and the number of digits the user guessed correctly.
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "d_random.h"

using namespace std;

class code
{
public:
	code(int m, int n);
	void createCode();
	void checkCorrect();
	void checkIncorrect(int guessedDigit);
	const bool checkValue(int guess);
	void printResult() const;
	void makeGuess();

private:
	vector<int> correctDigits;
	vector<int> guessedDigits;
	vector<int> incorrectGuesses;
	const int codeLength, maxDigitValue; 
	int totalCorrect, totalIncorrect;
};

code::code(int m, int n)
	:codeLength(n), maxDigitValue(m)
{
	/* Resize the two vectors holding the guessed digits and correct ones. */
	correctDigits.resize(codeLength);
	guessedDigits.resize(codeLength);

	totalCorrect = 0;
	totalIncorrect = 0;
}

void code::createCode()
{
	randomNumber rand;

	/* Create the code of random numbers based off of the length and digit restraints. */
	for (int i = 0; i < codeLength; i ++)
	{
		/* Passing in maxDigitValue + 1 because random(m) returns digits 0 <= val <= m-1. */
		correctDigits[i] = (int) rand.random(maxDigitValue + 1);   
	}
}

void code::checkCorrect()
{
	int numCorrect = 0;

	/* Check to each entry of the correct code against the guessed code. */
	for (int i = 0 ;  i < codeLength; i ++)
	{
		if (guessedDigits[i] == correctDigits[i])
		{
			numCorrect++;
		}
		else
		{
			checkIncorrect(guessedDigits[i]);
		}
	}

	totalCorrect = numCorrect;
}

void code::checkIncorrect(int guessedDigit)
{
	if (checkValue(guessedDigit))
	{
		for (int i = 0; i < codeLength; i++)
		{
			if (guessedDigit == correctDigits[i])
			{
				incorrectGuesses.resize(incorrectGuesses.size() + 1);
				incorrectGuesses[incorrectGuesses.size() - 1] = guessedDigit;
				totalIncorrect++;
				break;
			}
		}
	}
}

const bool code::checkValue(int guess)
{
	for (int i = 0; i < (int)incorrectGuesses.size(); i++)
	{
		if (guess = incorrectGuesses[i])
		{
			return false;
		}
	}

	return true;
}

void code::printResult() const
{
	/* Print the correct code. */
	cout <<"The correct code is: ";
	for (int i = 0; i < codeLength; i++)
	{
		cout <<correctDigits.at(i) <<" ";
	}

	cout <<endl <<"[" <<totalCorrect <<" | " <<totalIncorrect <<"]" <<endl;
}

void code::makeGuess()
{
	cout <<"Please insert " <<codeLength <<" digits:" <<endl;	
	
	/* Have the user input the specified number of digits. */
	for (int i = 0 ; i < codeLength; i++)
	{
		cout <<"Digit " <<(i + 1) <<": ";
		cin >>guessedDigits.at(i);
	}

}

int main()
{
	int length, maxDigit;

	cout <<"Welcome to Mastermind V1.0." <<endl <<"Please enter the length of your code: ";
	cin >>length;

	cout <<"Please enter the maximum digit you want in the code: ";
	cin >>maxDigit;

	/* Run three trials with the desired code length and maximum digit. */
	for (int i = 1; i < 4; i++)
	{
		code tempCode(maxDigit, length);
		cout <<"Trial " <<i <<", ";
		
		tempCode.createCode();
		tempCode.makeGuess();
		tempCode.checkCorrect();
		tempCode.printResult();
	}

	system("pause");
}
