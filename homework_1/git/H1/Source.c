#include <stdio.h>
/*a. Decompose a given even natural number, greater than 2, as a sum of two prime numbers (Goldbach’s conjecture).
b. Given a vector of numbers, find the longest contignous subsequence such that any consecutive elements have at least 2 distinct digits in common_digits_in_two_numbers.*/

void read_array(int list[], int* len_list) // Read a list of numbers
{// as input we have an empty list of numbers and an empty space for the lenght of the list
	// read_a_number the lean of the list
	printf("Input the len of the list -> ");
	scanf("%d", len_list);

	int index;

	printf("Read the array!\n");
	// read_a_number the list
	for (index = 1; index <= *len_list; ++index)
		scanf("%d", &list[index]);
}// as output we have the list of numbers and the lenght of the list

void read_a_number(int* nr)// here we read_a_number a number for exercise "a"
{// as input we have an empty space for a number
	printf("Give a even natural number, greater than 2 -> ");
	scanf("%d", nr);
}// as output we have a number

int prime_number(int nr) // here we identify the if a number is prime or not
{// as input we have a number
	if (nr <= 1 || (nr % 2 == 0 && nr!=2))
		return 0;
	else if (nr == 2)
		return 1;
	else
	{
		int nr_div = 0,div;

		for (div = 1; div <= nr; ++div)
			if (nr % div == 0)
				++nr_div;

		if (nr_div > 2)
			return 0;
		else if (nr_div == 2)
			return 1;
	}
}// as output function return 1 if the number is prime or 0 else

int decompose_a_number_as_a_sum_of_two_prime_numbers(int nr, int* a, int* b)// here we decompose a number in a sum of prime numbers for exercise "a"
{// as input we have the number witch we want to decompose and two numbers "a" and "b" witch will compose the sum of two prime numbers
	for (*a = 2; *a <= nr; ++ * a)
		for (*b = 2; *b <= nr; ++ * b)
			if (*a + *b == nr && prime_number(*a) == 1 && prime_number(*b) == 1)
				return 1;

	return 0;
}// as output the function will return 1 if we found two prime numbers witch sum is equal with "nr" else 0 and that two numbers witch form the sum

int common_digits_in_two_numbers(int a, int b)// here we identify if in a two distinct numbers we have at least two distinct digits
{// as input we have two numbers "a" and "b"
	int cf_secvence[10] = { 0 };

	while (a != 0)
	{
		if (cf_secvence[a % 10] == 0)
			++cf_secvence[a % 10];

		a = a / 10;
	}

	while (b != 0)
	{
		if (cf_secvence[b % 10] <= 1)
			++cf_secvence[b % 10];

		b = b / 10;
	}

	int count = 0;
	for (int index = 1; index <= 9; ++index)
		if (cf_secvence[index] == 2)
			++count;

	if (count >= 2)
		return 1;
	else
		return 0;
}// as putput the function return 1 if that two number have two different digits in common else 0

void determin_the_longest_subsequences(int list[], int len_list,int * st,int* dr) // here we determine the lenght of the longest determin_the_longest_subsequences from our list
{// as input we have the list of numbers and the lenght of the list the start of the max subsequence and the finish of the subsequence
	int start = 1, finish = 2, max_subsequence = 0, current_subsequence=1 ,current_index=1;

	while(finish <= len_list)
		if (common_digits_in_two_numbers(list[current_index], list[finish]) == 1)
		{
			++current_subsequence;
			++finish;
			++current_index;
		}
		else
		{
			if (max_subsequence < current_subsequence)
			{
				max_subsequence = current_subsequence;
				*st = start;
				*dr = finish;
			}

			start = finish;
			finish = start + 1;
			current_subsequence = 1;
			current_index = start;

		}

	if (common_digits_in_two_numbers(list[current_index], list[finish]) == 1)
	{
		++current_subsequence;
		++finish;
		++current_index;
	}
	else
	{
		if (max_subsequence < current_subsequence)
		{
			max_subsequence = current_subsequence;
			*st = start;
			*dr = finish;
		}

		start = finish;
		finish = start + 1;
		current_subsequence = 1;
		current_index = start;

	}
}// as output the function returrn the start index and the finsh index

int main()// here we have the menu of our project with 3 possible commands
{
	int len_list=0, list[1000];
	while (1)
	{
		int command;

		printf("1.Resolve a problem\n");
		printf("2.Resolve b problem\n");
		printf("3.Read an arry\n");
		printf("0.Exit\n");

		printf("Input a command -> ");
		scanf("%d", &command);

		if (command < 0 && command >3)
			printf("Invalide input\n");
		else if (command == 1)
		{
			int nra = 0, p1 = 2, p2 = 2;

			read_a_number(&nra);

			if (nra % 2 == 0)
			{
				if (decompose_a_number_as_a_sum_of_two_prime_numbers(nra, &p1, &p2) == 0)
					printf("The number can't be decomposed!\n");
				else
					printf("We can write the number %d of a sum of %d and %d\n", nra, p1, p2);
			}
			else
				printf("The number is not even!\n");
		}
		else if (command == 2)
		{
			if (len_list != 0)
			{
				int st = 0, dr = 0;

				determin_the_longest_subsequences(list, len_list, &st, &dr);

				if (st == dr)
					printf("We do not have a subequence\n");
				else
				{
					printf("The longest subsequence is: ");

					for (int index = st; index < dr; ++index)
						printf("%d ", list[index]);

					printf("\n");
				}
			}
			else
			{
				printf("You don't have a list yet\n");
			}
		}

		else if (command == 0)
		{
			printf("You exit!\n");
			break;
			
		}
		else if (command == 3)
		{
			read_array(list, &len_list);
		}
	}

	return 0;
}