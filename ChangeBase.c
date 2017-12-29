/*
 * In order to change a number base, first we compute the number representation in base 10.
 * the algorithm is: we take the number, take modulo of it by 10 so we get the least significant
 * digit (LCD) and then we multiply it by currentBase^0 (=1), then we divide the number by 10 to
 * get rid of the LCD. in the next iteration we again take modulo by 10 of number to get the LCD,
 * but now we multiply it by currentBase^1 (=currentBase). we sum all those computations and
 * continue until num equals 0, and then we return the sum. after that we have a number in base 10,
 * and we turn it to the newBase by the same algorithm as before with few changes: we take modulo
 * of newBase instead of 10, and we multiply LCD by 10^n instead of currentBase^n.
 *
 * The running time of the algorithm is O(n), when n is the digit of the number, because every
 * iteration the length of the number get small by 1 digit because we divide it by 10.
 **********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define TO_DECIMAL 10

/**
 * given a number, the current base and a new base. returns the number in the desired base.
 * must be given the base 10 in order to run properly, so must first cast to base 10, and then
 * cast to the desired base.
 * @param num the number to represent in the new base.
 * @param currentBase the current base of num.
 * @param newBase the desired base.
 * @return num in the desired base.
 */
unsigned long long changeBase(unsigned long long num, int currentBase, int newBase);

/**
 * this program is given a number, the current number base and the desired base, and the program
 * prints the number in that base.
 * @return the number in the desired base.
 */
int main()
{
    unsigned int number, currentBase, newBase;
    scanf("%d^%d^%d^", &currentBase, &newBase, &number);
    unsigned long long decimal = changeBase(number, currentBase, TO_DECIMAL);
    if (decimal == EXIT_FAILURE)
    {
        fprintf(stderr, "invalid!!\n");
        return 1;
    }
    unsigned long long result = changeBase(decimal, TO_DECIMAL, newBase);
    printf("%llu", result);
    return 0;
}

unsigned long long changeBase(unsigned long long num, int currentBase, int newBase)
{
    unsigned long long result = 0;
    unsigned long long multiplication = 1;
    while (num > 0)
    {
        int curDigit = (int)num % newBase;
        if (curDigit >= currentBase)
        {
            return EXIT_FAILURE;
        }
        result += curDigit * multiplication ;
        multiplication  *= currentBase;
        num /= newBase;
    }
    return result;
}