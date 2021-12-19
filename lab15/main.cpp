//
// Created by doctor on 16.12.2021.
//
#include <stdio.h>
#include <string.h>

typedef struct {
    char mark[20];
    char deployer[20];
    char type[20];
    int year;
    int cost;
} Car;

#define READ_DATA_FROM_FILE 1
#define WRITE_DATA_TO_FILE 2
#define DELETE_DATA_FROM_FILE 3
#define DELETE_FILE 4
#define EXIT 5
#define FILENAME "lab15/data.bin"

int main() {
    int action = 0;
    Car car_write = {};
    Car car_read = {};
    FILE* fd = nullptr;
    int result = 0;
    while (true) {
        puts("Enter the action:");
        puts("1 - get data about cars");
        puts("2 - add car data");
        puts("3 - clear the file");
        puts("4 - delete the file");
        puts("5 - exit");
        scanf("%d", &action);
        switch (action) {
            case READ_DATA_FROM_FILE:
                fd = fopen(FILENAME, "rb");
                if (fd == NULL) {
                    perror("can't open file for read");
                    return -1;
                }
                puts("Cars older than 5 years and not manufactured in China");
                while (fread(&car_read, sizeof(car_read), 1, fd) == 1) {
                    if (car_read.year < 2016 && !strcmp(car_read.deployer, "China")) {
                        printf("%s %s %s %d %d\n",
                               car_read.mark,
                               car_read.deployer,
                               car_read.type,
                               car_read.year,
                               car_read.cost);
                    }
                }
                fclose(fd);
                break;
            case WRITE_DATA_TO_FILE:
                fd = fopen(FILENAME, "a+b");
                if (fd == NULL) {
                    perror("can't open file for write");
                    return -1;
                }
                car_write = {'\0'};
                puts("Enter the mark, deployer, type, year, cost of car:");
                scanf("%s %s %s %d %d",
                      car_write.mark,
                      car_write.deployer,
                      car_write.type,
                      &car_write.year,
                      &car_write.cost);
                fwrite(&car_write, sizeof(car_write), 1, fd);
                fclose(fd);
                break;
            case DELETE_DATA_FROM_FILE:
                fd = fopen(FILENAME, "wb");
                if (fd == NULL) {
                    perror("can't open file for delete all data");
                    return -1;
                }
                fclose(fd);
                puts("The file has been cleared");
                break;
            case DELETE_FILE:
                result = remove(FILENAME);
                if (result) {
                    perror("removing was not success");
                    return -1;
                }
                puts("The file has been deleted");
                break;
            case EXIT:

                return 0;
        }
    }
}