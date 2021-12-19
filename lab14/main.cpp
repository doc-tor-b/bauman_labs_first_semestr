//
// Created by doctor on 16.12.2021.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char surname[20];
    char name[20];
    char second_surname[20];
    char gender[7];
    char country[20];
    char day[3];
    char month[3];
    char year[5];
    char education[20];
    char number[15];
} Programmer;

int main() {
    FILE* fd = fopen("lab14/programmers.txt", "r");
    if (fd == NULL) {
        perror("file is not found");
        return -1;
    }
    Programmer person = {'\0'};
    int day = 0;
    int month = 0;
    int year = 0;
    while (EOF != fscanf(fd, "%s%s%s%s%s%2s.%2s.%4s%s%s",
                  person.surname,
                  person.name,
                  person.second_surname,
                  person.gender,
                  person.country,
                  person.day,
                  person.month,
                  person.year,
                  person.education,
                  person.number)) {
        day = atoi(person.day); // Эта конструкция необходима, чтобы в вывод программы попадали незначащие нули
        month = atoi(person.month);
        year = atoi(person.year);
        if (!day || !month || !year) {
            perror("incorrect date");
            return -1;
        }
        if (year > 1996 || (year == 1996 && month == 12 && day > 16)) {
            printf("%s %s %s %s %s %s.%s.%s %s %s\n",
                   person.surname,
                   person.name,
                   person.second_surname,
                   person.gender,
                   person.country,
                   person.day,
                   person.month,
                   person.year,
                   person.education,
                   person.number);
        }
    }
    fclose(fd);
    return 0;
}