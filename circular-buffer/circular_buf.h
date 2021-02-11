#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Change buffer_size based on single data size */
typedef uint32_t buffer_val_size; 

/* Handle type of circular buffer */
typedef uint32_t *cbuf_handler;


/* Initialize Circular Buffer 
	Args : 
	*buffer                 : Pointer for circular buffer. User's allocated memory to be used as c_buffer. 
	buff_elements_size		: Number of max elements which can be stored in the buffer.
	total_allocated_memory  : Memory requried in bytes to be alloacted for the buffer. This value should be
							  calculated with function get_total_allocated_memory_required.
	Return : Circular buffer handler.
*/

cbuf_handler circular_buffer_init(buffer_val_size *buffer, size_t buff_elements_size, size_t total_allocated_memory);

/*
Returns required buffer size in bytes for given number of elements: buff_size. 
*/
size_t get_total_allocated_memory_required( size_t buff_size);

/* Add data to Buffer */
void circular_buffer_put(cbuf_handler cbuf, buffer_val_size data);

/* Retrieve a value from the buffer 
   Aargument data will hold get data address
   Return true in case of success */
bool circular_buffer_get(cbuf_handler cbuf, buffer_val_size * data);

/* Reset Circular data Buffer*/
void circular_buffer_reset(cbuf_handler cbuf);

/* Checks if the buffer is full */
bool circular_buffer_full(cbuf_handler cbuf);

/* Checks if the buffer is empty */
bool circular_buffer_empty(cbuf_handler cbuf);

/* Checks total capacity of the buffer */
size_t circular_buffer_capacity(cbuf_handler cbuf);

/*  Check the number of data(elements) stored in the buffer */
size_t circular_buffer_size(cbuf_handler cbuf);

#endif //CIRCULAR_BUFFER_H_