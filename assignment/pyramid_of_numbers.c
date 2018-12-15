/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <2AHIF>
 * ---------------------------------------------------------
 * Exercise Number: 3
 * Title:			Pyramid of Numbers
 * Author:			<Daniel Andricic>
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);

/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/

int main(int argc, char *argv[])
{
	struct BigInt big_int = {0, {0}};
	struct BigInt big_result = {0, {0}};
	char a_string[MAX_DIGITS];

	printf("Please enter a number: ");
	scanf("%s", a_string);

	strtobig_int(a_string, strlen(a_string), &big_int);

	for (int i = 2; i <= 9; i++)
	{
		multiply(&big_int, i, &big_result);
		print_big_int(&big_int);
		printf(" * %ld = ", i);
		copy_big_int(&big_result, &big_int);
		print_big_int(&big_int);
		printf("\n");
	}

	for (int i = 2; i <= 9; i++)
	{
		print_big_int(&big_int);
		divide(&big_int, i, &big_result);
		printf(" / %ld = ", i);
		copy_big_int(&big_result, &big_int);
		print_big_int(&big_int);
		printf("\n");
	}

	return 0;
}

int strtobig_int(const char *str, int len, struct BigInt *big_int)
{
	for (int i = 0; i < len; i++)
	{
		big_int->the_int[i] = str[i] - '0';
		big_int->digits_count++;
	}

	return big_int->digits_count;
}

void print_big_int(const struct BigInt *big_int)
{
	for (int i = 0; i < big_int->digits_count; i++)
	{
		printf("%d", big_int->the_int[i]);
	}
}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result)
{
	int overflow = 0;
	int current_val;
	for (int i = big_int->digits_count-1; i >= 0; i--)
	{
		current_val = (big_int->the_int[i]*factor) + overflow;
		overflow = crnt_val / 10;
		current_val = crnt_val % 10;
		big_result->the_int[i + 1] = crnt_val; //place i + 1 if 1 more character is needed
	}

	if(overflow > 0)
	{
		big_result->digits_count = big_int->digits_count+1;
		big_result->the_int[0] = overflow;
	}
	else
	{
		big_result->digits_count = big_int->digits_count;
		for (int i = 0; i < big_result->digits_count; i++)
		{
			big_result->the_int[i] = big_result->the_int[i + 1];
		}
	}
}

void copy_big_int(const struct BigInt *from, struct BigInt *to){
	to->digits_count = from->digits_count;

	for(int i = 0; i < from->digits_count; i++)
	{
		to->the_int[i] = from->the_int[i];
	}
}

void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result)
{
	int overflow = 0;
	int current_val;
	int current_val_new;
	int start;
	int count = 0;

	if(big_int->the_int[0] < divisor)
	{
		big_result->digits_count = big_int->digits_count -1;
		overflow = big_int->the_int[0];
		start = 1;
	}
	else
	{
		big_result->digits_count = big_int->digits_count;
		start = 0;
	}

	for (int i = start; i < big_int->digits_count; i++)
	{
		current_val = (overflow*10) + big_int->the_int[i];
		current_val_new = current_val / divisor;
		big_result->the_int[count] = current_val_new;
		overflow = current_val - (current_val_new * divisor);
		count++;
	}
}
