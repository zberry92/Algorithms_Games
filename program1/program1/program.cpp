/*
 * Zachary Berry and Patrick Willett (BerWil)
 * Project 1b
 * This project will simulate the game Mastermind. As of know it will ask the user for the length of the code
 * and the maximum number of digits. It will then have the user guess the code and print out the correct code
 * and the number of digits the user guessed correctly and the numbers they guessed correctly but in the wrong
 * order.
 */

#include <iostream>
#include <vector>
#include "d_random.h"
#include "d_except.h"

using namespace std;

/* Maximum guesses the user is allowed until they lose the game. */
const int max_guesses = 5;

/* code class to handle creating the secret code and guesses against it. */
class code
{
public:
	code();
	code(int m, int n);
	void createCode();
	void makeGuess();
	void checkCorrect();
	int  checkIncorrect(int guessedDigit);
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

/* mastermind class to run the game from its code object. */
class mastermind
{
public:
	mastermind();
	mastermind(int m, int n);
	void playGame();
private:
	code game;
	const int length;
};

/* Global Functions - ostream operator overloading*/
/* Overload to print vectors with the '<<' operator. I.E. "cout << <vector>" will print all members of the vector */
ostream &operator<< (ostream &out, const vector<int> vec)
{
	for (int i = 0; i < (int) vec.size(); i++)
	{
		cout <<vec[i] <<" ";
	}
	cout <<endl;
	return out;
}

/* Overload to print the secret code vector member from code objects. */
/* I.E. "cout << <code object>" will use the vector print overloaded operator and print the secret code. */
ostream &operator<< (ostream &out, const code &myCode)
{
	cout <<myCode.getCode() <<endl;
	return out;
}

/* Mastermind class functions */
/* Default constructor */
mastermind::mastermind()
	:length(10), game(10, 10)
{
}

/* Constructor with m and n defined by the user */
mastermind::mastermind(int m, int n)
	:length(n), game(m, n)
{
}

/* Handles playing the mastermind game. Handles the number of attempts the user is allowed and runs the game steps */
/* from the game object in the mastermind class. */
void mastermind::playGame()
{
	game.createCode();

	cout <<"The secret code is: ";
	cout <<game;

	for (int i = 0; i < max_guesses; i++)
	{
		cout <<"This is attempt " <<(i + 1) <<" out of " <<max_guesses <<endl;
		game.makeGuess();
		game.checkCorrect();
		if (game.printResult())
		{
			break;
		}
	}
}

/* Code class functions */
/* Default constructor */
code::code()
	:codeLength(10), maxDigitValue(10)
{
	/* Resize the two vectors holding the guessed digits and correct ones. */
	correctDigits.resize(10);
	guessedDigits.resize(10);

	totalCorrect = 0;
	totalIncorrect = 0;
}

/* Constructor when user inputs m and n */
code::code(int m, int n)
	:codeLength(n), maxDigitValue(m)
{
	/* Resize the two vectors holding the guessed digits and correct ones. */
	correctDigits.resize(codeLength);
	guessedDigits.resize(codeLength);

	totalCorrect = 0;
	totalIncorrect = 0;
}

/* Creates the random secret code from a random object from the random class. */
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

/* Has the user input a guess to the secret code. The user inputs each digit sequentially. */
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

/* Once the code is inputted this function checks each digit against the secret code. If the numbers are correct */
/* then the vairable numCorrect is incremented. If the numbers are not equal, they are sent to the checkIncorrect */
/* function to check if the number was guessed in the past or is sent to a different location. */
void code::checkCorrect()
{
	int numCorrect = 0;
	int numIncorrect = 0;

	/* Check to each entry of the correct code against the guessed code. */
	for (int i = 0 ;  i < codeLength; i ++)
	{
		if (guessedDigits[i] == correctDigits[i])
		{
			numCorrect++;
		}
		else
		{
			/* Check to see if the incorrect digit is somewhere in the code or already guessed. */
			numIncorrect += checkIncorrect(guessedDigits[i]);
		}
	}

	totalCorrect = numCorrect;
	totalIncorrect = numIncorrect;
}

/* Checks to see if the digit has already been guessed with the checkValue function, if it has not been guessed */
/* it is then checked against every digit in the code. If it matches another digit it is added to the guessedDigit */
/* vector and the totalIncorrect variable is incremented. */
int code::checkIncorrect(int guessedDigit)
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
				return 1;
			}
		}
	}
	return 0;
}

/* Checks if a digit has already been included in the incorrectGuesses vector. */
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

/* Prints the results of each guess the user makes. If they guess all number correctly the game ends. */
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

/* Returns the private variable correctDigits from the code class to be used with the global overloaded object */
/* that prints the secret code from a code object. */
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

	/* If a default value is entered then call the default constructor of mastermind */
	if (length == 0 && maxDigit == 0)
	{
		mastermind ourGame;
		ourGame.playGame();
	}
	else
	{
		mastermind ourGame(maxDigit, length);
		ourGame.playGame();
	}

	system("pause");
}
