/* auto-generated by gen_syscalls.py, don't edit */

#include <syscalls/cache.h>

extern int z_vrfy_sys_cache_instr_all(int op);
uintptr_t z_mrsh_sys_cache_instr_all(uintptr_t arg0, uintptr_t arg1, uintptr_t arg2,
		uintptr_t arg3, uintptr_t arg4, uintptr_t arg5, void *ssf)
{
	_current->syscall_frame = ssf;
	(void) arg1;	/* unused */
	(void) arg2;	/* unused */
	(void) arg3;	/* unused */
	(void) arg4;	/* unused */
	(void) arg5;	/* unused */
	union { uintptr_t x; int val; } parm0;
	parm0.x = arg0;
	int ret = z_vrfy_sys_cache_instr_all(parm0.val);
	_current->syscall_frame = NULL;
	return (uintptr_t) ret;
}
