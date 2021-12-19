//
// Created by doctor on 16.12.2021.
//

#include <stdio.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;
int main() {
    FILE* fd = fopen("lab14/dates.txt", "r");
    if (fd == NULL) {
        perror("file is not exist");
        return -1;
    }
    Date date = {0};
    int max_date = 0;
    while (fscanf(fd, "%d.%d.%d", &date.day, &date.month, &date.year) != EOF) {
        if (date.year > max_date) max_date = date.year;
    }
    printf("%d\n", max_date);
    fclose(fd);
    return 0;
}