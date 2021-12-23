//
// Created by doctor on 23.12.2021.
//

#include <stdio.h>
#include <string.h>

int main() {
    char orig_string[100] = {'\0'};
    puts("Enter the string:");
    fgets(orig_string, sizeof(orig_string) / sizeof(orig_string[0]), stdin);
    char* lexem = strtok(orig_string, " \n");
    char result_string[100] = {'\0'};
    strcat(result_string, lexem);
    int flag = 0;
    char buffer[50] = {'\0'};
    while (lexem != NULL) {
        if (flag) {
            sprintf(buffer, ", %s", lexem);
            strcat(result_string, buffer);
        }
        lexem = strtok(NULL, " \n");
        flag = 1;
    }
    puts("Result string:");
    puts(result_string);
    return 0;
}