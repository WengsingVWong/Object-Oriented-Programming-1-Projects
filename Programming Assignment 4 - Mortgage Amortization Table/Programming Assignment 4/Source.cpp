// Author: Wengsing Wong
// Adapted from CIS 3100 Programming Assignment 4
// This program asks the user to input values for the loan amount, the annual interest rate, the number of years, and
// additional principal (if any). It then outputs a mortgage amortization table to an external file, with the data in
// the table being formatted as comma separated currency numbers.

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// SPACE is a constant that represents the maximum number of spaces that can be allotted to a number.
const int SPACE = 12;

int length(double);
void printHeading(double, double, int, double, double, double, ofstream&);
void printTable(double, double, double, ofstream&);
void commaNumber(ofstream&, double);
void blanks(ofstream&, int);
void printDollarNumber(ofstream&, double, int, int);

int main()
{
	// loanAmount will hold the loan amount, annualInterest will hold the annual interest rate,
	// additionalPrincipal will hold the additional principal that will be paid per month (if any),
	// monthlyPayment will hold the amount to be paid per month in order to repay the loan,
	// actualPayment will hold the actual amount to be paid per month, and
	// numberOfYears will hold the number of years available to repay the loan.
	double loanAmount, annualInterest, additionalPrincipal, monthlyPayment, monthlyInterest, actualPayment;
	int numberOfYears;

	// Inputting data for the variables 
	cout << "Please enter the loan amount (do not include any commas): ";
	cin >> loanAmount;
	cout << "Please enter the annual interest rate as a percentage (do not include the \"%\" symbol): ";
	cin >> annualInterest;
	cout << "Please enter the number of years you have to pay off the loan: ";
	cin >> numberOfYears;
	cout << "Please enter the additional principal, if any, you are willing to pay per month: ";
	cin >> additionalPrincipal;

	// Validating user input
	// For the purposes of the assignment, the maximum loan amount was set at $10,000,00.00, exclusive.
	while (loanAmount <= 0.00 || loanAmount >= 10000000.00)
	{
		cout << "\nThe loan amount must be between $0.00 and $10,000,000.00, exclusive." << endl;
		cout << "Please enter a valid loan amount: ";
		cin >> loanAmount;
	}
	while (annualInterest >= 100 || annualInterest <= 0)
	{
		cout << "\nThe annual interest rate must be between 0.00% and 100.00%, exclusive." << endl;
		cout << "Please enter a valid annual interest rate: ";
		cin >> annualInterest;
	}
	while (numberOfYears <= 0)
	{
		cout << "\nThe number of years must be greater than zero, exclusive." << endl;
		cout << "Please enter a valid number of years: ";
		cin >> numberOfYears;
	}
	while (additionalPrincipal < 0)
	{
		cout << "\nThe additional principal must be greater than or equal to $0.00." << endl;
		cout << "Please enter a valid additional principal: ";
		cin >> additionalPrincipal;
	}

	// Ignore the \n key in the buffer so that getline will work properly
	cin.ignore();

	cout << endl;

	// fileName will hold the name of the external file that the mortgage amortization table will be outputted to.
	string fileName;

	// Instruct the user to enter a name for the external file and store it in fileName
	cout << "The mortgage amortization table will be sent to an external file." << endl;
	cout << "Please enter a name for this file: ";
	getline(cin, fileName);

	// Define an oftsream object called outFile that will output data to an external file named fileName
	ofstream outFile(fileName);

	// Calculate monthly interest, the monthly payment, and the actual payment.
	monthlyInterest = annualInterest / 12.0;
	monthlyPayment = (loanAmount * (monthlyInterest / 100)) / (1 - (1 / pow(1 + monthlyInterest / 100, numberOfYears * 12.0)));
	actualPayment = monthlyPayment + additionalPrincipal;
	
	// Output the top heading of the amortization table to an external file
	printHeading(loanAmount, annualInterest, numberOfYears, monthlyPayment, additionalPrincipal, actualPayment, outFile);

	// Output the data for the amortization table to an external file
	printTable(loanAmount, monthlyInterest, actualPayment, outFile);
	
	// Close the ofstream object, inform the user that the table has been fully outputted to an external file, and
	// end the program
	outFile.close();
	cout << "\nYour amortizaation table has been outputted to an external file named " << fileName << "." << endl;
	cout << "The program will now close.";
	return 0;
}

// This function returns the number of spaces required to print any number, including the decimal point and two decimal 
// places.
int length(double n)
{
	// If n is greater than or equal to 10, use base-10 logarithms to calculate the number of spaces needed. log10(n) will 
	// determine the number of digits in the number beyond the ones place, d/3 determines how many commas will be needed, 
	// and 4 represents the ones place, the decimal point, and the two decimal places.
	if (n >= 10)
	{
		int d = log10(n);
		return d + d / 3 + 4;
	}

	// If n is less than 10, then only 4 spaces will be needed to display the number: the ones place, the decimal point, and
	// the two decimal places.
	else
		return 4;
}

// This function prints the top heading of the mortgage amortization table (outputted to an external file).
void printHeading(double lA, double aI, int nOY, double mP, double addPr, double actP, ofstream& o)
{
	// The top heading of the mortgage amortization table (outputted to an external file)
	o << endl << endl << endl;
	blanks(o, SPACE - 4);
	o << "MORTGAGE AMORTIZATION TABLE" << endl << endl;

	// The "Amount" line (outputted to an external file)
	o << "Amount:";
	blanks(o, SPACE + 9);
	o << "$";
	printDollarNumber(o, lA, SPACE, 3);
	o << endl;

	// The "Interest Rate" line (outputted to an external file)
	o << "Interest Rate:";
	blanks(o, SPACE + 2);
	o << aI << "%" << endl;

	// The "Term (Years)" line (outputted to an external file)
	o << "Term (Years):";
	blanks(o, SPACE + 3);
	o << nOY << endl;

	// The "Monthly Payment" line (outputted to an external file)
	o << "Monthly Payment:";
	blanks(o, SPACE);
	o << "$";
	printDollarNumber(o, mP, SPACE, 3);
	o << endl;

	// The "Additional Principal" line (outputted to an external file)
	o << "Additional Principal:";
	blanks(o, SPACE - 5);
	o << "$";
	printDollarNumber(o, addPr, SPACE, 3);
	o << endl;

	// The "Actual Payment" line (outputted to an external file)
	o << "Actual Payment:";
	blanks(o, SPACE + 1);
	o << "$";
	printDollarNumber(o, actP, SPACE, 3);
	o << endl << endl;

	// The "Principal" table heading (outputted to an external file)
	blanks(o, SPACE - 2);
	o << "Principal";

	// The "Interest" table heading (outputted to an external file)
	blanks(o, SPACE - 6);
	o << "Interest";

	// The "Balance" table heading (outputted to an external file)
	blanks(o, SPACE - 5);
	o << "Balance" << endl;
}

// This function outputs the data for the amortization table to an external file.
void printTable(double lA, double mI, double actP, ofstream& o)
{
	// balance will hold the remaining balance to be repaid and is initially equal to the amount of the loan.
	// interest will hold the interest paid on the loan for each monthly payment.
	// principal will hold the amount of the loan that is repaid each month.
	// termNumber will hold the current term number.
	// lenOftm will hold the length of the number stored in termNumber.
	double balance = lA, interest, principal;
	int termNumber = 0, lenOftm;

	// This loop outputs the rest of the amortization table and will only terminate when the balance reaches $0.00.
	do
	{
		// Convert monthly interest to a decimal and calculate the interest payment and the principal payment
		interest = balance * (mI / 100);
		principal = actP - interest;

		// If the remaining balance is less than or equal to the actual monthly payment, set the principal
		// payment equal to the remaining balance. That will be the final payment.
		if (balance <= actP)
			principal = balance;

		// Subtract the principal payment from the old balance to obtain the new balance
		balance -= principal;

		// Increment the term number and output it to an external file
		termNumber++;
		o << termNumber;

		// The first line of the table must have "$" outputted appropriately to indicate that the data is formatted
		// as currency numbers.
		// This outputs the "$" before the first value for the principal payment.
		if (termNumber == 1)
		{
			blanks(o, SPACE - 6);
			o << "$";
		}

		// This applies for every line in the table except for the first.
		// This outputs the appropriate number of blank spaces so that the outputted principal payment data lines up
		// with the "Principal" table heading.
		else
		{
			lenOftm = log10(termNumber) + 1;
			blanks(o, SPACE - 4 - lenOftm);
		}

		// Output the principal payment
		printDollarNumber(o, principal, SPACE - 1, 3);

		// The first line of the table must have "$" outputted appropriately to indicate that the data is formatted
		// as currency numbers.
		// This outputs the "$" before the first value for the interest payment.
		if (termNumber == 1)
		{
			blanks(o, SPACE - 10);
			o << "$";
		}

		// This applies for every line in the table except for the first.
		// This outputs the appropriate number of blank spaces so that the outputted interest payment data lines up
		// with the "Interest" table heading.
		else
			blanks(o, SPACE - 9);

		// Output the interest payment
		printDollarNumber(o, interest, SPACE - 1, 3);

		// The first line of the table must have "$" outputted appropriately to indicate that the data is formatted
		// as currency numbers.
		// This outputs the "$" before the first value for the remaining balance.
		if (termNumber == 1)
		{
			blanks(o, SPACE - 10);
			o << "$";
		}

		// This applies for every line in the table except for the first.
		// This outputs the appropriate number of blank spaces so that the outputted remaining balance data lines up
		// with the "Balance" table heading.
		else
			blanks(o, SPACE - 9);

		// Output the balance payment
		printDollarNumber(o, balance, SPACE - 1, 3);

		// Move to the next line of the table
		o << endl;

		// If the remaining balance is greater than $0.00, calculate the new principal payment, interest payment, and
		// new remaining balance and output them accordingly. If the remaining balance has reached $0.00, then that is
		// the last line of the amortization table.
	} while (balance > 0);
}

// This function outputs a number to an external file properly formatted with commas.
void commaNumber(ofstream &o, double x)
{
	// n is the integer part of x, f is the fractional part of x, numPart will hold each part of x that the function will
	// focus on when outputting x to an external file with commas, d will hold the length of x beyond the ones place, and
	// comNum will hold the number of commas to be outputted along with x.
	int n, f, numPart, d, comNum;

	// Round x to the nearest hundredth
	x = round(x * 100) / 100;

	// Store the integer part of x in n, and store the fractional part of x in f
	n = int(x);
	f = (x - int(x)) * 100;

	// Only execute if there is an integer part of x to output
	if (n > 0)
	{
		// Calculate the number of digits in n beyond the ones place and the number of commas needed to print n
		d = log10(n);
		comNum = d / 3;

		// This for loop outputs (to an external file) all the digits of x (with properly placed commas) except 
		// those in the hundreds, tens, and ones place.
		for (int i = comNum; i >= 1; i--)
		{
			// Obtain the digits to the left of where the comma will be placed
			numPart = n / int(pow(10, i * 3));

			// Applies only if the digits to be outputted are located to the right of the leftmost comma
			if (i < comNum)
			{
				// If numPart contains only 1 digit, then output 2 0s before it.
				if (numPart < 10)
					o << "00" << numPart;

				// If numPart contains 2 digits, then output 1 0 before it.
				else if (numPart < 100)
					o << "0" << numPart;

				// If numPart contains 3 digits, then output it as is.
				else
					o << numPart;
			}

			// If the digits to be outputted are to the left of the leftmost comma, output the digits normally.
			else
				o << numPart;

			// Output a comma after whatever digits were just outputted and remove those digits from n
			o << ",";
			n = n % int(pow(10, i * 3));
		}

		// This if/else statement outputs the digits in the hundreds, tens, and ones places. 
		// If commas have been outputted previously for this number, then output the appropriate amount of 0s 
		// before the remaining digits.
		if (comNum != 0)
		{
			// If there is only 1 digit remaining (ones place), output 2 0s before it.
			if (n < 10)
				o << "00" << n;

			// If there are 2 digits remaining (tens and ones places), output 1 0 before them.
			else if (n < 100)
				o << "0" << n;

			// If there are 3 digits remaining (hundreds, tens, and ones places), output them normally.
			else
				o << n;
		}

		// If the integer part of x is 1-3 digits long (i.e. no commas are needed), output the integer part as is.
		else
			o << n;
	}
	// If there is no integer part of x to output, output a 0 before the decimal point.
	else if (n == 0)
		o << "0";

	// Output a decimal point.
	o << ".";

	// Output the fractional part of x.
	// If x did not have a fractional part, output 2 0s after the decimal point.
	if (f == 0)
		o << "00";

	// If the fractional part of x contains only contains a digit in the hundredths place, output a 0 before that digit.
	else if (f < 10)
		o << "0" << f;

	// If the fractional part of x contains two digits, output them normally.
	else
		o << f;
}

// This function outputs n blanks to an external file.
void blanks(ofstream &o, int n)
{
	for (int i = 1; i <= n; i++)
		o << " ";
}

// This function outputs a number to an external file properly formatted with commas and blanks.
// x is the number to be outputted, s is the maximum number of spaces available, and p represents position
// (1 is left-, 2 is center-, and 3 is right-justified).
void printDollarNumber(ofstream &o, double x, int s, int p)
{
	// b is a local variable that will hold the number of blank spaces needed to output x.
	// h is a local variable that will hold half the number of blank spaces needed to output x. This is needed
	// in order to output x center-justified.
	int b = s - length(x);
	int h = b / 2;

	// This switch statement outputs x with the appropriate blanks and commas to an external file in different
	// positions--left-justified, center-justified, or right-justified--depending on the value stored in p.
	switch (p)
	{
	// Left-justified
	// Output x with commas, and the necessary blanks afterwards
	case 1:
		commaNumber(o, x);
		blanks(o, b);
		break;

	// Center-justified
	// Output half of the necessary blanks, then x with commas, and then the rest of the blanks
	case 2:
		blanks(o, h);
		commaNumber(o, x);
		blanks(o, b - h);
		break;

	// Right-justified
	// Output the necessary blanks, and x with commas afterwards
	case 3:
		blanks(o, b);
		commaNumber(o, x);
		break;

	// Default statement in case an invalid value for p (not 1, 2, or 3) was passed to the function
	default:
		cout << "Invalid argument for position (p) was passed to the printDollarNumber function." << endl;
		break;
	}
}