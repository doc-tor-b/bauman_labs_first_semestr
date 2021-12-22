//
// Created by makar on 22.12.2021.
//
#define ERROR_OPEN_FILE -3
#include <stdio.h>
#include <stdlib.h>

int get_counter(FILE* fd) {
    int counter = 0;
    rewind(fd);
    fread(&counter, sizeof(counter), 1, fd);
    return counter;
}

void set_counter(FILE* fd, int counter) {
    // int counter = 0;
    rewind(fd);
    fwrite(&counter, sizeof(counter), 1, fd);
    // return counter;
}

char user_appruve() {
    char yn = ' ';
    do {
        printf("Are you sure that you want to delete data in file?\n");
        int res = 0;
        res = scanf("%c", &yn);
        if (res == 0 || (yn != 'y' || yn != 'n')) {
            printf("Error input\n");
        }
    } while(yn != 'y' || yn !='n');
    return yn;
}
int main () {
    FILE* fp = NULL;
    char filename[] = "rk3_example/test.bin";
    int counter = 0;
    bool has_created = 0;
    int number = 0;
    int choice = 0;
    char yn = 0;
    do {
        has_created = 0;
        fp = fopen(filename, "rb+");
        if (fp == NULL) {
            printf("Error\n");
            printf("Trying to create file\n");
            fp = fopen(filename, "wb+");
            if (fp == NULL) {
                printf("Error\n");
                printf("Exit program\n");
                exit(ERROR_OPEN_FILE);

            } else {
                printf("File was created");
                fwrite(&counter, sizeof(counter), 1, fp);
            }
        }
        has_created = true;

    } while (!has_created);

    do {
        printf("User input:\n\tt1: for reading all data in file\n\t2: for write data to file\n\t3: for delete all data in file\n\t4: for delete file\n\t5: fot closing file\nпшеф");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                counter = get_counter(fp);
                // rewind(fp);
                // fread(&counter, sizeof(counter), 1, fp);
                if (counter > 0) {
                    printf("Data from file: \n");
                    for (int i = 0; i < counter; ++i) {
                        fread(&number, sizeof(number),1, fp);
                        printf("%d = %d\n", i , number);
                    }
                    printf("Read success");
                }
                break;
            case 2:
                printf("Input number:\n");
                if (scanf("%d", &number)) {
                    counter = get_counter(fp);
                    fseek(fp, sizeof(counter) + counter * sizeof(number), SEEK_SET);
                    fwrite(&number, sizeof(number), 1, fp);
                    counter++;
                    set_counter(fp, counter);
                }
                break;
            case 3:
                do {
                    printf("Are you sure that you want to delete data in file?\n");
                    int res = 0;
                    res = scanf("%c", &yn);
                    if (res == 0 || (yn != 'y' || yn != 'n')) {
                        printf("Error input\n");
                    }
                } while(yn != 'y' || yn != 'n');
                if (yn == 'y') {
                    freopen(filename, "wb+", fp);
                    counter = 0;
                    set_counter(fp, counter);
                    printf("File was cleared\n");
                } else {
                    printf("file was not cleared");
                }
                break;
            case 4:
                yn = user_appruve();
                if (yn == 'y') {
                    fclose(fp);
                    if (-1 == remove(filename)) {
                        printf("ERROR, file was not deleted\n");
                        fp = fopen(filename, "rb+");
                        if (fp == NULL) {
                            printf("Can not open file for read\n");
                        }
                    } else {
                        printf("file was not cleared");
                    }
                } else {
                    printf("File was not deleted\n");
                }
                break;
            case 5:
                if (fp) {
                    fclose(fp);
                }
                exit(1);
                break;

        }
    } while (fp != NULL);
    return 0;
}
