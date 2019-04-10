/**
 * 	\addtogroup nvm-exercise
 * @{
 */

/**
 * \defgroup nvm-arch Architecture specific NVM device interface.
 * @{
 *
 * The architecture specific NVM device interface implements the platform specific NVM device.
 *
 */

/**
 * \file
 *         @brief       Header file for the architecture specific NVM device interface.
 * \author
 *         Peter Ruckebusch <peter.ruckebusch@gmail.com>
 */

#ifndef __NVM_ARCH_H__
#define __NVM_ARCH_H__

#include <stdint.h>
#include <stddef.h>

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
nvm_arch_read(	long int offset,
				size_t len,
				void *ptr);

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
int
nvm_arch_update(long int offset,
				size_t len,
				const void *ptr);

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
int
nvm_arch_append(long int offset,
				size_t len,
				const void *ptr);

#endif /*__NVM_ARCH_H__ */
/** @} */
/** @} */