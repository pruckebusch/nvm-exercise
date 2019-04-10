/**
 * \addtogroup nvm-arch
 * @{
 */

/**
 * \file
 *         @brief       Implementation of architecture specific NVM device interface.
 * \author
 *         Peter Ruckebusch <peter.ruckebusch@gmail.com>
 */

// Implements following header(s)
#include "nvm-arch.h"

// Uses following header(s)
#include <stdio.h>

/**
 * @brief      This operation checks if the value that was written is correct after the write operation.
 *
 * @param[in]  offset  The offset in the NVM were the attribute was written.
 * @param[in]  len     The length of the attribute (number of bytes).
 * @param[in]  ptr_in  The pointer were the value was copied from.
 * @param[in]  nvm     Pointer to the nvm FILE
 *
 * @return     0: SUCCESS
 * @return     1: ERROR
 */
int
_nvm_arch_check_write_operation(long int offset,
                                size_t len,
                                const void* ptr_in,
                                FILE *nvm)
{
  // skip offset from beginning and check if offset is correct
  int ret = fseek(nvm, offset, SEEK_SET);
  if( ret ){
    fprintf(stderr, "Illegal offset, err %d\n", ret);
    return 1;
  }
  int i = 0;
  while( i<len ){
    uint8_t data = 0;
    size_t nmemb = fread(&data, 1, 1, nvm);
    if( nmemb != 1 ){
      fprintf(stderr, "iter %d Num memb don't match can't read: %lu\n",i , nmemb);
      return 1;
    }
    if( data != ((uint8_t*) ptr_in)[i] ){
      fprintf(stderr, "data doesnt match: %u != %u\n", data, ((uint8_t*) ptr_in)[i]);
      return 1;
    }
    i++;
  }
  return 0;
}

/**
 * @brief      Copy len bytes into pointer from NVM starting at offset.
 *
 * @param[in]  offset  The offset in the NVM were the read operation should start.
 * @param[in]  len     The length of the read operation (number of bytes).
 * @param[out] ptr     The pointer to which len bytes should be copied.
 *
 * @return     0: SUCCESS
 * @return     1: ERROR
 */
int
nvm_arch_read(long int offset,
              size_t len,
              void *ptr)
{
  // open file in binary read mode.
  FILE *nvm = fopen("nvm.bin", "rb");
  
  // check if file exists
  if( nvm == NULL ){
    fprintf(stderr, "Can't open NVM file\n");
    return 1;
  }

  // skip offset from beginning and check if offset is correct
  int ret = fseek(nvm, offset, SEEK_SET);
  if( ret ){
    fprintf(stderr, "Illegal offset, err %d\n", ret);
    fclose(nvm);
    return 1;
  }
  
  // now we can read the record from the file
  size_t nmemb = fread(ptr, len, 1, nvm);
  if( nmemb != 1 ){
    fprintf(stderr, "Num memb don't match can't read: %lu\n", nmemb);
    fclose(nvm);
    return 1;
  }

  fclose(nvm);
  return 0;
}

/**
 * @brief      Update NVM by copying len bytes read from pointer to NVM starting at offset.
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
                const void *ptr)
{
  // open file in binary read/write mode for updating.
  FILE *nvm = fopen("nvm.bin", "r+b");
  
  // check if file exists
  if( nvm == NULL ){
    fprintf(stderr, "Can't open NVM file\n");
    return 1;
  }

  // skip offset from beginning and check if offset is correct
  int ret = fseek(nvm, offset, SEEK_SET);
  if( ret ){
    fprintf(stderr, "Illegal offset, err %d\n", ret);
    fclose(nvm);
    return 1;
  }
  
  // now we can write the record to the file
  size_t nmemb = fwrite(ptr, len, 1, nvm);
  if( nmemb != 1 ){
    fprintf(stderr, "Num memb don't match can't write: %lu\n", nmemb);
    fclose(nvm);
    return 1;
  }

  //check if the write operation was successful
  if( _nvm_arch_check_write_operation(offset, len, ptr, nvm) != 0 ){
    fprintf(stderr, "Incorrect data after write\n");
    fclose(nvm);
    return 1;    
  }

  fclose(nvm);
  return 0;
}

/**
 * @brief      Append to NVM by copying len bytes read from pointer to NVM starting at offset.
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
                const void *ptr)
{
  // open file in binary read/write mode for appending.
  FILE *nvm = fopen("nvm.bin", "a+b");

  // check if file exists
  if( nvm == NULL ){
    fprintf(stderr, "Can't open NVM file\n");
    return 1;
  }

  // now we can append the record to the file
  size_t nmemb = fwrite(ptr, len, 1, nvm);
  if( nmemb != 1 ){
    fprintf(stderr, "Num memb don't match can't write: %lu\n", nmemb);
    fclose(nvm);
    return 1;
  }

  //check if the write operation was successful
  if( _nvm_arch_check_write_operation(offset, len, ptr, nvm) != 0 ){
    fprintf(stderr, "Incorrect data after write\n");
    fclose(nvm);
    return 1;    
  }

  fclose(nvm);
  return 0;
}

/** @} */