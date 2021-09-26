#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#include "Array.hpp"

static const int MAX_VALUE = 100;

int main() {
    srand(time(NULL));
    Array<int> a{1,2,3};
    for (int i = 0; i < MAX_VALUE / 10; i++) {
        a.push_back(rand() % MAX_VALUE);
    }

    for (auto num : a) printf("%d ", num);
    printf("\n");

    return 0;
}



