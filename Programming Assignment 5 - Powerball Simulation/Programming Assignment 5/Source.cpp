// Author: Wengsing Wong
// Adapted from CIS 3100 BMWA Programming Assignment 5
// This program simulates Powerball drawings. It asks the user how many games he/she would like to play,
// simulates that many Powerball games, and displays the results onscreen.

#include <iostream>
#include <cstdlib> // Need this for rand() and srand()
#include <ctime> // Need this for time()
using namespace std;

const int WHITEBALLS = 69; // Number of white balls in the cage
const int WHITEPICKS = 5; // Number of white balls to be drawn from the cage
const int REDBALLS = 26; // Number of red balls in a second cage

int howManyGames();
void playWhite();
void packWhiteBalls(int[], int, int&);
void sortWhitePicks(int[], int);
void playRed();
void showResults(int[], int);
void showResults(int);

int main()
{
	// numOfGames holds the number of Powerball drawings the user wants to simulate
	int numOfGames = howManyGames();
	
	// Set up the random number generator
	unsigned int seed = time(0);
	srand(seed);

	// Repeat the Powerball drawing as many times as the user requests, represented by the number stored 
	// in numOfGames
	for (int i = 0; i < numOfGames; i++)
	{
		playWhite();
		playRed();
	}
	return 0;
}

// This function asks the user to input the number of games he/she wants to play, validates it, and then 
// returns it
int howManyGames()
{
	// Local variable to hold the number of games
	int nOG;
	cout << "How many games would you like to play? ";
	cin >> nOG;
	cout << endl << endl;

	// Validate user input; the number of games must be a positive number
	while (nOG <= 0)
	{
		cout << "That is an invalid number of games. The number of games must be greater than 0.\n";
		cout << "How many games would you like to play? ";
		cin >> nOG;
		cout << endl << endl;
	}

	// Return the number of games to play
	return nOG;
}

// This function sets up the cage of 69 white balls and the cage for the 5 drawn white balls. It then removes
// 5 white balls from the first cage and places them in the second. Lastly, the 5 drawn white balls are
// sorted in ascending order.
void playWhite()
{
	// Define a variable to hold the beginning number of white balls in the cage. This variable will be
// decremented by 1 after each drawing to represent the permanent removal of that ball from the cage.
	int sizeOfWhiteBallsCage = WHITEBALLS;

	// Define the array (the cage) that will hold the 69 white balls
	int whiteBallsCage[WHITEBALLS];

	// Add all 69 white balls to the cage
	for (int i = 0; i < WHITEBALLS; i++)
	{
		int j = i + 1;
		whiteBallsCage[i] = j;
	}

	// Define the array that will hold the 5 white balls drawn from the cage of white balls and a pointer 
	// variable that points to the array (the cage) that holds the remaining white balls
	int whitePicksArray[WHITEPICKS];
	int *whitePicksArrayPtr = whitePicksArray;
	int sizeOfWhitePicksArray = WHITEPICKS;

	// Draw 5 white balls from the cage and add them to the whitePicks array. After each ball is drawn, 
	// it is removed from the cage of white balls, the remaining elements are shifted to the left, and 
	// the array's size decreases by 1.
	for (int i = 0; i < WHITEPICKS; i++)
	{
		int randomWhiteBall = rand() % sizeOfWhiteBallsCage;
		*(whitePicksArrayPtr + i) = whiteBallsCage[randomWhiteBall];

		// Remove the selected white ball from the cage, shift the remaining elements to the left, and 
		// decrease the size of the array by 1
		packWhiteBalls(whiteBallsCage, randomWhiteBall, sizeOfWhiteBallsCage);
	}

	// Sort the white balls drawn from the main array in ascending order
	sortWhitePicks(whitePicksArray, sizeOfWhitePicksArray);

	// Display the results of the drawing
	showResults(whitePicksArray, sizeOfWhitePicksArray);
}

// This function permanently removes a white ball from the cage of white balls and shifts the remaining balls
// to the left. The size of the array also permanently decreases by 1.
// num[] is the array that is being manipulated by the function, d is the index of the ball being drawn (and 
// removed), and size is the size of the manipulated array.
void packWhiteBalls(int num[], int d, int &size)
{
	// Starting from where the ball was drawn, overwrite each ball with the one that comes next sequentially.
	for (int i = d; i < size - 1; i++)
	{
		num[i] = num[i + 1];
	}

	// Reduce the size of the array by 1 to eliminate the extra copy of the last ball in the array and to
	// simulate the removal of the drawn ball
	size -= 1;
}

// This function sorts the white balls we have drawn from the cage of white balls in ascending order.
void sortWhitePicks(int array[], int size)
{
	// minIndex is a local variable that will end up holding the index of the ball with the lowest value in
	// the array.
	// minValue is a local variable that will end up holding the ball with the lowest value in the array.
	int minIndex, minValue;

	// This loop sorts the array in ascending order.
	for (int start = 0; start < (size - 1); start++)
	{
		// Store the index and number of the current leftmost ball in the array. This ball will be the
		// baseline. Every time the loop iterates, the initial baseline ball will be the next ball, and so
		// on until the balls are sorted.
		minIndex = start;
		minValue = array[start];

		// Compare the number of the current leftmost ball to that of each of the subsequent balls. If the 
		// number of one of the subsequent balls is less than that of the current leftmost ball, store the
		// former's index and number in minValue and minIndex. This ball will be the new baseline. Continue
		// until you reach the end of the array.
		for (int index = start + 1; index < size; index++)
		{
			if (array[index] < minValue)
			{
				minValue = array[index];
				minIndex = index;
			}
		}

		// Swap the positions of the current leftmost ball with the ball that was determined to have the
		// lowest number.
		swap(array[minIndex], array[start]);
	}
}

// This function draws a random red ball from the cage of red balls and returns the number drawn
void playRed()
{
	// Draw a random red ball from the cage of red balls
	int randomRedBall = (rand() % REDBALLS) + 1;

	// Display the results of the drawing
	showResults(randomRedBall);
}

// This function displays the 5 white balls drawn
void showResults(int wbd[], int size)
{
	cout << "White Balls are: ";
	for (int i = 0; i < size; i++)
		cout << wbd[i] << " ";
}

// This function displays the red ball drawn
void showResults(int rbd)
{
	cout << "Power Ball is: " << rbd << endl << endl;
}