// Author: Wengsing Wong
// CIS 3100 Programming Assignment 6
// This program creates a class to allow mathematical and relational operations with rational (fractional)
// numbers and tests the class by asking the user to input 4 different rational numbers.

#include <iostream>
using namespace std;

// This function returns the greatest common factor of two integers.
int gcf(int a, int b)
{
	// Will store the GCF of integers a and b
	int d;

	// This if/else statement assigns the smaller of the two integers to d. It takes the absolute value of the 
	// two integers in case one or both are negative.
	if (abs(a) > abs(b))
		d = abs(b);
	else
		d = abs(a);

	// This while loop divides the value stored in d into both integers. If the test fails, the loop decrements 
	// d and repeats the test. The loop will terminate if d divides into both integers evenly (without remainder).
	// The loop also checks the value of d in the test expression because the lowest possible GCF is 1, which 
	// means that if d reaches a value of 1, then the loop should terminate as well.
	while (((a % d != 0) || (b % d != 0)) && (d > 1))
		d--;

	// Return the GCF of a and b
	return d;
}

class Rational
{
public:
	Rational();											// Default constructor
	Rational(int, int);									// Constructor with initialization arguments
	Rational(const Rational&);							// Copy constructor
	const Rational& operator=(const Rational&);			// Overloaded assignment operator
	Rational operator+(const Rational&) const;			// Overloaded addition operator
	Rational operator-(const Rational&) const;			// Overloaded subtraction operator
	Rational operator*(const Rational&) const;			// Overloaded multiplication operator
	Rational operator/(const Rational&) const;			// Overloaded division operator
	Rational operator++();								// Overloaded prefix ++ operator
	Rational operator++(int);							// Overloaded postfix ++ operator
	bool operator==(const Rational&) const;				// Overloaded == operator
	bool operator>(const Rational&) const;				// Overloaded > operator
	bool operator<(const Rational&) const;				// Overloaded < operator
	operator int() const;								// Converts an object to an integer
	operator double() const;							// Converts an object to a double
	~Rational();										// Destructor
private:
	int numerator;											// Will hold the numerator portion of the object
	int denominator;										// Will hold the denominator portion of the object
	int objectID;											// Will be used to identify each unique object in 
															// the program
	static int objectCount;									// Will be used to assign a unique objectID to each 
															// unique object
	friend istream& operator>>(istream&, Rational&);		// Overloaded stream extraction operator (>>)
	friend ostream& operator<<(ostream&, const Rational&);	// Overloaded stream insertion operator (<<)
};

// Initialize objectCount to 0
int Rational::objectCount = 0;

// Default constructor for Rational class
Rational::Rational()
{
	// The default rational number will be 0/1, or 0
	numerator = 0;
	denominator = 1;

	// Assign a unique objectID to the default Rational object
	objectID = ++objectCount;

	// Tell the user that the default constructor was called and display the new object's ID and default value
	cout << "Default constructor called for object " << objectID << " : " << *this << endl;
}

// Constructor with initialization arguments
Rational::Rational(int n, int d)
{
	// If both n and d are negative OR n is positive and d is negative, both n and d need to be multiplied by
	// -1 because the resulting fraction is positive (for the former) OR because the negative sign is customarily
	// placed in the numerator (for the latter).
	if (((n < 0) && (d < 0)) || ((n > 0) && (d < 0)))
	{
		numerator = n * -1;
		denominator = d * -1;
	}

	// If n is negative and d is positive, then the fraction can be displayed as is, since the negative sign is
	// customarily placed in the numerator.
	else if ((n < 0) && (d > 0))
	{
		numerator = n;
		denominator = d;
	}

	// If n and d are positive, the fraction can be displayed as is.
	else
	{
		numerator = n;
		denominator = d;
	}
	
	// Assign a unique objectID to the Rational object
	objectID = ++objectCount;

	// Tell the user that the constructor was called and display the new object's ID and value
	cout << "Constructor called for object " << objectID << " : " << *this << endl;
}

// Copy constructor
Rational::Rational(const Rational &r)
{
	// Create a new object and initialize its private variables with the values stored in the corresponding
	// private variables of the object passed to the copy constructor
	numerator = r.numerator;
	denominator = r.denominator;

	// Assign a unique objectID to the copy of the object passed to the copy constructor
	objectID = ++objectCount;

	// Tell the user that the copy constructor was called and indicate which object was copied to which object
	cout << "Copy constructor called for object " << objectID << " from object " << r.objectID << endl;
}

// Overloaded assignment operator
const Rational& Rational::operator=(const Rational& obj)
{
	// Checking for self-assignment; if the object on the right of the = is not identical to the object on the
	// left of the =, then assign the values stored in the right object's private variables to the corresponding
	// private variables of the left object. Afterwards, tell the user which object's contents were assigned to
	// which object.
	if (this != &obj)
	{
		numerator = obj.numerator;
		denominator = obj.denominator;
		cout << "Assignment from object " << obj.objectID << " to object " << objectID << endl;
	}

	// Return the left object (to which contents were copied)
	return *this;
}

// Overloaded addition operator
Rational Rational::operator+(const Rational& obj) const
{
	// Temporary variables to hold the new numerator and denominator after the two Rational objects are added
	int n, d;

	// If the denominators of the two Rational objects are equal, then the new denominator is equal to the old
	// denominators. The new numerator is equal to the sum of the two old numerators.
	if (denominator == obj.denominator)
	{
		n = numerator + obj.numerator;
		d = denominator;
	}

	// If the denominators of the two Rational objects are not equal, then the new numerator is calculated as 
	// shown. The new denominator is equal to the product of the two old denominators.
	else
	{
		n = (numerator * obj.denominator) + (obj.numerator * denominator);
		d = denominator * obj.denominator;
	}
	
	// Find the greatest common factor of the new numerator and denominator, and simplify
	int g = gcf(n, d);
	n /= g;
	d /= g;

	// Return a new Rational object with the simplified new numerator and denominator as initialization
	// arguments
	return Rational(n, d);
}

// Overloaded subtraction operator
Rational Rational::operator-(const Rational& obj) const
{
	// Temporary variables to hold the new numerator and denominator after the two Rational objects are 
	// subtracted
	int n, d;

	// If the denominators of the two Rational objects are equal, then the new denominator is equal to the old
	// denominators. The new numerator is equal to the difference between the two old numerators.
	if (denominator == obj.denominator)
	{
		n = numerator - obj.numerator;
		d = denominator;
	}

	// If the denominators of the two Rational objects are not equal, then the new numerator is calculated as 
	// shown. The new denominator is equal to the product of the two old denominators.
	else
	{
		n = (numerator * obj.denominator) - (obj.numerator * denominator);
		d = denominator * obj.denominator;
	}

	// Find the greatest common factor of the new numerator and denominator, and simplify
	int g = gcf(n, d);
	n /= g;
	d /= g;

	// Return a new Rational object with the simplified new numerator and denominator as initialization
	// arguments
	return Rational(n, d);
}

// Overloaded multiplcation operator
Rational Rational::operator*(const Rational& obj) const
{
	// Temporary variables to hold the new numerator and denominator after the two Rational objects are 
	// multiplied
	int n, d;

	// The new numerator and denominator are the product of the two old numerators and the two old denominators,
	// respectively.
	n = numerator * obj.numerator;
	d = denominator * obj.denominator;

	// Find the greatest common factor of the new numerator and denominator, and simplify
	int g = gcf(n, d);
	n /= g;
	d /= g;

	// Return a new Rational object with the simplified new numerator and denominator as initialization
	// arguments
	return Rational(n, d);
}

// Overloaded division operator
Rational Rational::operator/(const Rational& obj) const
{
	// Temporary variables to hold the new numerator and denominator after the two Rational objects are 
	// divided
	int n, d;

	// The new numerator and denominator are calculated as shown.
	n = numerator * obj.denominator;
	d = denominator * obj.numerator;

	// Find the greatest common factor of the new numerator and denominator, and simplify.
	int g = gcf(n, d);
	n /= g;
	d /= g;

	// Return a new Rational object with the simplified new numerator and denominator as initialization
	// arguments
	return Rational(n, d);
}

// Overloaded prefix ++ operator
Rational Rational::operator++()
{
	// To add 1 to a fraction, add its denominator to its numerator (since 1 is equal to denominator/denominator)
	numerator += denominator;

	// Find the greatest common factor of the new numerator and old denominator, and simplify.
	int g = gcf(numerator, denominator);
	numerator /= g;
	denominator /= g;

	// Return the resulting object
	return *this;
}

// Overloaded postfix ++ operator
Rational Rational::operator++(int)
{
	// Create a temporary Rational object with the old numerator and denominator as initialization arguments
	Rational temp(numerator, denominator);

	// To add 1 to a fraction, add its denominator to its numerator (since 1 is equal to denominator/denominator)
	numerator += denominator;

	// Find the greatest common factor of the new numerator and old denominator, and simplify.
	int g = gcf(numerator, denominator);
	numerator /= g;
	denominator /= g;

	// Return the temporary Rational object
	return temp;
}

// Overloaded == operator
bool Rational::operator==(const Rational& obj) const
{
	// Flag to indicate whether the expression is equal or not
	bool isEqual;

	// If the denominators are equal, then the numerators can be compared normally. If the two numerators are
	// equal, set the flag to true. If the two numerators are not equal, set the flag to false.
	if (denominator == obj.denominator)
	{
		if (numerator == obj.numerator)
			isEqual = true;
		else
			isEqual = false;
	}

	// If the denominators are not equal, then the two Rational objects must be converted so that they have the
	// same denominator. The resulting numerators as a result of this conversion can be calculated as shown.
	// If the resulting numerators are equal, set the flag to true. If the resulting numerators are not equal,
	// set the flag to false.
	else
	{
		if ((numerator * obj.denominator) == (obj.numerator * denominator))
			isEqual = true;
		else
			isEqual = false;
	}

	// Return the boolean value stored in the flag
	return isEqual;
}

// Overloaded > operator
bool Rational::operator>(const Rational& obj) const
{
	// Flag to indicate whether the left Rational object is greater than the right Rational object
	bool isGT;

	// If the denominators are equal, then the numerators can be compared normally. If the left object's 
	// numerator is greater than the right object's numerator, set the flag to true. Otherwise, set the flag to
	// false.
	if (denominator == obj.denominator)
	{
		if (numerator > obj.numerator)
			isGT = true;
		else
			isGT = false;
	}

	// If the denominators are not equal, then the two Rational objects must be converted so that they have the
	// same denominator. The resulting numerators as a result of this conversion can be calculated as shown.
	// If the resulting left object's numerator is greater than the resulting right object's numerator, set the
	// flag to true. Otherwise, set the flag to false.
	else
	{
		if ((numerator * obj.denominator) > (obj.numerator * denominator))
			isGT = true;
		else
			isGT = false;
	}

	// Return the boolean value stored in the flag
	return isGT;
}

// Overloaded < operator
bool Rational::operator<(const Rational& obj) const
{
	// Flag to indicate whether the left Rational object is less than the right Rational object 
	bool isLT;

	// If the denominators are equal, then the numerators can be compared normally. If the left object's 
	// numerator is less than the right object's numerator, set the flag to true. Otherwise, set the flag to
	// false.
	if (denominator == obj.denominator)
	{
		if (numerator < obj.numerator)
			isLT = true;
		else
			isLT = false;
	}

	// If the denominators are not equal, then the two Rational objects must be converted so that they have the
	// same denominator. The resulting numerators as a result of this conversion can be calculated as shown.
	// If the resulting left object's numerator is less than the resulting right object's numerator, set the
	// flag to true. Otherwise, set the flag to false.
	else
	{
		if ((numerator * obj.denominator) < (obj.numerator * denominator))
			isLT = true;
		else
			isLT = false;
	}

	// Return the boolean value stored in the flag
	return isLT;
}

// Converting an object to an integer
Rational::operator int() const
{
	// To convert a Rational object to an integer, divide the numerator by the denominator. Since both private
	// variables are integers, integer division will take place, causing the resulting decimal places (if any)
	// to be cut off and leaving only the integer part.
	return numerator / denominator;
}

// Converting an objec to a double
Rational::operator double() const
{
	// To convert a Rational object to a double, multiply the numerator and denominator by 1.0 (which will 
	// temporarily convert the values stored in the private variables to doubles) and then divide the numerator
	// by the denominator.
	return (numerator * 1.0) / (denominator * 1.0);
}

// Destructor
Rational::~Rational()
{
	// Tell the user that the destructor was called and for which object
	cout << "Destructor called for object " << objectID << endl;
}

// Overloaded stream extraction operator (>>)
istream& operator>>(istream& i, Rational& r)
{
	// Temporary variable to store the "/" character as the operator extracts the inputted numerator and
	// denominator and stores them in the corresponding variables in a given Rational object. This is necessary 
	// because the numerator and denominator of a Rational object are not stored in the format "n/d"; "n" and 
	// "d" are stored separately.
	char dummy;
	i >> r.numerator >> dummy >> r.denominator;

	// Return the input stream object
	return i;
}

// Overloaded stream insertion operator (<<)
ostream& operator<<(ostream& o, const Rational& r)
{
	// The operator accesses the numerator and denominator of a given Rational object and outputs them to the
	// screen, separated by a "/" character. This is necessary because the numerator and denominator of a
	// Rational object are not stored in the format "n/d"; "n" and "d" are stored separately.
	o << r.numerator << "/" << r.denominator;

	// Return the output stream object
	return o;
}

int main()
{
	// Instantiate 7 different Rational objects using the default constructor
	Rational r1, r2, r3, r4, r5, r6, r7;

	// Ask the user to input four different rational numbers and store them in r1 to r4
	cout << "Please enter 4 rational numbers, each in the format of (n/d): ";
	cin >> r1 >> r2 >> r3 >> r4;

	// Test the class by performing various relational and mathematical operations, and assign values to r5 and 
	// r6 based on the results
	if (r1 > r2)
		r5 = r3 + r4;
	else
		r5 = r3 - r4;

	if (r3 == r4)
		r6 = r1 * r2;
	else
		r6 = r1 / r2;

	// Display the values stored in r5 and r6 to verify that the overloaded operators are working as intended
	cout << "r5 = " << r5 << endl;
	cout << "r6 = " << r6 << endl;
	
	// Use the overloaded prefix operator and display the values stored in r5 and r7 to verify that it is
	// working as intended
	r7 = ++r5;
	cout << "r5 = " << r5 << endl;
	cout << "r7 = " << r7 << endl;

	// Use the overloaded postfix operator and display the values stored in r6 and r7 to verify that it is
	// working as intended
	r7 = r6++;
	cout << "r6 = " << r6 << endl;
	cout << "r7 = " << r7 << endl;

	// Use the overloaded assignment operator to perform multiple assignments in the same line, and display the
	// value stored in r7 to verify that it is working as intended
	r7 = r6 = r5;
	cout << "r7 = " << r7 << endl;
	
	return 0;
}