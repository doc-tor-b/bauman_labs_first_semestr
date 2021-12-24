//
// Created by doctor on 23.12.2021.
//

#include <stdio.h>
#include <stdlib.h>

#define FILE_PATH "rk3_final/data.bin"

#define GET_ALL_DATA_FROM_FILE 1
#define GET_DATA_ABOUT_SOME_STUDENT 2
#define ADD_NEW_STUDENT_DATA 3
#define DELETE_ALL_DATA_IN_FILE 4
#define CLOSE_PROGRAM 5

#define OPEN 1
#define NOT_OPEN 0;

typedef struct {
    char surname[20];
    char name[20];
    char second_surname[20];
    char data[20];
    char first_exam[20];
    char second_exam[20];
    char third_exam[20];
    char fourth_exam[20];
} Student;

void get_data(Student student);
Student add_data();

int main() {
    FILE* fd = NULL;
    puts("Trying to open data file");
    int flag_file = NOT_OPEN;
    fd = fopen(FILE_PATH, "r+b");
    if (fd == NULL) {
        puts("File is not exist");
        puts("Trying to create data file");
        fd = fopen(FILE_PATH, "w+b");
        if (fd == NULL) {
            perror("Can not to create data file");
            return 0;
        }
    }
    flag_file = OPEN;
    int action = 0;
    int result = 0;
    Student student = {};
    while (true) {
        puts("Enter the action:");
        puts("\t1 Get all data from file");
        puts("\t2 Get data about students which born in the same day");
        puts("\t3 Add new student data");
        puts("\t4 Delete all data in file");
        puts("\t5 Close program");
        scanf("%d", &action);
        switch (action) {
            case GET_ALL_DATA_FROM_FILE:
                if (flag_file) {
                    fseek(fd, 0, SEEK_SET);
                    while (fread(&student, sizeof(Student), 1, fd) != 1) {
                        get_data(student);
                    }
                }
                break;
            case GET_DATA_ABOUT_SOME_STUDENT:
                break;
            case ADD_NEW_STUDENT_DATA:
                if (flag_file) {
                    fseek(fd, 0, SEEK_END);
                    student = add_data();
                    result = fwrite(&student, sizeof(student), 1, fd);
                    if (result != 1) {
                        puts("Error of add new student to file");
                    } else {
                        puts("Student was added");
                    }
                }
                break;
            case DELETE_ALL_DATA_IN_FILE:
                break;
            case CLOSE_PROGRAM:
                if (flag_file == OPEN) {
                    fclose(fd);
                    flag_file = NOT_OPEN;
                }
                return 0;
        }
    }
}

void get_data(Student student) {
    printf("%s %s %s %s %s %s %s\n",
           student.surname,
           student.name,
           student.data,
           student.first_exam,
           student.second_exam,
           student.third_exam,
           student.fourth_exam);
}

Student add_data() {
    Student st = {};
    puts("Enter the:");
    puts("\tSurname");
    puts("\tName");
    puts("\tSecond surname");
    puts("\tBirthday");
    puts("\tFirst exam");
    puts("\tSecond exam");
    puts("\tThird exam");
    puts("\tFourth exam");
    scanf("%s %s %s %s %s %s %s %s",
          st.surname,
          st.name,
          st.second_surname,
          st.data,
          st.first_exam,
          st.second_exam,
          st.third_exam,
          st.fourth_exam);
    return st;
}