/* Zachary Berry and Patrick Willett (berwil)
 * Project 2-b
 * This program will create a deck object then create a linked list of 52 cards in the deck. All of the cards
 * will then be printed with overloaded operators.
 */

#include <iostream>
#include "d_except.h"
#include "d_node.h"
#include "d_random.h"

using namespace std;

// enum to define values for our suits.
enum card_suits_t {CLUB, 
				   HEART, 
				   DIAMOND, 
				   SPADE};

// Card class to handle the name and suit of a specific card.
class card
{
public:
	card();
	card(const card &card);
	card(const int value, const int suit);
	card& operator= (const card &rhs);
	const int getValue() {return cardValue;};
	const int getSuit() {return cardSuit;};
	void setValue(const int value);
	void setSuit(const int suit);

private:
	int cardValue; //For cards above 10: 11 - Jack, 12 - Queen, 13 - King, 14 - Ace
	int cardSuit;  //Values determined by enum card_suits_t 
};

// Deck class to make the deck and hold the memory positions of the firt and last card in the
// linked list of card objects.
class deck
{
public:
	deck();
	~deck();
	friend ostream& operator<< (ostream& ostr, deck& tempDeck);
	void makeDeck();
	card& dealCard();
	void replaceCard(const card tempCard);
	void shuffleDeck();

private:
	node<card> *front;
	node<card> *last;
	int deckSize;
	randomNumber rand;
};

// Overloaded operator to print the value and suit of the card object.
ostream& operator<< (ostream& ostr, card& tempCard) 
{
	//Print the value of the card.
	ostr<<"Your card is a : ";
	if (tempCard.getValue() == 14)
	{
		ostr <<"Ace";
	}
	else if(tempCard.getValue() == 13)
	{
		ostr <<"King";
	}
	else if(tempCard.getValue() == 12)
	{
		ostr <<"Queen";
	}
	else if(tempCard.getValue() == 11)
	{
		ostr <<"Jack";
	}
	else 
	{
		ostr<<tempCard.getValue();
	}		  
	
	//Print the suit of the card
	ostr<<" of ";
	switch(tempCard.getSuit())
	{
	case (CLUB):
		ostr <<"Clubs";
		break;
	case (HEART):
		ostr <<"Hearts";
		break;
	case (DIAMOND):
		ostr <<"Diamonds";
		break;
	case (SPADE):	
		ostr <<"Spades";
		break;
	}

	ostr <<endl;
	return ostr;
}

// Overloaded operator to print out an entire deck linked list pointed to by the deck object.
ostream& operator<< (ostream& ostr, deck& tempDeck)
{
	node<card> *traverse;
	traverse = tempDeck.front;

	while (traverse != NULL)
	{
		ostr <<traverse->nodeValue;
		ostr <<endl;

		traverse = traverse->next;
	}

	return ostr;
}


// newScore Function will compute the score the user has as they draw a card.
int newScore(int score, card tempCard)
{
	int value = tempCard.getValue();
	int suit = tempCard.getSuit();

	if (value == 14)
	{
		//Card is an ace.
		score += 10;
	}
	else if (value > 10 && value < 14)
	{
		//Card is Jack, Queen or King
		score += 5;
	}
	 
	else if (value == 7)
	{
		// Card is 7
		score = score/2;
	}
	else if (value >= 2 && value <= 6)
	{
		// Card is between 2 and 6.
		score = 0;
	}

	if(suit == HEART)
	{
		// Card is a heart. 
		score++;
	}

	return score;
}

// playFlip() function will play the Flip game.
void playFlip()
{
	int usrInput, score = 0;
	deck myDeck;
	card tempCard;

	// Explain the rules of the game to the user.
	cout <<"Welcome to Flip! The point of the game is to end the game with the most points. \n"
		 <<"You can keep taking cards until you decide to end the game. To take a card enter 1 below and 0 to end game. \n"
		 <<"The point system is as follows: \n"
		 <<"(a) receives 10 points for an ace, \n"
		 <<"(b) receives 5 points for a king, queen or jack, \n"
         <<"(c) receives 0 points for an 8, 9 or 10, \n"
		 <<"(d) loses half their points for a 7, \n"
		 <<"(e) loses all their points for a 2, 3, 4, 5 or 6, and \n"
		 <<"(f) receives 1 point extra, in addition to the above, for a heart. \n \n \n";

	// SHuffle the deck three times.
	for (int i = 0; i < 3; i++)
	{
	  	myDeck.shuffleDeck();
	}

	// Continue to play the game until the user enters a 0.
	while (true)
	{
		cout <<"Please enter choose whether you want to end the game of draw a card. (0 - end | 1 - draw): ";
		cin >> usrInput;

		if (usrInput == 0)
		{
			break;
		}

		// Deal a card from the top of the deck and compute the score.
		else if (usrInput == 1)
		{
			tempCard = myDeck.dealCard();
			cout <<tempCard <<endl;
			score = newScore(score, tempCard);
		}
		else
		{
			throw rangeError("playFlip() entered a number not in range.");
		}

		cout <<"Your Current Score: " <<score <<endl;
	}

	cout <<"Your final score of the game is: " <<score <<endl;
	return;
}

// deck constructor
deck::deck()
{
	deckSize = 0;
	makeDeck();
}

//deck destructor
deck::~deck()
{
	node<card> *curr;

	while (front != NULL)
	{
		curr = front;
		front = front->next;
		delete curr;
	}
}

// makeDeck() function will make a deck of 52 cards from 2 - Ace of each suit. Makes use of the node class. 
// The card object is made into a node via the template class and is constructed into a linked list.
void deck::makeDeck()
{
	node<card> *curr = new node<card>;
	if (curr == NULL)
	{
		throw memoryAllocationError("deck::makeDeck(): Memory not allocated correctly.");
	}
	front = curr;

	for (int i = 2; i < 15; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			card tempCard(i, j);
			curr->nodeValue = tempCard;
			// As long as we have not reached the end of the list keep creading nodes.
			if (!(i == 14 && j == 3)) 
			{
				curr->next = new node<card>;
				curr = curr->next;
				deckSize++;
			}
			else
			{
				last = curr;
			}
		}
	}
}

// dealCard() function will deal a card off the top of the deck and remove that card from the deck
card& deck::dealCard()
{
	node<card> *curr;

	if (deckSize == 0)
	{
		cout <<"There are no more cards in the deck!" <<endl;
		return curr->nodeValue;
	}

	//set current to the front and use it to find the value of the card we are dealing.
	curr = front;

	//Move the front pointer to the next card as we are deleting the top of the list.
	front = front->next;
	deckSize--;

	return curr->nodeValue;
}

// replaceCard() function will add a new card to the end of the deck;
void deck::replaceCard(const card tempCard)
{
	node<card> *curr;

	// Set curr to the last node in the list and create a new node after it.
	curr = last;
	curr->next = new node<card>(tempCard);
	if (curr->next == NULL)
	{
		throw memoryAllocationError("deck::replaceCard(): Memory not allocated correctly.");
	}
	deckSize++;
	
	//Set last to the new last node.
	last = curr->next;

	return;
}

// shuffleDeck() will shuffle the deck by taking the first node in the list and putting it somewhere random in the deck. 
void deck::shuffleDeck()
{
	node<card> *moveNode;
	node<card> *prev;
	int deckPosition;

	// Preform the switch 52 times.
	for (int i = 0; i < 52; i++)
	{
		// Readjust the front pointer.
		moveNode = front;
		prev = front;

		// Find a random position in the list and move to it.
		deckPosition = rand.random(deckSize - 1);
		if (deckPosition > 51)
		  continue;

		// 
		for (int i = 0; i < deckPosition; i++)
		{
			prev = prev->next;
		}

		if (moveNode != prev && prev != NULL && prev->next != NULL)
		{
			moveNode->next = prev->next;
			prev->next = moveNode;
			front = front->next;
		}
		// Any other case do not perform a move.
		else
		{
			continue;
		}

	}
}

// Default card constructor
card::card()
{
	cardValue = 0;
	cardSuit = 0;
}

// card constructor
card::card(const int value, const int suit)
{
	cardValue = value;
	cardSuit = suit;
}

//card copy constructor
card::card(const card &tempCard)
{
	cardValue = tempCard.cardValue;
	cardSuit = tempCard.cardSuit;
}

// Overloaded assignment operator for the card class.
card &card::operator= (const card &rhs)
{
	cardValue = rhs.cardValue;
	cardSuit = rhs.cardSuit;

	return *this;
}

void card::setValue(const int value)
{
	if (value < 2 && value > 14)
	{
		throw rangeError("card::setValue() entered a number not in range.");
	}
	else
	{
		cardValue = value;
	}
}

void card::setSuit(const int suit)
{
	if (suit < 2 && suit > 14)
	{
		throw rangeError("card::setValue() entered a number not in range.");
	}
	else
	{
		cardSuit = suit;
	}
}

int main()
{
	try
	{
		playFlip();	
	}

	// Catch any errors that may be thrown.
	catch (const rangeError& re)
	{
		cerr <<re.what() <<endl;
	}
	catch (const memoryAllocationError& re)
	{
		cerr <<re.what() <<endl;
	}

	return 0;
}
