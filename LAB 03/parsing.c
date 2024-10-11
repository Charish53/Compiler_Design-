/*Write a C Program to verify whether the string is accepted/rejected for the given  grammar ? make sure that  your grammar should follow all the production rules */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_GRAMMAR_RULES 10
#define MAX_STR_LEN 100

typedef struct {
    char left;
    char right[10];
} GrammarRule;

typedef struct {
    char left;
    char parsed[10];
    char remaining[10];
    int origin;
} ParseItem;

GrammarRule rules[MAX_GRAMMAR_RULES] = {
    {'S', "aSSb"},
    {'S', "a"},
    {'S', "b"}
};

int rule_count = 9;
ParseItem parse_table[MAX_STR_LEN][MAX_ITEMS];
int item_count[MAX_STR_LEN];
char str[MAX_STR_LEN];

void add_item(int pos, ParseItem item) {
    for (int i = 0; i < item_count[pos]; ++i) {
        ParseItem *current = &parse_table[pos][i];
        if (current->left == item.left && strcmp(current->parsed, item.parsed) == 0 && 
            strcmp(current->remaining, item.remaining) == 0 && current->origin == item.origin) {
            return;
        }
    }
    parse_table[pos][item_count[pos]++] = item;
}

int is_complete(ParseItem item) {
    return item.remaining[0] == '\0';
}

void predict(ParseItem item, int pos) {
    char non_terminal = item.remaining[0];
    for (int i = 0; i < rule_count; ++i) {
        if (rules[i].left == non_terminal) {
            ParseItem new_item;
            new_item.left = rules[i].left;
            strcpy(new_item.parsed, "");
            strcpy(new_item.remaining, rules[i].right);
            new_item.origin = pos;
            add_item(pos, new_item);
        }
    }
}

void scan(ParseItem item, int pos) {
    if (str[pos] == item.remaining[0]) {
        ParseItem new_item = item;
        char parsed[10];
        strncpy(parsed, item.remaining, 1);
        parsed[1] = '\0';
        strcat(new_item.parsed, parsed);
        memmove(new_item.remaining, item.remaining + 1, strlen(item.remaining));
        add_item(pos + 1, new_item);
    }
}

void complete(ParseItem item, int pos) {
    for (int i = 0; i < item_count[item.origin]; ++i) {
        ParseItem origin_item = parse_table[item.origin][i];
        if (origin_item.remaining[0] == item.left) {
            ParseItem new_item = origin_item;
            char parsed[10];
            strncpy(parsed, origin_item.remaining, 1);
            parsed[1] = '\0';
            strcat(new_item.parsed, parsed);
            memmove(new_item.remaining, origin_item.remaining + 1, strlen(origin_item.remaining));
            add_item(pos, new_item);
        }
    }
}

int parse(char *input, int len) {
    ParseItem start_item = {'P', "", "S", 0};
    add_item(0, start_item);

    for (int pos = 0; pos <= len; ++pos) {
        for (int i = 0; i < item_count[pos]; ++i) {
            ParseItem item = parse_table[pos][i];

            if (!is_complete(item)) {
                if (item.remaining[0] >= 'A' && item.remaining[0] <= 'Z') {
                    predict(item, pos);
                } else {
                    scan(item, pos);
                }
            } else {
                complete(item, pos);
            }
        }
    }

    for (int i = 0; i < item_count[len]; ++i) {
        if (parse_table[len][i].left == 'P' && is_complete(parse_table[len][i]) && parse_table[len][i].origin == 0) {
            return 1;
        }
    }

    return 0;
}

int main() {
    printf("Enter input: ");
    scanf("%s", str);
    int len = strlen(str);

    if (parse(str, len)) {
        printf("Valid Input \n");
    } else {
        printf("Not Valid Input \n");
    }

    return 0;
}
