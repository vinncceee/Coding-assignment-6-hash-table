//Name: Vince Vennedick Banks
//ID: 1001702150
/* Coding Assignment 6 */
#include <stdio.h>

#define HASHTABLESIZE 10


typedef struct playstation_store_games
{
    char *name;
    char *genre;
    int year_of_release;
    char ESRB_rating;
    float current_retail_price;
    struct playstation_store_games *next_ptr;
}
POKEMON;


int MyHashFunction(pass in value being used in hash)
{
    perform hash method
    return value % HASHTABLESIZE;
}

int main(void)
{
    char HashValue[20];
    printf("Enter value ");
    scanf("%s ", HashValue);
    printf("The hash value for %s is %d\n”, HashValue, MyHashFunction(HashValue));
    return 0;
}