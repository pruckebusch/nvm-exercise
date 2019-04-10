#ifndef __GP_NVM_H__
#define __GP_NVM_H__

#include <stdint.h>
#include <stddef.h>

typedef unsigned char uint8_t;
typedef uint8_t gp_nvm_attr_id_t;
typedef uint8_t gp_nvm_result_t;

enum GP_NVM_RESULT_CODE
{
	GP_NVM_SUCCESS,
	GP_NVM_FAIL,
	GP_NVM_ATTR_NOT_FOUND,
	GP_NVM_ATTR_LEN_DIFF,
	GP_NVM_MEM_FULL,
	GP_NVM_MEM_ERROR,
};

void
gp_nvm_init();

gp_nvm_result_t 
gp_nvm_get_attribute(	gp_nvm_attr_id_t attr_id,
						uint8_t* p_length,
						uint8_t* p_value);

gp_nvm_result_t
gp_nvm_set_attribute(	gp_nvm_attr_id_t attr_id,
						uint8_t length, 
						uint8_t* p_value);

#endif /* __GP_NVM_H__ */