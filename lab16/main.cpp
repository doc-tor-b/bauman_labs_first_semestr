//
// Created by doctor on 22.12.2021.
//

#include <stdio.h>
#include <math.h>

#define CALCULATE 1
#define EXIT 2
#define FUNCTION


#ifdef FUNCTION

double func(double x) {
    return 7 * pow(((x) - 3), 5) - 4 * pow(((x) - 3), 3) - 2;
}
#else

#define func(x) 7 * pow(((x) - 3), 5) - 4 * pow(((x) - 3), 3) - 2

#endif

int main() {
    double x = 0;
    int action = 0;
    while (true) {
        puts("For calculating result -- enter 1");
        puts("For exit -- enter 2");
        scanf("%d", &action);
        switch (action) {
            case CALCULATE:
                puts("Enter the value:");
                scanf("%lf", &x);
                printf("%lf\n", func(x));
                break;
            case EXIT:
                return 0;
        }
    }
}