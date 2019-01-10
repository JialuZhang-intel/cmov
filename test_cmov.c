
#define FUNC_NAME test_cmov_reg
#define ASM_CMOV_REG 1
#include "test_base.h"
#undef ASM_CMOV_REG
#undef FUNC_NAME

#define FUNC_NAME test_cmov_mem
#define ASM_CMOV_MEM 1
#include "test_base.h"
#undef ASM_CMOV_MEM
#undef FUNC_NAME

#define FUNC_NAME test_cmov_mem_with_use
#define ASM_CMOV_MEM_WITH_USE 1
#include "test_base.h"
#undef ASM_CMOV_MEM_WITH_USE
#undef FUNC_NAME

