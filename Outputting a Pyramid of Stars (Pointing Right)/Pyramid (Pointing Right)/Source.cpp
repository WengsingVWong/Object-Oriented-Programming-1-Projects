// Author: Wengsing Wong
// This was part of an exam question from CIS 3100.
// This program asks the user to input an integer, and outputs a pyramid pointing to the right
// with its longest row containing a number of stars equal to the integer inputted by the user.

#include <iostream>
using namespace std;

int main()
{
	// This will determine the length of the longest row (a.k.a. the middle row) in the pyramid,
	// as well as the number of rows both above and below the middle row.
	int n;

	// Asks the user to input an integer and stores the result in n.
	cout << "Enter an integer: ";
	cin >> n;

	// Validates user input; in this case, the user cannot input a number that is less than or
	// equal to 0. If the user's input is invalid, the user is asked to input a different value,
	// which is then validated. The process repeats until the user has inputted a value
	// greater than 0.
	while (n <= 0)
	{
		cout << endl;
		cout << "A pyramid cannot have " << n << " stars in a row." << endl;
		cout << "Please enter another value: ";
		cin >> n;
	}

	cout << endl;

	// The outer loop (i) will control the row number. It will repeat a number of
	// times equal to one less than double the number inputted by the user.
	for (int i = 1; i <= (2 * n - 1); i++)
	{
		// This will output the top half of the pyramid, including the
		// middle row.
		if (i <= n)
		{
			// The inner loop (j) controls the number of stars and spaces
			// that are outputted in each row.
			for (int j = 0; j < n; j++)
			{
				if (j > i - 1)
					cout << " ";
				else
					cout << "*";
			}
			cout << endl;
		}

		// This will output the bottom half of the pyramid, excluding the
		// middle row.
		else
		{
			// The inner loop (j) controls the number of stars and spaces
			// that are outputted in each row.
			for (int j = (n - 1); j > 0; j--)
			{
				if (j >= (i - n))
					cout << "*";
				else
					cout << " ";
			}
			cout << endl;
		}
	}
	cout << endl;

	return 0;
}