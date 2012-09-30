/* Zachary Berry and Patrick Willett (berwil)
 * This program will create a deck object then create a linked list of 52 cards in the deck. All of the cards
 * will then be printed with overloaded operators.
 */

#include <iostream>
#include "d_except.h"
#include "d_node.h"

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
	card(const int value, const int suit);
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

private:
	node<card> *front;
	node<card> *last;
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

// deck constructor
deck::deck()
{
	makeDeck();
}

// deck destructor
deck::~deck()
{
	delete front;
	delete last;
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
			}
			// When we have reached the end of our cards set our last pointer to the end of the deck.
			else
			{
				last = curr;
			}
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
	deck myDeck;

	try
	{
		myDeck.makeDeck();
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

	// Print out the contents of the deck.
	cout <<myDeck;

	system("pause");
	return 0;
}