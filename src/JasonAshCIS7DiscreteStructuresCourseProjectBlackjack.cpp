// Programmer: Jason Ash
// Team: I don't know Jack (solo team)
// CIS-7 Discrete Structures
// November 21, 2025
// Professor: Dr. Nguyen
/* Description:  A Blackjack game that continually updates the probability of the user and dealer either getting a 21 or going bust.
It just uses one deck of 52 standard cards and plays per casino rules.*/
/* Casino rules: Dealer must draw on 16 or less, and stand on 17 or more. If the player gets a Blackjack, it's an automatic win even if the dealer gets a Blackjack.
If the player has anything less than a pat 21 and the dealer has a pat Blackjack, the dealer automatically wins. Ties result in a push.
If the player's hand bust (even if the dealer hand bust) then the player automatically loses. Otherwise, the player's hand beat the dealer's hand then the player wins.
If the dealer's hand beats the players hand, then the dealer wins.*/
// Inputs: The player can choose whether to hit or stand, and whether or not to play again.
/* Outputs: The player's hand value, the dealer's hand value, the card names received as hits (if any), and updated probabilities of obtaining a 21 or busting on the next hit
(probabilities are not displayed if the player or dealer already has a 21 or has already went bust*/

// Preprocessor Directives: The next lines of code preceded with the pound/hash-tag symbol cause the contents of another file to be inserted into the program.
#include<iostream>

// This library allows the programmer to use rand and srand functions. cstdlib is also needed for the exit() function.
#include <cstdlib>

// This library allows us to retrieve the time for a seed for srand.
#include <ctime>

// The cctype library is needed for its tolower() member function to simplify programming a little bit so that I do not have to account for the user entering upper or lower case choices.
#include <cctype>

// The string library is needed since strings are not a native part of the C++ core language
#include<string>

// The iomanip library is needed to format cout to two decimal points of precision because anything past this could unintentionally intimidate the player.
#include<iomanip>

using namespace std;

// Function prototypes
// The shuffleDeck function receives in the deckArray and its number of elements, and populates each elements with a unique, random (or as random as can be obtained using srand and rand) card number.
void shuffleDeck(int[], const int);

// The displayCard function receives in an integer as a parameter and returns a string with the card name. (For example, "Ace of Spades")
string displayCard(int);

/* The talleyCards() function receives in array of integers that represents the player's or dealer's hand, a constant int that represents the size of the hand array, and the hand value so far
and adds up the value of that hand according to the rules of Blackjack (aces can be a 1 or 11) and returns an int representing the hand value.
An individual card's value is actually determined by the getCardValue() function that talleyCards calls. */
int talleyCards(int[], const int, int);

/* The getCardValue() function receives in an integer representing the card number of the current position being added to the value in the player's or dealer's hand
and the value of that hand so far (to handle aces) and returns the determined value of that card.*/
int getCardValue(int, int);

/* The calcProbabilities() function receives in the deck array, the array size, the deck position marker, the hand value, and a reference to the calculateBust variable
since functions can only return one value. Since the calcProbability21 and calculateProbabilityBust functions in my flowchart are nearly identical,
I decided to combine them into one function and use a reference variable since only one value can be returned.*/
double calcProbabilities(int[], const int, int, int, double &);

int main()
{
	const int HIGHEST_CARD_NUM = 52;
	const int LOWEST_CARD_NUM = 1;

	// Per my analysis (see Project Documentation), the maximum number of cards in a worse-case scenario to reach 21 is 11 cards: 1 + 1 + 1 + 1 + 2 + 2 + 2 + 2+ 3 + 3 + 3 = 21
	const int MAX_CARDS_REACH21 = 11;

	int deckArray[HIGHEST_CARD_NUM];
	int playerHand[MAX_CARDS_REACH21];
	int dealerHand[MAX_CARDS_REACH21];

	// The following statement with srand is included once to seed rand (James 39).
	srand(static_cast<unsigned>(time(nullptr)));

	/* The deckPositionMarker, playerHandMarker, and dealerHandMarker keep track of the next card position in their respective arrays so that a card being dealt or received as a hit
    can be inserted into the correct element.*/
	int 	deskPositionMarker,
		playerHandMarker,
		dealerHandMarker;

	/* The playAgainChoice is just 'y' or 'Y' to play another game of Blackjack or anything else ends the program, and the strategy choice is 'h' or 'H' for hit or anything else ends the player's
    turn.*/
	char 	playAgainChoice,
            strategyChoice;

	// The Booleans playerPatHand and dealerPatHand are used by my algorithm to determine if only the initial two cards dealt are the only ones in the player's and dealer's hands, respectively.
	bool 	playerPatHand,
		dealerPatHand;

	// The Booleans playerBlackjack and dealerBlackjack are used to determine if the either of them obtained a Blackjack.
	bool	playerBlackjack,
		dealerBlackjack;

	// The Booleans playerBust and dealerBust determine if the player or dealer has went bust, respectively.
	bool 	playerBust = false,
		dealerBust = false;

	// The playerHandValue and dealerHandValue integers hold the value of their current hands, respectively.
	int 	playerHandValue,
            dealerHandValue;

	// The doubles probability21 and probabilityBust store the probability that the player or dealer will obtain a 21 on the next hit or go bust, respectively.
    // The probability21 variable is not used by the program, so I commented it out.
	// double 	probability21 = 0;
	double 	probabilityBust = 0;

	// Format cout to only show two decimal places of precision with doubles and floating point values.
	cout << setprecision(2) << fixed << showpoint;

	cout << "This is a Blackjack program using one deck of a standard 52 card deck." << endl;
	cout << "It continually updates the probability of the user and dealer obtaining 21" << endl;
	cout << "or going bust after the initial first two cards and after each hit." << endl;

	do
	{
		// Set deskPositionMarker, playerPositionMarker, and dealerMarker to zero at the beginning of each game
		deskPositionMarker = 0;
		playerHandMarker = 0;
		dealerHandMarker = 0;

		// At the beginning of each game, the playerPatHand and dealerPatHand Booleans are set to true.
		playerPatHand = true;
		dealerPatHand = true;

		// Their initial values for playerBust and dealerBust are set to false at the beginning of each game so that the logic that happens when they go bust does not happen until then.
		playerBust = false;
		dealerBust = false;

		// The playerBlackjack and dealerBlackjack Booleans are set to false at the beginning of each game so that they do not interfere with my algorithm later on.
		playerBlackjack = false;
		dealerBlackjack = false;

		// Initialize the playerHandValue and dealerHandValue to zero at the start of every game.
		playerHandValue = 0;
        dealerHandValue = 0;

        //Strategy choice is initialized to 'h' to enter the player turn while loop (unless the player, dealer, or both have a pat Blackjack).
        strategyChoice = 'h';

		// This for loop initializes all of the elements of the deckArray to zero which indicates that no card is present.
		for(int deckInitializer = 0; deckInitializer < HIGHEST_CARD_NUM; deckInitializer++)
		{
			deckArray[deckInitializer] = 0;
		}

		// This for loop initializes all of the elements of the playerHand and dealerHand arrays to zero to make sure no cards are present to start out with.
		for(int handInitializer = 0; handInitializer < MAX_CARDS_REACH21; handInitializer++)
		{
			playerHand[handInitializer] = 0;
			dealerHand[handInitializer] = 0;
		}

		/* Call the shuffleDeck function to populate each element in the deckArray with a random integer between 1 and 52 which represent all of the cards in the deck.
		The shuffleDeck() function has the deckArray passed to it and the highest card number as an arguments.*/
		shuffleDeck(deckArray, HIGHEST_CARD_NUM);

		// Call displayCard within a cout statement to display the string name of the card being dealt. For example, "Jack of Diamonds".

		cout << "The player has been dealt: " << displayCard(deckArray[deskPositionMarker]) << endl;

		// Deal the first card in the deck to the player by copying the first element of the deckArray to the first element of the playerHand array.
		playerHand[playerHandMarker] = deckArray[deskPositionMarker];

		// Increment deck position marker.
		deskPositionMarker++;

		// Increment player hand position marker.
		playerHandMarker++;

		// Copy the second element of the deckArray to the first element of the dealerHand array. This is the dealer's hole card that won't be revealed until the player's turn is resolved.
		dealerHand[dealerHandMarker] = deckArray[deskPositionMarker];

		// Increment deck position marker.
		deskPositionMarker++;

		// Increment dealer hand position marker.
		dealerHandMarker++;

		// Deal the player and dealer one more card each for their initial two cards.
		cout << "The player has been dealt: " << displayCard(deckArray[deskPositionMarker]) << endl;

		playerHand[playerHandMarker] = deckArray[deskPositionMarker];

		deskPositionMarker++;

		playerHandMarker++;

		cout << "The dealer\'s up card is: " << displayCard(deckArray[deskPositionMarker]) << endl;

		dealerHand[dealerHandMarker] = deckArray[deskPositionMarker];

		deskPositionMarker++;

		dealerHandMarker++;

		/* Call the talleyCards() function which is passed in an array of integers, a constant int representing the size of the array, and the hand value so far as an arguments
        	and determines the hand value according to the rules of the game and assigns the returned value to playerHandValue.*/
		playerHandValue = talleyCards(playerHand, MAX_CARDS_REACH21, playerHandValue);

		// Check for instant win scenario by seeing if the player has a pat 21 (which is a Blackjack).
		// Unlike the flowchart, scoring is deferred until later.
		if((playerHandValue == 21) && (playerPatHand == true))
		{
			playerBlackjack = true;
			cout << "Player Blackjack!" << endl;
		}
		else
		{
			playerPatHand = false;
			playerBlackjack = false;
		}

		// Call the talleyCards() function with the dealerHand as an argument to determine the value of the dealer's hand.
		dealerHandValue = talleyCards(dealerHand, MAX_CARDS_REACH21, dealerHandValue);
		if((dealerHandValue == 21) && (dealerPatHand == true))
		{
			dealerBlackjack = true;
			cout << "Dealer Blackjack!" << endl;
		}
		else
		{
			dealerPatHand = false;
			dealerBlackjack = false;
		}

        // Player's turn ends once 21 has been obtained, if the player does not hit, or if the player goes bust.
        if(!playerBlackjack && !dealerBlackjack)
        {
            cout << "Player's turn:" << endl;
        }

		while(!playerBlackjack && !dealerBlackjack && (playerHandValue < 21) && !playerBust && (tolower(strategyChoice) == 'h'))
		{
			cout << "The player's hand value so far is: " << playerHandValue << "." << endl;

			/* Display the probability of the player obtaining 21 on the next hit by calling calcProbability21 which is passed the deckArray, array size, deckPositionMarker, and playerHand value
            as arguments, and returns a double that is multiplied by 100 for a percentage.*/
			cout << "The probability of the player obtaining 21 on the next hit is: " << (calcProbabilities(deckArray, HIGHEST_CARD_NUM, deskPositionMarker, playerHandValue, probabilityBust) * 100);
			cout << "%" << endl;

			// Display the probability of the player going bust on the next hit.
			cout << "The probability of the player going bust on the next hit is: " << (probabilityBust * 100) << "%" << endl;

			// Prompt and response for player hit
			cout << "Would you like to hit (h or H) or any other option to stand?" << endl;
			cin >> strategyChoice;

			// If the player hits,
			if(tolower(strategyChoice) == 'h')
			{
				cout << "The player has been dealt: " << displayCard(deckArray[deskPositionMarker]) << endl;
				playerHand[playerHandMarker] = deckArray[deskPositionMarker];
				deskPositionMarker++;
				playerHandMarker++;
				playerHandValue = talleyCards(playerHand, MAX_CARDS_REACH21, playerHandValue);
			}

			if(playerHandValue > 21)
			{
				playerBust = true;
			}
		} // end player's turn while loop

		// Dealer's turn. If the dealer does not have a Blackjack, and the dealer's hand is less than 17, and the dealer had not yet went bust, then the dealer automatically draws a hit card.
		cout << "The dealer\'s hole card is: " << displayCard(dealerHand[0]) << endl;
		if(!playerBlackjack && !dealerBlackjack)
        {
            cout << "Dealer's turn:" << endl;
        }

		while(!dealerBlackjack && (dealerHandValue < 17) && !dealerBust)
		{
			cout << "The dealer's hand value so far is: " << dealerHandValue << "." << endl;
			cout << "The probability of the dealer obtaining 21 on the next hit is: " << (calcProbabilities(deckArray, HIGHEST_CARD_NUM, deskPositionMarker, dealerHandValue, probabilityBust) * 100);
			cout << "%" << endl;
			cout << "The probability of the dealer going bust on the next hit is: " << (probabilityBust * 100) << "%" << endl;
			cout << "The dealer has been dealt: " << displayCard(deckArray[deskPositionMarker]) << endl;
			dealerHand[dealerHandMarker] = deckArray[deskPositionMarker];
			deskPositionMarker++;
			dealerHandMarker++;
			dealerHandValue = talleyCards(dealerHand, MAX_CARDS_REACH21, dealerHandValue);
			if(dealerHandValue > 21)
			{
				dealerBust = true;
			}
            if((dealerHandValue >= 17) && (dealerHandValue <= 21))
            {
                    cout << "The dealer has a hand value of " << dealerHandValue << " and is going to stand" << endl;
            }
		} // end dealer's turn while loop

		// Scoring
		if(playerBlackjack && !dealerBlackjack)
		{
			cout << "Player won 1.5x the bet amount!" << endl;
		}
		if(playerBlackjack && dealerBlackjack)
		{
			cout << "Both the player and dealer got a Blackjack. Player receives 2.5x the bet amount!" << endl;
		}
		if(dealerBlackjack && !playerBlackjack)
		{
			cout << "Dealer wins!" << endl;
		}
		if(playerBust)
		{
			cout << "The player has went bust and loses this game." << endl;
		}
		if(dealerBust && !playerBust)
		{
			cout << "The dealer has went bust, but the player did not. Therefore, the player wins by default." << endl;
		}
		if(dealerBust && playerBust)
		{
			cout << "Although the dealer has went bust, the player also went bust. Therefore, the player still loses this game." << endl;
		}
		if((playerHandValue > dealerHandValue) && !playerBust && !dealerBust)
		{
			cout << "The player\'s hand value of " << playerHandValue << " beats the dealer hand value of " << dealerHandValue << ". Player wins." << endl;
		}
		if((playerHandValue < dealerHandValue) && !playerBust && !dealerBust)
		{
			cout << "The dealer\'s hand value of " << dealerHandValue << " beats the player\'s hand value of " << playerHandValue << ". Player loses this game." << endl;
		}
		if((playerHandValue == dealerHandValue) && !playerBust && !dealerBust && !playerBlackjack & !dealerBlackjack)
		{
			cout << "The player\'s hand value of " << playerHandValue << " and the dealer\'s hand value of " << dealerHandValue << " are the same. The outcome is a push (tie). ";
            cout << "Player\'s bet is refunded." << endl;
		}
		// End scoring

		// Prompt and response for player's choice to play again or not.
		cout << "Would you like to play again? (y or Y)" << endl;
		cin >> playAgainChoice;
	} while(tolower(playAgainChoice) == 'y'); // end do-while

	cout << "Thank you for playing!" << endl;

	return 0;
} // end main

/* The void shuffleDeck function takes in the deckArray and the highest card number (which is the number of cards in a deck) as a parameters and populates each element with a unique, random integer
between 1 and 52 to represent all of the cards in the deck.*/
void shuffleDeck(int unsuffledDeckArray[], const int MAX_NUM_CARDS)
{
	// int randCard holds the current random card within the do-while loop below.
	int randCard;

	// Set the tempDeckPositionMarker to zero to start at the beginning of the unshuffledDeckArray. deckIndex took the place of tempDeckPositionMarker from my flowchart in the for loop below.
	// tempDeckPositionMarker = 0;

	/* For each pass through the outer for loop, a random card is generated, then an inner for loop checks to see if that card is already present within the array up to the deckIndex position.
	If the card is already in the deck, then a new random card is chosen, and the deck is checked to see if it contains that card.
	If the deck does not have that card, then the unshuffledDeckArray at deckIndex element is assigned the value of that random card.
	This ensures that each card number inserted into the deckArray is random and unique (i.e. no duplicate cards).
	This is a very inefficient algorithm because it is O(n^2) for every card inserted into the deck.
    Having the inner loop only go up to the deckIndex position only slightly improves efficiency, but not in the leading term.
	The Boolean cardAlreadyPresent is necessary to flag whether or not it is already in the deck. If so, a new random card number is generated.
    If not, then the element in unsuffledDeckArray at position deckIndex is assigned the value 	of that random card number.
	Although this algorithm is inefficient, I decided to write it that way for simplicity of programming (since I'm still inexperienced with programming)
    and to more easily "wrap my head around" what it is doing*/

	bool cardAlreadyPresent;

	for(int deckIndex = 0; deckIndex < MAX_NUM_CARDS; deckIndex++)
	{
		do
		{
			// Assume to start with that the randomly generated card is not in the deck. This assumption will be less and less valid as cards are inserted from the beginning to the end of the deck.
			// Therefore, this algorithm really starts to experience inefficiency from the middle to the end of the shuffling process.

			cardAlreadyPresent = false;

			/* Generate a new pseudo-random number each pass through the do-while loop.
			Per Jason James, this formula generates a random number between the lowest and highest number including those numbers (James 36).*/

			randCard = rand()%((MAX_NUM_CARDS - 1) + 1) + 1;

			for(int deckCheck = 0; deckCheck <= deckIndex; deckCheck++)
			{
				if(unsuffledDeckArray[deckCheck] == randCard)
				{
					cardAlreadyPresent == true;
				} // end if
			} // end inner for loop

		} while(cardAlreadyPresent); // end do-while loop

		// The below if statement is probably not needed and redundant. So, it has been commented out.
		//if(!cardAlreadyPresent)
		// {
			unsuffledDeckArray[deckIndex] = randCard;
		// }

	} // end outer for loop
} // end void shuffleDeck() function

// The displayCard() function receives an integer as a parameter representing a unique card number, and it returns a string with the name of that card. For example, card number 51 is King of Clubs
string displayCard(int cardNumber)
{
	string tempCardName;

	/* The first scenario of the card number equaling 0 should never happen by the time this function is called. I just included it for error handling.
    Also, the final else is included for error handling.*/
	if(cardNumber == 0)
	{
		cout << "An error has occurred and that card position in the deck has not yet been shuffled and populated." << endl;
		exit(1);
	}
	else if((cardNumber >= 1) && (cardNumber <= 4))
	{
		tempCardName = "Ace of ";
	}
	else if((cardNumber >= 5) && (cardNumber <= 8))
	{
		tempCardName = "Deuce of ";
	}
	else if((cardNumber >= 9) && (cardNumber <= 12))
	{
		tempCardName = "Three of ";
	}
	else if((cardNumber >= 13) && (cardNumber <= 16))
	{
		tempCardName = "Four of ";
	}
	else if((cardNumber >= 17) && (cardNumber <= 20))
	{
		tempCardName = "Five of ";
	}
	else if((cardNumber >= 21) && (cardNumber <= 24))
	{
		tempCardName = "Six of ";
	}
	else if((cardNumber >= 25) && (cardNumber <= 28))
	{
		tempCardName = "Seven of ";
	}
	else if((cardNumber >= 29) && (cardNumber <= 32))
	{
		tempCardName = "Eight of ";
	}
	else if((cardNumber >= 33) && (cardNumber <= 36))
	{
		tempCardName = "Nine of ";
	}
	else if((cardNumber >= 37) && (cardNumber <= 40))
	{
		tempCardName = "Ten of ";
	}
	else if((cardNumber >= 41) && (cardNumber <= 44))
	{
		tempCardName = "Jack of ";
	}
	else if((cardNumber >= 45) && (cardNumber <= 48))
	{
		tempCardName = "Queen of ";
	}
	else if((cardNumber >= 49) && (cardNumber <= 52))
	{
		tempCardName = "King of ";
	}
	else
	{
		cout << "An error has occurred in determining the card name. This program will now exit." << endl;
		exit(1);
	}

	// Modulus division to determine the suit.
	cardNumber = cardNumber % 4;

	if(cardNumber == 0)
	{
		tempCardName = tempCardName + "Spades";
	}
	else if(cardNumber == 1)
	{
		tempCardName = tempCardName + "Hearts";
	}
	else if(cardNumber == 2)
	{
		tempCardName = tempCardName + "Diamonds";
	}
	else if(cardNumber == 3)
	{
		tempCardName = tempCardName + "Clubs";
	}
	else
	{
		cout << "An error has occurred in determining the card suit. This program will now exit." << endl;
		exit(1);
	}

	return tempCardName;

} // end dipslayCard() function

/* The talleyCards() function receives in an array of integers representing the player's or dealer's hand, the size of that array, and the value of the hand so far,
and it adds up that hand's value according to the rules of Blackjack. It then returns that value to the caller.
An individual card's value is actually determined by the getCardValue() function that talleyCards calls.*/
int talleyCards(int handArray[], const int MAX_HAND_SIZE, int handValueSoFar)
{
	int tempMarker = 0;
	int handValue = 0;

	while(tempMarker < MAX_HAND_SIZE)
	{
		// The efficiency of this function is improved slightly by checking if an element of the hand array is zero in which case there are no more cards in the hand from that position onwards.
		// An internal return statement such as this might not be considered structured programming, though.
		if(handArray[tempMarker] == 0)
		{
			return handValue;
		}
		handValue = handValue + getCardValue(handArray[tempMarker], handValueSoFar);
		tempMarker++;
	}
	return handValue;
} // end talleyCards()

/* The getCardValue() function is called by the talleyCards() function. The former receives in a card number that represents the card in the current position of the player's or dealer's hand
being added to the hand value. It also receives in the total hand value so far to handle aces (any hand of 10 or less, and an ace is considered an 11, otherwise, it is considered a one).*/
int getCardValue(int cardNumber, int handValueSoFar)
{
	int tempCardValue = 0;

	// The first if statement handles aces by assigning 11 to an ace if the hand value so far is <= 10. Otherwise, and ace counts as a one.
	if((cardNumber >= 1) && (cardNumber <= 4))
	{
		if(handValueSoFar <= 10)
		{
			tempCardValue = 11;
		}
		else
		{
			tempCardValue = 1;
		}
	}
	else if((cardNumber >= 5) && (cardNumber <= 8))
	{
		tempCardValue = 2;
	}
	else if((cardNumber >= 9) && (cardNumber <= 12))
	{
		tempCardValue = 3;
	}
	else if((cardNumber >= 13) && (cardNumber <= 16))
	{
		tempCardValue = 4;
	}
	else if((cardNumber >= 17) && (cardNumber <= 20))
	{
		tempCardValue = 5;
	}
	else if((cardNumber >= 21) && (cardNumber <= 24))
	{
		tempCardValue = 6;
	}
	else if((cardNumber >= 25) && (cardNumber <= 28))
	{
		tempCardValue = 7;
	}
	else if((cardNumber >= 29) && (cardNumber <= 32))
	{
		tempCardValue = 8;
	}
	else if((cardNumber >= 33) && (cardNumber <= 36))
	{
		tempCardValue = 9;
	}
	// After the 9's, 10 and all of the face cards are counted as a 10.
	else if((cardNumber >= 37) && (cardNumber <= 52))
	{
		tempCardValue = 10;
	}
	else
	{
		cout << "Something has gone wrong with getting a card value" << endl;
		exit(1);
	}

	return tempCardValue;
} // end getCardValue()

/* The calcProbabilities() function receives in the deck array, the deck position marker, the hand value, and a reference to the variable in main that will hold the probability of going bust.
The probability of obtaining 21 is returned.*/
double calcProbabilities(int remainingDeckArray[], const int DECK_SIZE, int deckPlaceMarker, int handValue, double &calcBust)
{
	// currentCardValue is used to hold the value of the current card value in the deck array element at tempDeckPosMarker position.
	int currentCardValue = 0;

	// The calculation for the probability of obtaining a 21 on the next hit will be: (the number of hands that result in a 21) / (total hands possible on the next hit).
	// Similarly, the calculation for the probability of busting on the next hit will be: (the number of hands that result in a bust) / (total hands possible on the next hit).
	int 	totalHands = 0,
		handsResult21 = 0,
		handsResultBust = 0;

    int tempHandValue = 0;

    // This for loop skips the initialization of the deckPlaceMarker since that was passed into the function as a parameter.
	for(; deckPlaceMarker < DECK_SIZE; deckPlaceMarker++)
	{
		tempHandValue = handValue;
		currentCardValue = getCardValue(remainingDeckArray[deckPlaceMarker], handValue);
		tempHandValue = tempHandValue + currentCardValue;
		if(tempHandValue == 21)
		{
			handsResult21++;
		}
		if(tempHandValue > 21)
		{
			handsResultBust++;
		}
		totalHands++;
	}

	calcBust = static_cast<double>(handsResultBust) / static_cast<double>(totalHands);
	return (static_cast<double>(handsResult21) / static_cast<double>(totalHands));
} // end calcProbabilities()


/*Works Cited:
James, Jason. Exploring C++ The Adventure Begins. Craieprogramming.Org, 2025, OER Series Exploring C++ The Adventure Begins, https://craieprogramming.org/OER/, Accessed 18 Feb. 2025. */
