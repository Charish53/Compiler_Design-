/*syntax analyzer*/
/*Write a C program to take it as an argument and count the number of lines, words, and characters in it.

Also count the number of characters that are 1. Vowels [a,e,i,o,u,A,E,I,O,U] , 2. Consonants, 3. Digits[0-9] and 4. Other than these three.

Print all of them on the terminal.

Sum of 1st + 2nd + 3rd + 4th = Number of characters*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main()
{
    char ch, file_name[25];
    int characters = 0, words = 0, lines = 0;
    int vowels = 0, consonants = 0, digits = 0, spl_char = 0;
    FILE *fp;

    fp = fopen("program2.c", "r");
    if (fp == NULL)
    {
        printf("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
        characters++;

        if (ch == '\n' || ch == '\0')
            lines++;

        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            words++;

        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || 
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
        {
            vowels++;
        }
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            consonants++;
        }
        if (ch >= '0' && ch <= '9')
        {
            digits++;
        }
        if (!isalnum(ch))
        {
            spl_char++;
        }
    }
    if (characters > 0)
    {
        words++;
        lines++;
    }
    printf("\n");
    printf("Total vowels          = %d\n", vowels);
    printf("Total consonants      = %d\n", consonants);
    printf("Total digits          = %d\n", digits);
    printf("Other than these      = %d\n", spl_char);
    printf("Number of Characters  = %d\n", characters);
    printf("Total words           = %d\n", words);
    printf("Total lines           = %d\n", lines);
    fclose(fp);
    return 0;
}

//=============================program2.c ==================================//
// #include<stdio.h>
// int main() {
//     int a;
//     printf("Hello World\n");
//     return 0;
// }
