#include <iostream>
#include "d_node.h"

using namespace std;

class card
{
public:
	card(){};
	card(const int x, const int y){suit = y; value = x;};  //card(int suit, int value) 
	int getSuit(){return suit;};
	int getValue(){return value;};
	void setSuit(const int x){suit = x;};
	void setValue(const int x){value = x;};

private:
	int suit; /* 1:club, 2:diamond  3:heart  4:spade */
	int value; /* jack:11, queen:12, king:13, ace: 14 */
};

class deck
{
public:
	deck();
	~deck(){};
	void makeDeck();
	void printDeck();

private:
	node<card> *front;
};

ostream& operator<< (ostream& os , card& a) {

		  os<<"Value: ";
		  if(a.getValue() == 14)
			  os<<"Ace";
		  else if(a.getValue() == 13)
			  os<<"King";
		  else if(a.getValue() == 12)
			  os<<"Queen";
		  else if(a.getValue() == 11)
			  os<<"Jack";
		  else 
			  os<<a.getValue();

			  
		  cout<<" Suit: ";
		  
		  switch(a.getSuit())
		  {
			  case (1):  //club
				  os<<"Club ";
				  break;
			  case(2):	//diomoind
				  os<<"Diamond ";
				  break;
			  case(3):	//heart
				  os<<"Heart ";
				  break;
			  case(4):	//spade
				  os<<"Spade ";
				  break;
		  }
		  os<<endl;
			

		  return os;
		}


deck::deck()
{
	front = NULL;
}

void deck::makeDeck()
{
	node<card> *curr = new node<card>;
	front = curr;

	for (int i = 2; i < 15; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			card tempCard(i, j);
			curr->nodeValue = tempCard;
			if (!(i == 14 && j == 4))
			{
				curr->next = new node<card>;
				curr = curr->next;
			}
		}
	}
}

void deck::printDeck()
{
	node<card> *traverse;
	traverse = front;

	while (traverse != NULL)
	{
		cout <<traverse->nodeValue;
		cout <<endl;

		traverse = traverse->next;
	}
}

int main()
{
	deck myDeck;

	myDeck.makeDeck();
	myDeck.printDeck();

	system("pause");
}