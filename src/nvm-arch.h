#ifndef __NVM_ARCH_H__
#define __NVM_ARCH_H__

#include <stdint.h>
#include <stddef.h>

int 
nvm_arch_read(	long int offset,
				size_t len,
				void *ptr);

int
nvm_arch_update(long int offset,
				size_t len,
				const void *ptr);

int
nvm_arch_append(long int offset,
				size_t len,
				const void *ptr);

#endif /*__NVM_ARCH_H__ */