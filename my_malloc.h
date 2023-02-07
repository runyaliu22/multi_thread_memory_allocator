#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;




struct node {
  size_t size;
  struct node * next;
  struct node * prev;
};

typedef struct node Metadata;

__thread Metadata * head_unlock = NULL;

Metadata * head_lock = NULL;



size_t data_segment = 0;
size_t data_segment_free = 0;


void * ts_malloc_lock(size_t size);
void ts_free_lock(void* ptr);

void * ts_malloc_nolock(size_t size);
void ts_free_nolock(void* ptr);



void check_adjacent(Metadata* curr, Metadata* head);

void * reuse_block(size_t size, Metadata * p, int sbrk_lock, Metadata* head);
//void * reuse_block(size_t size, Metadata * p);

void * allocate_new_block(size_t size, int sbrk_lock);
//void * allocate_new_block(size_t size);


void add_to_ll(Metadata * p, Metadata* head);
void remove_from_ll(Metadata * p, Metadata* head);


//void * ff_malloc(size_t size);
void ff_free(void * ptr, Metadata* head);

void * bf_malloc(size_t size, int sbrk_lock, Metadata* head);
//void * bf_malloc(size_t size);

void bf_free(void * ptr, Metadata* head);



unsigned long get_data_segment_size();             
unsigned long get_data_segment_free_space_size();  
