/*Write a C Program to Convert Left Recursive grammar to Right Recursive grammar*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100
char terms[MAX], nonterms[MAX];
char production_dict[MAX][MAX][MAX];
int leftcheck_list[MAX][MAX];
bool leftcheck_dict[MAX], rightcheck_dict[MAX];
int nonterms_count = 0, terms_count = 0, prod_count[MAX];

bool isTerm(char ter) {
    if (ter == '#') {
        return true;
    }
    for (int i = 0; i < terms_count; i++) {
        if (ter == terms[i]) {
            return true;
        }
    }
    return false;
}
bool isNTerm(char nT) {
    for (int i = 0; i < nonterms_count; i++) {
        if (nT == nonterms[i]) {
            return true;
        }
    }
    return false;
}
// Function to check for left recursion
bool LeftCheck(char nT, char search, int escape) {
    for (int i = 0; i < prod_count[nT]; i++) {
        if (search == production_dict[nT][i][0]) {
            leftcheck_list[search][i] = nT;
            return true;
        } else if (isNTerm(production_dict[nT][i][0])) {
            return LeftCheck(production_dict[nT][i][0], search, escape + 1);
        }
    }
    return false;
}
// Function to check for right recursion
bool RightCheck(char nT, char search) {
    for (int i = 0; i < prod_count[nT]; i++) {
        int len = strlen(production_dict[nT][i]);
        if (search == production_dict[nT][i][len - 1]) {
            return true;
        }
    }
    return false;
}
// Function to convert left recursion to right recursion
void Left_toRight(char nT) {
    char bet[MAX][MAX], alpha[MAX][MAX];
    int bet_count = 0, alpha_count = 0;

    for (int i = 0; i < prod_count[nT]; i++) {
        if (nT == production_dict[nT][i][0]) {
            strcpy(alpha[alpha_count++], production_dict[nT][i] + 1);
        } else {
            strcpy(bet[bet_count++], production_dict[nT][i]);
        }
    }

    printf("%c -> ", nT);
    for (int i = 0; i < bet_count; i++) {
        printf("%s%c' ", bet[i], nT);
        if (i != bet_count - 1) printf("/");
    }
    printf("\n");

    printf("%c' -> ", nT);
    for (int i = 0; i < alpha_count; i++) {
        printf("%s%c' ", alpha[i], nT);
        if (i != alpha_count - 1) printf("/");
    }
    printf("/#\n");
}
// Function to print the production rules
void Prod_print(char nT) {
    printf("%c -> ", nT);
    for (int i = 0; i < prod_count[nT]; i++) {
        printf("%s", production_dict[nT][i]);
        if (i != prod_count[nT] - 1) printf("/");
    }
    printf("\n");
}
int main() {
    int n;
    char productions[MAX][MAX];

    printf("Enter the number of Productions: ");
    scanf("%d", &n);

    printf("\nRules:\n--------------------\nEpsilon is represented by  # \n");

    for (int i = 0; i < n; i++) {
        printf("Enter production %d: ", i + 1);
        scanf("%s", productions[i]);
    }

    for (int i = 0; i < n; i++) {
        nonterms[nonterms_count++] = productions[i][0];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 3; j < strlen(productions[i]); j++) {
            if (!isNTerm(productions[i][j]) && productions[i][j] != '#' && productions[i][j] != '/') {
                terms[terms_count++] = productions[i][j];
            }
        }
    }

    for (int i = 0; i < nonterms_count; i++) {
        prod_count[nonterms[i]] = 0;
    }

    for (int i = 0; i < n; i++) {
        char nonterm = productions[i][0];
        char *expansion = strtok(&productions[i][3], "/");
        while (expansion != NULL) {
            strcpy(production_dict[nonterm][prod_count[nonterm]++], expansion);
            expansion = strtok(NULL, "/");
        }
    }


    for (int i = 0; i < nonterms_count; i++) {
        leftcheck_dict[nonterms[i]] = LeftCheck(nonterms[i], nonterms[i], 0);
        rightcheck_dict[nonterms[i]] = RightCheck(nonterms[i], nonterms[i]);
    }

    printf("\n");
    for (int i = 0; i < nonterms_count; i++) {
        if (leftcheck_dict[nonterms[i]]) {
            printf("%c contains Left Recursive Grammar\n", nonterms[i]);
        }
        if (rightcheck_dict[nonterms[i]]) {
            printf("%c contains Right Recursive Grammar\n", nonterms[i]);
        }
    }

    // Left recursion elimination
    printf("--------------------------------\n Converted Grammar:\n");
    for (int i = 0; i < nonterms_count; i++) {
        if (leftcheck_dict[nonterms[i]]) {
            Left_toRight(nonterms[i]);
        } else {
            Prod_print(nonterms[i]);
        }
    }

    return 0;
}
