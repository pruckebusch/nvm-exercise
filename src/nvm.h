/**
 * 	\addtogroup nvm-exercise
 * @{
 */

/**
 * \defgroup nvm-hil Hardware independent NVM device interface.
 * @{
 *
 * The hardware independent NVM device interface enables creating a cross-platform general purpose NVM library.
 *
 */

/**
 * \file  nvm.h
 * \brief Header file for the hardware independent NVM device interface.
 * \author  Peter Ruckebusch <peter.ruckebusch@gmail.com>
 */

#ifndef __NVM_H__
#define __NVM_H__

#include <stdint.h>

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
nvm_read(	uint32_t offset,
			uint8_t len,
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
nvm_update(	uint32_t offset,
			uint8_t len,
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
nvm_append(	uint32_t offset,
			uint8_t len,
			const void *ptr);

#endif /*__NVM_H__ */
/** @} */
/** @} */