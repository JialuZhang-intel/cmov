void check_eq(int expected, int value, const char* msg);

int FUNC_NAME(int const* A, int const* B, int const n, int const iters)
{
    int i, j;
    int res, res2;

    res = 0;
    res2 = 0;
    for(i = 0; i < iters; ++i) {
        for(j = 0; j < n; ++j) {
            #ifdef CHECK
                int prev = res;
            #endif

            #ifdef ASM_CMOV_REG
                asm ("cmp %[A_j], 0\n\t"
                    "cmovne %[res], %[j]"
                    : [res] "+r"(res)
                    : [A_j] "m"(A[j]), [j] "r"(j)
                    : "cc");

            #elif ASM_CMOV_MEM
                asm ("cmp %[A_j], 0\n\t"
                    "cmovne %[res], %[B_j]"
                    : [res] "+r"(res)
                    : [A_j] "m"(A[j]), [B_j] "m"(B[j])
                    : "cc");

            #elif ASM_BRANCH_REG
                asm goto ("cmp %[A_j], 0\n\t"
                        "je %l[done]\n\t"
                        :
                        : [A_j] "m"(A[j])
                        : "cc"
                        : done);
                res = j;
                done:

            #elif ASM_BRANCH_MEM
                asm goto ("cmp %[A_j], 0\n\t"
                        "je %l[done]\n\t"
                        :
                        : [A_j] "m"(A[j])
                        : "cc"
                        : done);
                res = B[j];
                done:

            #elif ASM_CMOV_MEM_WITH_USE
                asm ("cmp %[A_j], 0\n\t"
                    "cmovne %[res], %[B_j]\n\t"
                    "add %[res2] ,4\n\t"
                    "add %[res2], 4\n\t"
                    "add %[res2], 4\n\t"
                    "add %[res2] ,4\n\t"
                    "add %[res2], 4\n\t"
                    "add %[res2] ,4\n\t"
                    "add %[res2], 4\n\t"
                    "add %[res2], 4"
                    : [res] "+r"(res), [res2] "+r"(res2)
                    : [A_j] "m"(A[j]), [B_j] "m"(B[j])
                    : "cc");

            #elif ASM_BRANCH_MEM_WITH_USE
                asm goto ("cmp %[A_j], 0\n\t"
                        "je %l[done]\n\t"
                        :
                        : [A_j] "m"(A[j])
                        : "cc"
                        : done);
                res = B[j];
                done:
                asm ("add %[res2], 4\n\t"
                    "add %[res2], 4\n\t"
                    "add %[res2], 4\n\t"
                    "add %[res2] ,4\n\t"
                    "add %[res2], 4\n\t"
                    "add %[res2] ,4\n\t"
                    "add %[res2], 4\n\t"
                    "add %[res2], 4"
                    : [res2] "+r"(res2)
                    : [B_j] "m"(B[j]));

            #else
                if(A[j]) {
                    res = j;
                }
            #endif

            #ifdef CHECK
                check_eq(A[j] ? j : prev, res, __func__);
            #endif

            continue;
        }
    }

    return res;
}
