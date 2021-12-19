//
// Created by doctor on 19.12.2021.
//

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#define GET_ALL_DATA_FROM_FILE 1
#define ENTER_SOME_DAY 2
#define PUT_DATA_TO_FILE 3
#define DELETE_ALL_DATA 4
#define EXIT 5

#define DATAFILE "rk3/data.bin"

typedef struct {
    char surname[20];
    char name[20];
    char birthday[20];
    char first_exam[20];
    char second_exam[20];
    char third_exam[20];
    char fourth_exam[20];
} Student;

int print_data(Student st);

int main() {
    int action = 0;
    Student st {};
    FILE* fd = NULL;
    int result = 0;
    Student* students = NULL;
    while (true) {
        puts("Enter the action");
        scanf("%d", &action);
        putchar('\n');
        switch (action) {
            case GET_ALL_DATA_FROM_FILE:
                fd = fopen(DATAFILE, "rb");
                if (fd == NULL) {
                    perror("can't open file for read");
                    return -1;
                }
                while (fread(&st, sizeof(st), 1, fd) == 1) {
                    print_data(st);
                }
                fclose(fd);
                putchar('\n');
                break;
            case ENTER_SOME_DAY: {
                fd = fopen(DATAFILE, "rb");
                if (fd == NULL) {
                    perror("can't open file for read");
                    return -1;
                }
                fseek(fd, 0, SEEK_END);
                size_t size = ftell(fd);
                fseek(fd, 0, SEEK_SET);
                students = (Student*) malloc(size/sizeof(Student) * sizeof(Student));
                if (students == NULL) {
                    perror("malloc fault");
                    return -1;
                }

                int i = 0;
                while (fread(&st, sizeof(st), 1, fd) == 1) {
                    students[i] = st;
                    ++i;
                }
                int flag_no_data = 0;
                for (int i = 1; i < 32; ++i) {
                    int flag = 0;
                    int index = 0;
                    for(int j = 0; j < (malloc_usable_size((void*)students) / sizeof(students[0])); ++j) {
                        if (atoi(students[j].birthday) == i && !flag) {
                            puts("-------");
                            index = j;
                            flag = 1;
                        } else if (atoi(students[j].birthday) == i && flag == 1) {
                            print_data(students[index]);
                            print_data(students[j]);
                            flag = 2;
                            flag_no_data = 1;
                        } else if (atoi(students[j].birthday) == i && flag == 2) {
                            print_data(students[j]);
                        }
                    }
                }
                if (!flag_no_data) {
                    puts("Students with the same birthday were not found");
                }

                fclose(fd);
                free(students);
                putchar('\n');
                break;
            }
            case PUT_DATA_TO_FILE:
                fd = fopen(DATAFILE, "a+b");
                if (fd == NULL) {
                    perror("file open fault");
                    return 0;
                }

                puts("Enter the Surname and Name of student:");
                scanf("%s %s", st.surname, st.name);
                puts("Enter the birthday in format date.month.year:");
                scanf("%s", st.birthday);

                puts("Enter the first_exam");
                while (getchar() != '\n');
                fgets(st.first_exam, sizeof(st.first_exam), stdin);
                *strchr(st.first_exam, '\n') = '\0';

                puts("Enter the second_exam");
                fgets(st.second_exam, sizeof(st.second_exam), stdin);
                *strchr(st.second_exam, '\n') = '\0';

                puts("Enter the third_exam");
                fgets(st.third_exam, sizeof(st.third_exam), stdin);
                *strchr(st.third_exam, '\n') = '\0';

                puts("Enter the fourth_exam");
                fgets(st.fourth_exam, sizeof(st.fourth_exam), stdin);
                *strchr(st.fourth_exam, '\n') = '\0';

                result = fwrite(&st, sizeof(st), 1, fd);
                if (result != 1) {
                    perror("recording failed");
                    return -1;
                }
                fclose(fd);
                putchar('\n');
                break;
            case DELETE_ALL_DATA:
                fd = fopen(DATAFILE, "wb");
                if (fd == NULL) {
                    perror("can't open file for delete all data");
                    return -1;
                }
                fclose(fd);
                putchar('\n');
                break;
            case EXIT:
                putchar('\n');
                return 0;
        }
    }
}

int print_data(Student st) {
    printf("%s %s %s |%s| |%s| |%s| |%s|\n",
           st.surname,
           st.name,
           st.birthday,
           st.first_exam,
           st.second_exam,
           st.third_exam,
           st.fourth_exam);
    return 0;
}