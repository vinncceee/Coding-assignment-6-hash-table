#include <stdio.h>
#include <string.h>

#define HASHTABLESIZE 30
#define MAX_INPUT_SIZE 2048


int MyHashFunction(char *key)
{
    int sum = 0;
    int length = strlen(key);

    for(int i = 0; i < length; i++)
    {
        sum += key[i];
    }

    return sum % HASHTABLESIZE;
}

int main(void)
{
    char HashValue[MAX_INPUT_SIZE];
    printf("Enter value: ");
    fgets(HashValue, sizeof(HashValue), stdin);
    char *newline = strchr(HashValue, '\n');
    if (newline) 
    {
        *newline = '\0';
    }
    printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue));
    return 0;
}