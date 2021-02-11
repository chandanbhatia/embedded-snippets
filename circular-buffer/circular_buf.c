#include "circular_buf.h"

// The definition of our circular buffer structure is hidden from the user
typedef struct {
  buffer_val_size *buffer;
  size_t head;
  size_t tail;
  size_t max; //of the buffer
  bool full;
} cbuf_struct;

typedef struct {
  cbuf_struct cbuf_struct_t;
  buffer_val_size bufferDataStart;
} cbuf_struct_complete;

size_t get_total_allocated_memory_required( size_t buff_size){
  printf(" cbuf_struct size: %ld, size_t size: %ld \n", sizeof(cbuf_struct),  sizeof(size_t) );
  return( (sizeof(cbuf_struct)) +  ( sizeof(size_t) * buff_size) );
}

cbuf_handler circular_buffer_init(buffer_val_size *buffer, size_t buff_elements_size, size_t total_allocated_memory){
  assert(buffer && buff_elements_size);

  assert(total_allocated_memory >= get_total_allocated_memory_required (buff_elements_size) );
  cbuf_struct * s_cbuf = ( cbuf_struct *) buffer;
  cbuf_struct_complete  *s_cbuf_complete =  ( cbuf_struct_complete *) buffer;

 /* buffer will start after structure members */
  s_cbuf->buffer = &s_cbuf_complete->bufferDataStart;
  s_cbuf->max = buff_elements_size;
  circular_buffer_reset((cbuf_handler)s_cbuf);

  assert(circular_buffer_empty((cbuf_handler)s_cbuf));

  return (cbuf_handler)s_cbuf;
}

void circular_buffer_reset(cbuf_handler cbuf) {
  cbuf_struct *s_cbuf = (cbuf_struct *)cbuf;
  assert(cbuf);

  s_cbuf->head = 0;
  s_cbuf->tail = 0;
  s_cbuf->full = false;
}

bool circular_buffer_full(cbuf_handler cbuf) {
  cbuf_struct *s_cbuf = (cbuf_struct *)cbuf;
  assert(s_cbuf);

  return s_cbuf->full;
}

bool circular_buffer_empty(cbuf_handler cbuf) {
  cbuf_struct *s_cbuf = (cbuf_struct *)cbuf;
  assert(s_cbuf);

  return (!s_cbuf->full && (s_cbuf->head == s_cbuf->tail));
}

size_t circular_buffer_size(cbuf_handler cbuf) {
  cbuf_struct *s_cbuf = (cbuf_struct *)cbuf;
  assert(s_cbuf);
  size_t Size;

  if (!s_cbuf->full) {
    if (s_cbuf->head >= s_cbuf->tail) {
      Size = (s_cbuf->head - s_cbuf->tail);
    } else {
      Size = (s_cbuf->max + s_cbuf->head - s_cbuf->tail);
    }
  } else {
    Size = s_cbuf->max;
  }
  return Size;
}

size_t circular_buffer_capacity(cbuf_handler cbuf) {
  cbuf_struct *s_cbuf = (cbuf_struct *)cbuf;
  assert(s_cbuf);

  return s_cbuf->max;
}


void circular_buffer_put(cbuf_handler cbuf, buffer_val_size data) {
  cbuf_struct *s_cbuf = (cbuf_struct *)cbuf;
  assert(s_cbuf && s_cbuf->buffer);

  s_cbuf->buffer[s_cbuf->head] = data;

  if (s_cbuf->full) {
    s_cbuf->tail = (s_cbuf->tail + 1) % s_cbuf->max;
  }

  s_cbuf->head = (s_cbuf->head + 1) % s_cbuf->max;
  s_cbuf->full = (s_cbuf->head == s_cbuf->tail);

}

bool circular_buffer_get(cbuf_handler cbuf, buffer_val_size *data) {
  cbuf_struct *s_cbuf = (cbuf_struct *)cbuf;
  assert(s_cbuf && data && s_cbuf->buffer);

  bool returnVal = false;

  if (!circular_buffer_empty(cbuf)) {
    *data = s_cbuf->buffer[s_cbuf->tail];
     s_cbuf->full = false;
     s_cbuf->tail = (s_cbuf->tail + 1) % s_cbuf->max;
    returnVal = true;
  }

   return returnVal;
}