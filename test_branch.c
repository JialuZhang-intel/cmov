#define FUNC_NAME test_branch_reg
#define ASM_BRANCH_REG 1
#include "test_base.h"
#undef ASM_BRANCH_REG
#undef FUNC_NAME

#define FUNC_NAME test_branch_mem
#define ASM_BRANCH_MEM 1
#include "test_base.h"
#undef ASM_BRANCH_MEM
#undef FUNC_NAME

#define FUNC_NAME test_branch_mem_with_use
#define ASM_BRANCH_MEM_WITH_USE 1
#include "test_base.h"
#undef ASM_BRANCH_MEM_WITH_USE
#undef FUNC_NAME


