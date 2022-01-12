//
// Created by doctor on 10.01.2022.
//

#include <stdio.h>
#include <malloc.h>

#define PRINT_ALL_DATA_FROM_FILE 1
#define PRINT_DATA_ABOUT 2
#define ADD_NEW_STUDENT 3
#define DELETE_ALL_DATA 4
#define EXIT 5

typedef struct {
    char name[20];
    char surname[20];
    char date[20];
    int val;
} Student;

void print_student_data(Student stud);
Student scan_student();

int main() {
    Student stud = {};
    Student* students = NULL;
    FILE* fd = fopen("exam_list/text.bin", "r+b");
    if (fd == NULL) {
        fd = fopen("exam_list/text.bin", "w+b");
        if (fd == NULL) {
            puts("can't open file");
            return 0;
        }
    }
    int action = 0;
    while (true) {
        scanf("%d", &action);
        switch (action) {
            case PRINT_ALL_DATA_FROM_FILE:
                fseek(fd, 0, SEEK_SET);
                while (fread(&stud, sizeof(stud), 1, fd) == 1) {
                    print_student_data(stud);
                }
                break;
            case PRINT_DATA_ABOUT: {
                fseek(fd, 0, SEEK_END);
                int bytes = ftell(fd);
                fseek(fd, 0, SEEK_SET);
                students = (Student*)malloc(bytes);
                if (students == NULL) {
                    puts("can't allocate memory");
                    return 1;
                }
                for (int i = 0; i < bytes / sizeof(stud); ++i) {
                    fread(&stud, sizeof(stud), 1, fd);
                    students[i] = stud;
                }
                int* res = NULL;
                int len = 0;
                for (int i = 0; i < bytes / sizeof(stud); ++i) {
                    int value = students[i].val;
                    int pos = 0;
                    int flag = 0;
                    int brflag = 0;
                    for (int k = 0; k < len; ++k) {
                        if (res[k] == value) {
                            brflag = 1;
                        }
                    }
                    if (brflag) {
                        continue;
                    }
                    res = (int*)realloc(res, len + sizeof(int));
                    res[len] = value;
                    len ++;
                    for (int j = 0; j < bytes / sizeof(stud); ++j) {
                        if (students[j].val == value && flag == 0) {
                            flag = 1;
                            pos = j;
                        } else if (students[j].val == value && flag == 1) {
                            puts(students[pos].surname);
                            puts(students[j].surname);
                            flag = 2;
                        } else if (students[j].val == value && flag == 2) {
                            puts(students[j].surname);
                        }
                    }
                    puts("--------");
                }
                free(res);
                free(students);
                break;
            }
            case ADD_NEW_STUDENT:
                fseek(fd, 0, SEEK_END);
                stud = scan_student();
                fwrite(&stud, sizeof(stud), 1, fd);
                break;
            case DELETE_ALL_DATA:
                freopen("exam_list/text.bin", "w+b", fd);
                if (fd == NULL) {
                    puts("can't open file");
                    return 1;
                }
                break;
            case EXIT:
                fclose(fd);
                return 0;
        }
    }
}

void print_student_data(Student stud) {
    printf("%s %s %s %d\n",
           stud.name,
           stud.surname,
           stud.date,
           stud.val);
}

Student scan_student() {
    Student stud = {};
    scanf("%s %s %s %d",
          stud.name,
          stud.surname,
          stud.date,
          &stud.val);
    return stud;
}