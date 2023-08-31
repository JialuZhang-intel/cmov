#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int A_SIZE = 2048;
const int ITERS = 500 * 1000;
const float PROBS[] = {0.0f, 0.05f, 0.1f, 0.15f,
                       0.2f, 0.25f, 0.3f, 0.35f,
                       0.4f, 0.45f, 0.5f, 0.55f,
                       0.6f, 0.65f, 0.7f, 0.75f,
                       0.8f, 0.85f, 0.9f, 0.95f,
                       1.0f};

int test_cmov_reg(int const *A, int const *B, int const n, int const iters);
int test_cmov_mem(int const *A, int const *B, int const n, int const iters);
int test_cmov_mem_with_use(int const *A, int const *B, int const n, int const iters);

int test_branch_reg(int const *A, int const *B, int const n, int const iters);
int test_branch_mem(int const *A, int const *B, int const n, int const iters);
int test_branch_mem_with_use(int const *A, int const *B, int const n, int const iters);

void check_eq(int expected, int value, const char *msg)
{
    if (expected != value)
    {
        printf("Check failed! %s, expected %d, value %d\n", msg, expected, value);
        fflush(stdout);
    }
}

int main(int argc, char *argv[])
{
    int i, j;
    int A[A_SIZE], A1[A_SIZE];
    int test_type = -1;
    if (argc == 2)
    {
        if (strcmp(argv[1], "branch_reg") == 0)
        {
            test_type = 0;
            printf("#probability;time_branch_reg;\n");
        }
        else if (strcmp(argv[1], "cmov_reg") == 0)
        {
            test_type = 1;
            printf("#probability;time_cmov_reg;\n");
        }
        else if (strcmp(argv[1], "branch_mem") == 0)
        {
            test_type = 2;
            printf("#probability;time_branch_mem;\n");
        }
        else if (strcmp(argv[1], "cmov_mem") == 0)
        {
            test_type = 3;
            printf("#probability;time_cmov_mem;\n");
        }
        else if (strcmp(argv[1], "time_branch_mem_with_use") == 0)
        {
            test_type = 4;
            printf("#probability;time_branch_reg;\n");
        }
        else if (strcmp(argv[1], "cmov_mem_with_use") == 0)
        {
            test_type = 5;
            printf("#probability;time_cmov_mem_with_use;\n");
        }
    }
    else
    {
        printf("#probability;time_branch_reg;time_cmov_reg;"
               "time_branch_mem;time_cmov_mem;"
               "time_branch_mem_with_use;time_cmov_mem_with_use\n");
    }

    srand(time(NULL));

    fflush(stdout);

    for (i = 0; i < sizeof(PROBS) / sizeof(float); ++i)
    {
        printf("%f", PROBS[i]);
        for (j = 0; j < A_SIZE; ++j)
        {
            float const rand1 = (float)rand() * (float)RAND_MAX;
            float const rand2 = (float)rand();
            float const rand_val = rand1 + rand2;
            float const rand_01 = rand_val / (float)RAND_MAX / (float)RAND_MAX;
            A[j] = rand_01 < PROBS[i];
            A1[j] = j;
        }

        clock_t before;
        volatile int sum;
        sum = sum;

        if (test_type == -1 || test_type == 0)
        {
            before = clock();
            sum = test_branch_reg(A, A1, A_SIZE, ITERS);
            printf(";%f", (float)(clock() - before) / (float)CLOCKS_PER_SEC);
            fflush(stdout);
        }

        if (test_type == -1 || test_type == 1)
        {
            before = clock();
            sum = test_cmov_reg(A, A1, A_SIZE, ITERS);
            printf(";%f", (float)(clock() - before) / (float)CLOCKS_PER_SEC);
            fflush(stdout);
        }

        if (test_type == -1 || test_type == 2)
        {
            before = clock();
            sum = test_branch_mem(A, A1, A_SIZE, ITERS);
            printf(";%f", (float)(clock() - before) / (float)CLOCKS_PER_SEC);
            fflush(stdout);
        }

        if (test_type == -1 || test_type == 3)
        {
            before = clock();
            sum = test_cmov_mem(A, A1, A_SIZE, ITERS);
            printf(";%f", (float)(clock() - before) / (float)CLOCKS_PER_SEC);
            fflush(stdout);
        }

        if (test_type == -1 || test_type == 4)
        {
            before = clock();
            sum = test_branch_mem_with_use(A, A1, A_SIZE, ITERS);
            printf(";%f", (float)(clock() - before) / (float)CLOCKS_PER_SEC);
            fflush(stdout);
        }

        if (test_type == -1 || test_type == 5)
        {
            before = clock();
            sum = test_cmov_mem_with_use(A, A1, A_SIZE, ITERS);
            printf(";%f", (float)(clock() - before) / (float)CLOCKS_PER_SEC);
            fflush(stdout);
        }

        printf("\n");
        fflush(stdout);
    }

    return 0;
}
