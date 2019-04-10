// Author: Wengsing Wong
// This was programming practice for CIS 3100.
// This program asks the user to input an integer, and outputs a pyramid 
// with a number of rows equal to the number he/she inputted.

#include <iostream>
using namespace std;

int main()
{
	// This will determine the number of rows in the pyramid.
	int rows;

	// Asks the user to input an integer and stores the result in rows.
	cout << "Enter an integer: ";
	cin >> rows;

	// Validates user input; in this case, the user cannot input a number 
	// that is less than or equal to 0. If the user's input is invalid, the 
	// user is asked to input a different value, which is then validated.
	// The process repeats until the user has inputted a value greater than 0.
	while (rows <= 0)
	{
		cout << endl;
		cout << "A pyramid cannot have " << rows << " rows." << endl;
		cout << "Please enter another value: ";
		cin >> rows;
	}

	cout << endl;

	// The outer loop (i) controls the row number and will loop a number of times
	// equal to the number the user inputs.
	for (int i = rows; i >= 1; i--)
	{
		// This inner loop outputs the spaces, if any, that appear before the stars in each row.
		for (int space = 0; space < rows - i; space++)
			cout << " ";

		// This inner loop outputs the left half of the pyramid, including the middle column. 
		for (int j = i; j <= 2 * i - 1; j++)
			cout << "*";

		// This inner loop outputs the right half of the pyramid, excluding the middle column.
		for (int k = 0; k < i - 1; k++)
			cout << "*";

		// Moves to the next line for the next row.
		cout << endl;
	}
	return 0;
}