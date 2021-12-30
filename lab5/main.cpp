//
// Created by doctor on 31.12.2021.
//

#include <stdio.h>
#include <assert.h>

int main () {
    printf("Enter the degree of two: ");
    int result = 0;
    int val = 0;
    result = scanf("%d", &val);
    assert(result == 1);
    int k = 0;
    while (val > 1) {
        ++k;
        val = val >> 1;
    }
    printf("%d\n", k);
    return 0;
}