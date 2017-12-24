#include "MemoryLeakDetector.h"
int main() {

    int *ptr = (int*)malloc(100);
    int *ptr1 = (int*)malloc(100);
    int *ptr2 = (int*)malloc(100);
    int *ptr3 = (int*)malloc(100);

    free(ptr);
    atexit(reportMemoryLeak);

    return 0;
}