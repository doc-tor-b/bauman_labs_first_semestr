//
// Created by doctor on 23.12.2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_PATH "rk3_final/data.bin"

#define GET_ALL_DATA_FROM_FILE 1
#define GET_DATA_ABOUT_SOME_STUDENT 2
#define ADD_NEW_STUDENT_DATA 3
#define DELETE_ALL_DATA_IN_FILE 4
#define CLOSE_PROGRAM 5

typedef struct {
    char surname[20];
    char name[20];
    char data[20];
    char first_exam[20];
    char second_exam[20];
    char third_exam[20];
    char fourth_exam[20];
} Student;

void get_data(Student student);
Student add_data();
int get_confirmation();

int main() {
    FILE* fd = NULL;
    puts("Trying to open data file");
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
    puts("Еhe file was opened successfully");
    int action = 0;
    int result = 0;
    Student student = {};
    Student* students = NULL;
    while (true) {
        puts("Enter the action:");
        puts("\t1 Get all data from file");
        puts("\t2 Get data about students which born in the same day");
        puts("\t3 Add new student data");
        puts("\t4 Delete all data in file");
        puts("\t5 Close program");
        scanf("%d", &action);
        switch (action) {
            case GET_ALL_DATA_FROM_FILE: {
                fseek(fd, 0, SEEK_SET);
                int flag = 0;
                puts("--------------");
                while (fread(&student, sizeof(Student), 1, fd) == 1) {
                    get_data(student);
                    flag = 1;
                }
                if (!flag) {
                    puts("File is empty");
                }
                puts("--------------");
                break;
            }
            case GET_DATA_ABOUT_SOME_STUDENT: {
                fseek(fd, 0, SEEK_END);
                long int pos = ftell(fd);
                if (pos == 0) {
                    puts("--------------");
                    puts("File is empty");
                    puts("--------------");
                    break;
                }
                students = (Student *) malloc(pos);
                fseek(fd, 0, SEEK_SET);
                for (int i = 0; i < pos / sizeof(Student); ++i) {
                    result = fread(&students[i], sizeof(students[i]), 1, fd);
                    if (result != 1) {
                        puts("Error of reading file");
                    }
                }
                int index = 0;
                int is_same_students_exist = 0;
                for (int d = 1; d <= 31; ++d) {
                    int flag_data = 0;
                    for (int i = 0; i < pos / sizeof(Student); ++i) {
                        if (atoi(students[i].data) == d && flag_data == 0) {
                            flag_data = 1;
                            index = i;
                        } else if (atoi(students[i].data) == d && flag_data == 1) {
                            puts("--------------");
                            get_data(students[index]);
                            get_data(students[i]);
                            flag_data = 2;
                            is_same_students_exist = 1;
                        } else if (atoi(students[i].data) == d && flag_data == 2) {
                            get_data(students[i]);
                        }
                    }
                }
                free(students);
                if (!is_same_students_exist) {
                    puts("--------------");
                    puts("There are no students with the same birthdays");
                    puts("--------------");
                } else {
                    puts("--------------");
                }
                break;
            }
            case ADD_NEW_STUDENT_DATA:
                fseek(fd, 0, SEEK_END);
                student = add_data();
                result = fwrite(&student, sizeof(student), 1, fd);
                if (result != 1) {
                    puts("--------------");
                    puts("Error of add new student to file");
                    puts("--------------");
                } else {
                    puts("--------------");
                    puts("Student was added");
                    puts("--------------");
                }
                break;
            case DELETE_ALL_DATA_IN_FILE:
                puts("Do you want delete all user data?");
                result = get_confirmation();
                if (result == 1) {
                    freopen(FILE_PATH, "w+b", fd);
                    puts("--------------");
                    puts("Data successfully deleted");
                    puts("--------------");
                } else {
                    puts("--------------");
                    puts("Action canceled");
                    puts("--------------");
                }
                break;
            case CLOSE_PROGRAM:
                fclose(fd);
                return 0;
        }
    }
}

void get_data(Student student) {
    printf("%s %s %s |%s| |%s| |%s| |%s|\n",
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
    puts("Enter the: Surname Name Birthday(day.month.year)");
    scanf("%s %s %s",
          st.name,
          st.surname,
          st.data);
    puts("First exam");
    while (getchar() != '\n');
    fgets(st.first_exam, sizeof(st.first_exam), stdin);
    *strchr(st.first_exam, '\n') = '\0';
    puts("Second exam");
    fgets(st.second_exam, sizeof(st.second_exam), stdin);
    *strchr(st.second_exam, '\n') = '\0';
    puts("Third exam");
    fgets(st.third_exam, sizeof(st.third_exam), stdin);
    *strchr(st.third_exam, '\n') = '\0';
    puts("Fourth exam");
    fgets(st.fourth_exam, sizeof(st.fourth_exam), stdin);
    *strchr(st.fourth_exam, '\n') = '\0';
    return st;
}

int get_confirmation() {
    char yn = 0;
    puts("Please confirm the action (y/n)");
    while (getchar() != '\n');
    while (true) {
        yn = getchar();
        if (yn == 'y') {
            return 1;
        } else if (yn == 'n') {
            return 0;
        } else {
            if (yn != '\n') {
                puts("Invalid value, repeat the input (y/n)");
            }
        }
    }
}