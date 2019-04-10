/**
 * 	\addtogroup nvm-exercise
 * @{
 */

/**
 * \defgroup gp-nvm-lib General purpose NVM library.
 * @{
 *
 * The general purpose NVM library (gp-nvm-lib) allows store and obtain attributes from non-volatile memory devices.
 *
 * The gp-nvm-lib can be used to persistenly store attributes on a non-volatile memory device. 
 * For this purpose a getter and a setter function are provided.
 * The gp-nvm-lib maintains a list of attributes in RAM, indexed by the attribute ID.
 * Each entry contains the offset in the NVM and length of the attribute.
 * 
 * \todo Extend the attribute list with a CRC value for each attribute and for the list itself.
 * \todo Allow attributes that can have a variable size.  
 *
 */

/**
 * \file 	gp-nvm.h
 * \brief	Header file for the general purpose NVM library.
 * \author	Peter Ruckebusch <peter.ruckebusch@gmail.com>
 */

#ifndef __GP_NVM_H__
#define __GP_NVM_H__

#include <stdint.h>
#include <stddef.h>

/**
 * @brief      Attribute identifier.
 * 
 */
typedef uint8_t gp_nvm_attr_id_t;
/**
 * @brief      gp-nvm-lib operation result code.
 * 
 */
typedef uint8_t gp_nvm_result_t;

/**
 * @brief      Enumeration of result codes.
 * 
 */
enum GP_NVM_RESULT_CODE
{
	GP_NVM_SUCCESS,
	GP_NVM_FAIL,
	GP_NVM_ATTR_NOT_FOUND,
	GP_NVM_ATTR_LEN_DIFF,
	GP_NVM_MEM_FULL,
	GP_NVM_MEM_ERROR,
};

/**
 * @brief      Allows to search for an entry in the attribute list based on the attribute ID.
 *
 * @param[in]  attr_id  The att.ribute identifier
 *
 * @return     NULL: No entry was found.
 * @return     attr_list_entry_t*: Pointer to the entry in the attribute list.
 */
void
gp_nvm_init();

/**
 * @brief      Allows to search for an entry in the attribute list based on the attribute ID.
 *
 * @param[in]  attr_id  The att.ribute identifier
 *
 * @return     NULL: No entry was found.
 * @return     attr_list_entry_t*: Pointer to the entry in the attribute list.
 */
gp_nvm_result_t 
gp_nvm_get_attribute(	gp_nvm_attr_id_t attr_id,
						uint8_t* p_length,
						uint8_t* p_value);

/**
 * @brief      Get an attribute based on attribute ID.
 * 
 * This function searches for the attribute in NVM.
 * If found, it copies both the length and value into the respective pointers provides as parameters.
 *
 * @param[in]  attr_id   The attribute identifier
 * @param[out] p_length  Pointer were the length can be stored.
 * @param[out] p_value   Pointer were the value can be stored.
 *
 * @return     0: GP_NVM_SUCCESS
 * @return     2: GP_NVM_ATTR_NOT_FOUND
 * @return     5: GP_NVM_MEM_ERROR
 */
gp_nvm_result_t
gp_nvm_set_attribute(	gp_nvm_attr_id_t attr_id,
						uint8_t length, 
						uint8_t* p_value);

#endif /* __GP_NVM_H__ */

/** @} */
/** @} */