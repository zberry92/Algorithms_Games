/*
 * Zachary Berry and Patrick Willett (BerWil)
 * Project 1b
 * This project will simulate the game Mastermind. As of know it will ask the user for the length of the code
 * and the maximum number of digits. It will then have the user guess the code and print out the correct code
 * and the number of digits the user guessed correctly.
 */

#include <iostream>
#include <vector>
#include "d_random.h"
#include "d_except.h"

using namespace std;

/* Maximum quesses the user is allowed. */
const int max_guesses = 5;

/* code class to handle the secret code and the guesses. */
class code
{
public:
	code(int m, int n);
	void createCode();
	void makeGuess();
	void checkCorrect();
	void checkIncorrect(int guessedDigit);
	bool checkValue(int guess) const;
	bool printResult() const;
	vector<int> getCode() const;

private:
	vector<int> correctDigits;
	vector<int> guessedDigits;
	vector<int> incorrectGuesses;
	const int codeLength, maxDigitValue; 
	int totalCorrect, totalIncorrect;
};

/* mastermind class to run the game */
class mastermind
{
public:
	mastermind();
	mastermind(int m, int n);
	void playGame();
private:
	code game;
	const int length, maxDigit;
};

/* Global Functions - ostream operator overloading*/

/* Overload to print vectors. */
ostream &operator<< (ostream &out, const vector<int> vec)
{
	for (int i = 0; i < (int) vec.size(); i++)
	{
		cout <<vec[i] <<" ";
	}
	cout <<endl;
	return out;
}

/* Overload to print the secret code from code objects. */
ostream &operator<< (ostream &out, const code &myCode)
{
	cout <<myCode.getCode() <<endl;
	return out;
}

/* Mastermind class functions */
mastermind::mastermind()
	:length(10), maxDigit(10), game(maxDigit, length)
{
}

mastermind::mastermind(int m, int n)
	:length(n), maxDigit(m), game(maxDigit, length)
{
}

void mastermind::playGame()
{
	game.createCode();

	cout <<"The secret code is: ";
	cout <<game;

	for (int i = 0; i < max_guesses; i++)
	{
		game.makeGuess();
		game.checkCorrect();
		if (game.printResult())
		{
			break;
		}
	}
}

/* Code class functions */
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

void code::makeGuess()
{
	cout <<"Please insert " <<codeLength <<" digits:" <<endl;	
	
	/* Have the user input the specified number of digits. */
	for (int i = 0 ; i < codeLength; i++)
	{
		cout <<"Digit " <<(i + 1) <<": ";
		cin >>guessedDigits[i];
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
			/* Check to see if the incorrect digit is somewhere in the code. */
			checkIncorrect(guessedDigits[i]);
		}
	}

	totalCorrect = numCorrect;
}

void code::checkIncorrect(int guessedDigit)
{
	/* Check to see if the value has already been guess. */
	if (checkValue(guessedDigit))
	{
		/* Check code for the incorrect digit, if there is a match then resize the incorrectGuesses vector, */
		/* input the value and incrememnt the incorrect count. */
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

bool code::checkValue(int guess) const
{
	for (int i = 0; i < (int)incorrectGuesses.size(); i++)
	{
		if (guess == incorrectGuesses[i])
		{
			return false;
		}
	}

	return true;
}

bool code::printResult() const
{
	cout <<endl <<"Your results are [Correctly guessed | correct but in the wrong place]: " <<endl
		 <<"[" <<totalCorrect <<" | " <<totalIncorrect <<"]" <<endl;

	if (totalCorrect == codeLength)
	{
		cout <<"Congratulations! You guessed the code correctly!" <<endl;
		return true;
	}
	else
	{
		cout <<"You did not answer correctly!!!" <<endl;
		return false;
	}
}

vector<int> code::getCode() const
{
	return correctDigits;
}

int main()
{
	int length = 0, maxDigit = 0;

	cout <<"Welcome to Mastermind V2.0." <<endl <<"If you want to customize the length and maximum digit of your code,"
		 <<endl <<"enter numbers when prompted, if you want to use the default (10), just enter '0'." <<endl;
	
	cout <<"Please enter the length of your code: ";
	cin >>length;

	cout <<"Please enter the maximum digit you want in the code: ";
	cin >>maxDigit;

	if (length == 0 && maxDigit == 0)
	{
		mastermind outGame();
	}

	mastermind ourGame(maxDigit, length);

	ourGame.playGame();

	system("pause");
}
