/**
 * \addtogroup nvm-hil
 * @{
 */

/**
 * \file
 *         @brief       Implementation of hardware independent NVM device interface.
 * \author
 *         Peter Ruckebusch <peter.ruckebusch@gmail.com>
 */

// Implements following header(s)
#include "nvm.h"

// Uses following header(s)
#include "nvm-arch.h"

/**
 * @brief      Copy len bytes into pointer from NVM starting from offset.
 *
 * @param[in]  offset  The offset in the NVM were the read operation should start.
 * @param[in]  len     The length of the read operation (number of bytes).
 * @param[out] ptr     The pointer to which len bytes should be copied.
 *
 * @return     0: SUCCESS
 * @return     1: ERROR
 */
int
nvm_read(uint32_t offset, uint8_t len, void *ptr)
{
	return nvm_arch_read(offset, len, ptr);
}

/**
 * @brief      Update NVM by copying len bytes read from pointer to NVM starting from offset.
 *
 * @param[in]  offset  The offset in the NVM were the update operation should start.
 * @param[in]  len     The length of the update operation (number of bytes).
 * @param[out] ptr     The pointer from which len bytes should be copied.
 *
 * @return     0: SUCCESS
 * @return     1: ERROR
 */
int nvm_update(uint32_t offset, uint8_t len, const void *ptr)
{
	return nvm_arch_update(offset, len, ptr);
}

/**
 * @brief      Append to NVM by copying len bytes read from pointer to NVM starting from offset.
 *
 * @param[in]  offset  The offset in the NVM were the append operation should start.
 * @param[in]  len     The length of the append operation (number of bytes).
 * @param[out] ptr     The pointer from which len bytes should be copied.
 *
 * @return     0: SUCCESS
 * @return     1: ERROR
 */
int nvm_append(uint32_t offset, uint8_t len, const void *ptr)
{
	return nvm_arch_append(offset, len, ptr);
}

/** @} */