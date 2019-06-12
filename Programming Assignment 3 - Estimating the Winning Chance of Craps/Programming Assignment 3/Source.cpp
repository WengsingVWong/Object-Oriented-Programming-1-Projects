// Author: Wengsing Wong
// Adapted from CIS 3100 Programming Assignment 3
// This program simulates playing craps. It asks the user how many games he/she would like to play and 
// simulates playing that number of games. It then displays the number of wins and calculates and 
// displays the winning percentage. Lastly, it asks the user if he/she would like to initiate another
// simulation. If yes, then the program repeats. If not, then the program terminates.

#include <iostream>
#include <iomanip> // For setprecision()
#include <cstdlib> // For srand() and rand()
#include <ctime> // For time()
#include <cctype> // For toupper()
using namespace std;

int getNumOfGames();
double playCraps(int);
void showWinStats(int, double);
char getPlayAgain();
void separateSims(int&);

int main()
{
	// numofGames will hold the number of games played during the simulation.
	// simNum will hold the simulation number.
	// winCount will hold the number of wins.
	// playAgain will hold a character that will be used to tell the program to play another set of games or terminate.
	int numofGames, simNum = 0;
	double winCount;
	char playAgain;

	do
	{
		// Output the heading, get the number of games, play that number of games, display the results,
		// and ask the user if he/she wants to run another simulation.
		simNum++;
		separateSims(simNum);
		numofGames = getNumOfGames();
		winCount = playCraps(numofGames);
		showWinStats(numofGames, winCount);
		playAgain = getPlayAgain();
		
	} while ((toupper(playAgain) == 'Y') && (toupper(playAgain) != 'N'));
	
	return 0;
}

// This function gets the number of games the user wants to play and returns it.
int getNumOfGames()
{
	// Local variable to hold the number of games the user wants to play
	int nOG;

	// Ask the user to input the number of games he/she wants to play
	cout << "How many games would you like to play? ";
	cin >> nOG;

	// User input validation loop; the number of games to play cannot be less than or equal to 0.
	while (nOG <= 0)
	{
		cout << "That is an invalid number of games. Please enter a valid number of games to play: ";
		cin >> nOG;
	}

	// Return the number of games to play.
	return nOG;
}

// This function simulates the playing of craps. It plays a number of games specified by the user (nOG).
double playCraps(int nOG)
{
	// die1 and die2 will hold the values rolled by the two dice.
	// diceSum will hold the sum of the two dice.
	// winValue will hold the sum of the two dice IF it is not 2, 3, 7, 11, or 12.
	// wC is a local variable that will hold the number of wins.
	// loseCount will hold the number of losses (this will not be shown to the user).
	int die1, die2, diceSum, winValue;
	double wC = 0;
	double loseCount = 0;

	// Seed the random number generator
	unsigned int seed = time(0);
	srand(seed);

	// Play the number of games specified by the user
	for (int i = 1; i <= nOG; i++)
	{
		// Roll the two dice and get their sum
		die1 = rand() % 6 + 1;
		die2 = rand() % 6 + 1;
		diceSum = die1 + die2;

		// If the sum of the dice is 2, 3, or 12 (craps), the user loses. 
		if ((diceSum == 2) || (diceSum == 3) || (diceSum == 12))
			loseCount += 1;

		// If the sum of the dice is 7 or 11 (natural), the user wins.
		else if ((diceSum == 7) || (diceSum == 11))
			wC += 1;

		// Otherwise, keep rolling until the sum is 7 or the same number again.
		else
		{
			winValue = diceSum;

			do
			{
				die1 = rand() % 6 + 1;
				die2 = rand() % 6 + 1;
				diceSum = die1 + die2;
			} while ((diceSum != 7) && (diceSum != winValue));

			// If the sum is 7, the user loses.
			if (diceSum == 7)
				loseCount += 1;

			// If the user rolls the same number again, the user wins. 
			else if (diceSum == winValue)
				wC += 1;
		}
	}
	
	// Return the number of wins
	return wC;
}

// This function displays the number of wins and the winning percentage for the simulation.
void showWinStats(int nOG, double wC)
{
	cout << "Number of Wins: " << wC << endl;
	cout << setprecision(4) << fixed << "Winning Chance Estimate: " << (wC / nOG) * 100 << "%\n";
}

// This function gets a character from the user indicating whether he/she wants to run another simulation.
char getPlayAgain()
{
	// Local variable to hold the character inputted by the user
	char pA;

	// Ask the user if he/she would like to run another simulation and get user input.
	cout << endl;
	cout << "If you would like to run another simulation, please enter 'Y' or 'y'. If not, enter 'N' or 'n': ";
	cin >> pA;
	cout << endl;

	// User input validation loop; the user has to enter 'Y', 'y', 'N', or 'n'.
	while (!isalpha(pA) || !((toupper(pA) == 'Y') || (toupper(pA) == 'N')))
	{
		cout << "You did not enter one of the specified characters.\n";
		cout << "Please enter 'Y' if you would like to run another simulation,\n";
		cout << "or enter 'N' to terminate the program. ";
		cin >> pA;
		cout << endl;
	}

	// Return the character
	return pA;
}

// This function outputs a heading consisting of a line of stars and the simulation number to separate 
// the individual crap game simulations.
void separateSims(int &simNum)
{
	// Local variable to hold the number of stars that will be outputted in the heading on either side of
	// the simulation number declaration
	int sepSym = 25;

	// Output the stars to the left of the declaration
	for (int i = 0; i < sepSym; i++)
		cout << "*";

	// Display the simulation number
	cout << "Simulation #" << simNum;

	// Output the rest of the stars
	for (int i = 0; i < sepSym; i++)
		cout << "*";

	cout << endl;
}