//
// Created by doctor on 10.01.2022.
//

#include <stdio.h>

#define PRINT_ALL_DATA_FROM_FILE 1
#define PRINT_COUNT 2
#define ADD_NEW_ROW 3
#define EXIT 5

int main () {
    FILE* fd = fopen("first_exam/test.txt", "r+");
    if (fd == NULL) {
        fd = fopen("first_exam/test.txt", "w+");
        if (fd == NULL) {
            puts("can't open file");
            return 1;
        }
    }
    int action = 0;
    while (true) {
        scanf("%d", &action);
        switch (action) {
            case PRINT_ALL_DATA_FROM_FILE: {
                fseek(fd, 0, SEEK_END);
                int bytes = ftell(fd);
                fseek(fd, 0, SEEK_SET);
                for (int i = 0; i < bytes; ++i) {
                    char symb = fgetc(fd);
                    putchar(symb);
                }
                break;
            }
            case PRINT_COUNT: {
                fseek(fd, 0, SEEK_END);
                int flag_new_row = 1;
                int bytes = ftell(fd);
                fseek(fd, 0, SEEK_SET);
                int count = 0;
                for (int i = 0; i < bytes; ++i) {
                    char symb = fgetc(fd);
                    // printf("%c\n", symb);
                    if (symb == '\n') {
                        flag_new_row = 1;
                    } else if (flag_new_row == 1) {
                        if (symb == 'b' || symb == 'B') {
                            count++;
                        }
                        flag_new_row = 0;
                    }
                }
                printf("%d\n", count);
                break;
            }
            case ADD_NEW_ROW: {
                fseek(fd, 0, SEEK_END);
                char symb = getchar();
                while (symb != '\n') {
                    fputc(symb, fd);
                    symb = getchar();
                }
                fputc('\n', fd);
                break;
            }
            case EXIT:
                fclose(fd);
                return 0;
        }
    }
}