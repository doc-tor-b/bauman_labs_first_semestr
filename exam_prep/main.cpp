//
// Created by doctor on 10.01.2022.
//
#include <stdio.h>

#define GET_ALL_DATA_FROM_FILE 1
#define GET_DATA_ABOUT_YONNER_18 2
#define ADD_NEW_STUDENT 3
#define DELETE_ALL_DATA_IN_FILE 4
#define EXIT 5

#define FILENAME "exam_prep/data.txt"

typedef struct {
    char name[20];
    char surname[20];
    int day;
    int month;
    int year;
} Student;

Student get_data_from_stdin();
void put_data_to_file(FILE* fd, const Student* stud);
void print_student_data(const Student* stud);
int read_data_from_file(FILE* fd, Student* stud);

int main () {
    FILE* fd = fopen(FILENAME, "r+");
    if (fd == NULL) {
        fd = fopen(FILENAME, "w+");
        if (fd == NULL) {
            perror("can't open data file");
        }
    }
    int action = 0;
    Student stud = {};
    while (true) {
        puts("Enter the action");
        scanf("%d", &action);
        switch (action) {
            case GET_ALL_DATA_FROM_FILE:
                fseek(fd, 0, SEEK_SET);
                while (read_data_from_file(fd, &stud) != EOF) {
                    print_student_data(&stud);
                }
                break;
            case GET_DATA_ABOUT_YONNER_18:
                fseek(fd, 0, SEEK_SET);
                while (read_data_from_file(fd, &stud) != EOF) {
                    if (stud.year > 2004 || (stud.year == 2004 && stud.month >= 1 && stud.day > 11)) {
                        print_student_data(&stud);
                    }
                }
                break;
            case ADD_NEW_STUDENT:
                fseek(fd, 0, SEEK_END);
                stud = get_data_from_stdin();
                put_data_to_file(fd, &stud);
                break;
            case DELETE_ALL_DATA_IN_FILE:
                freopen(FILENAME, "w+", fd);
                break;
            case EXIT:
                fclose(fd);
                return 0;
        }
    }
}

Student get_data_from_stdin() {
    Student stud = {};
    puts("Enter the name surname and date of born");
    if (scanf("%s %s %d.%d.%d", stud.name, stud.surname, &stud.day, &stud.month, &stud.year) != 5) {
        perror("can't read information");
    }
    return stud;
}

void put_data_to_file(FILE* fd, const Student* stud) {
    fprintf(fd, "%s %s %d.%d.%d\n", stud->name, stud->surname, stud->day, stud->month, stud->year);
}

void print_student_data(const Student* stud) {
    printf("%s %s %d.%d.%d\n", stud->name, stud->surname, stud->day, stud->month, stud->year);
}

int read_data_from_file(FILE* fd, Student* stud) {
    int result = fscanf(fd, "%s %s %d.%d.%d", stud->name, stud->surname, &stud->day, &stud->month, &stud->year);
    return result;
}