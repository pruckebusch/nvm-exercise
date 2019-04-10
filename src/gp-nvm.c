// Implements following header(s)
#include "gp-nvm.h"

// Uses following header(s)
#include "nvm.h"
#include <stdio.h>
#include <string.h>

#define MAX_ATTRS 10

typedef struct attr_list_entry {
	gp_nvm_attr_id_t attr_id;
	uint8_t len;
	uint32_t offset;
} attr_list_entry_t;

typedef struct attr_list {
	uint8_t num_entries;
	uint32_t total_size;
	attr_list_entry_t entries[MAX_ATTRS];
} attr_list_t;

// Attribute list is also maintained in RAM memory for fast look-up
attr_list_t attrs;

void
gp_nvm_init()
{
	// clear whatever data is currently in attrs
	memset(&attrs, 0, sizeof(attr_list_t));
	// read correct attr_list from nvm
	if( nvm_read(0, sizeof(attr_list_t), &attrs) != 0 ){
		// attr list does not exist yet
		nvm_append(0, sizeof(attr_list_t), &attrs);
	}
	printf("GP-NVM: printing attr list at boot-time.\n");
	printf("\t num_entries = %u, total size = %u\n", attrs.num_entries, attrs.total_size);
	for( int i = 0; i<attrs.num_entries; i++ ){
		printf("\t [%d] = { attr_id: %u, offset: %u, len: %u\n", i, attrs.entries[i].attr_id, attrs.entries[i].offset, attrs.entries[i].len);
	}
}

attr_list_entry_t*
_gp_nvm_get_attr_list_entry(gp_nvm_attr_id_t attr_id)
{
	attr_list_entry_t* attr = NULL;
	int i = 0;
	while( i<attrs.num_entries && attr == NULL ){
		if( attrs.entries[i].attr_id == attr_id ){
			attr = &attrs.entries[i];
		}
		i++;
	}
	return attr;
}

gp_nvm_result_t
gp_nvm_get_attribute(	gp_nvm_attr_id_t attr_id,
						uint8_t* p_length,
						uint8_t* p_value)
{
	// lookup attr_id in attrs list
	attr_list_entry_t* attr = _gp_nvm_get_attr_list_entry(attr_id);
	if( attr == NULL ){
		return GP_NVM_ATTR_NOT_FOUND;
	}

	// read attr data from nvm and copy in value pointer
	if( nvm_read(attr->offset, attr->len, p_value) ){
		return GP_NVM_MEM_ERROR;
	}
	// copy len into len pointer
	*p_length = attr->len;

	return GP_NVM_SUCCESS;
}

gp_nvm_result_t
gp_nvm_set_attribute(	gp_nvm_attr_id_t attr_id,
						uint8_t length, 
						uint8_t* p_value)
{
	// lookup attr_id in attrs list
	attr_list_entry_t* attr = _gp_nvm_get_attr_list_entry(attr_id);

	//add attribute if it doesn't exist yet
	if(attr == NULL){
		// check if attr list can still grow
		if( attrs.num_entries == MAX_ATTRS ) {
			return GP_NVM_MEM_FULL;
		}

		// write attr to mem
		if( nvm_append(sizeof(attr_list_t) + attrs.total_size, length, p_value) != 0 ){
			return GP_NVM_MEM_ERROR;
		}

		// add new attr in list
		attrs.entries[attrs.num_entries].attr_id = attr_id;
		attrs.entries[attrs.num_entries].offset = sizeof(attr_list_t) + attrs.total_size;
		attrs.entries[attrs.num_entries].len = length;
		attrs.total_size += length;
		attrs.num_entries++;

		//update attr list in mem
		if( nvm_update(0, sizeof(attr_list_t), &attrs) != 0 ){
			// remove attr from list
			attrs.total_size -= length;
			attrs.num_entries--;
			return GP_NVM_MEM_ERROR;
		}
		return GP_NVM_SUCCESS;
	}

	// check if the lengths match (var length arrays are not possible)
	if( attr->len != length ){
		return GP_NVM_ATTR_LEN_DIFF;
	}

	// update attr data in nvm
	if( nvm_update(attr->offset, attr->len, p_value) != 0 ){
		return GP_NVM_MEM_ERROR;
	}

	return GP_NVM_SUCCESS;
}

// howto add var length arrays:
// option a) include max_length when setting attribute so enough mem can be allocated
// option b) move attr with higher offset backward/forward in NVM when length differs
// 			also update offsets in attr_list with int offset_diff = new_len - old_len 