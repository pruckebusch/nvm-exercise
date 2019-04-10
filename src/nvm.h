#ifndef __NVM_H__
#define __NVM_H__

#include <stdint.h>

int
nvm_read(	uint32_t offset,
			uint8_t len,
			void *ptr);

int
nvm_update(	uint32_t offset,
			uint8_t len,
			const void *ptr);

int
nvm_append(	uint32_t offset,
			uint8_t len,
			const void *ptr);

#endif /*__NVM_H__ */