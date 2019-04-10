// Implements following header(s)
#include "nvm.h"

// Uses following header(s)
#include "nvm-arch.h"

int
nvm_read(uint32_t offset, uint8_t len, void *ptr)
{
	return nvm_arch_read(offset, len, ptr);
}

int nvm_update(uint32_t offset, uint8_t len, const void *ptr)
{
	return nvm_arch_update(offset, len, ptr);
}

int nvm_append(uint32_t offset, uint8_t len, const void *ptr)
{
	return nvm_arch_append(offset, len, ptr);
}