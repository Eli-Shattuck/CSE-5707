#include <stdio.h>
#include <stdlib.h>
#include <thread>

int main() {
    uint64_t x = 65;

    printf("%u\n", x / 64u);

    return 0;
}