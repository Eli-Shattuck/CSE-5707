#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    const int N = atoi(argv[1]);
    const int R = atoi(argv[2]);

    printf("%d\n", N);
    for(int i = 0; i < N; i++) {
        printf("%d %d %d\n", i, rand() % R + 1, rand() % R + 1);
    }
    printf("%d\n", (int)(N*(R/2) * 0.7));

    return 0;
}