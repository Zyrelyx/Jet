//------------------------------------------------------------------------------
// memory_allocator.h
//
// Implements a memory allocation system which keeps track of allocated objects.
//
// Group: Elias Komar
//
// Author: 12315923
//------------------------------------------------------------------------------
//

#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <stdlib.h>     // malloc, free
#include <stdio.h>      // printf
#include <stdbool.h>    // bool

typedef struct _AllocatedObject_
{
  void* object_;                  // Pointer to the object
  void (*freeFunction_)(void**);   // Function pointer to free the object
} AllocatedObject;

#define INITIAL_SIZE 100  // initial size of allocatedObjects_ array
#define CHUNK_SIZE 10     // if no memory available, allocate this many new objects

typedef struct _MemoryAllocator_
{  
  AllocatedObject* alloced_objects_;     // Array of allocated objects
  int num_allocated_;                   // number of allocated objects
  int size_;                            // size of allocatedObjects_ array  
} MemoryAllocator;

void* myMalloc(size_t size, MemoryAllocator* allocator);
void myFree(void** object);
MemoryAllocator* createAllocator(void);
MemoryAllocator* addAllocatedObject(MemoryAllocator* allocator, void* object);
bool isObjectTracked(MemoryAllocator* allocator, void* object);
void freeAll(MemoryAllocator** allocator);
void freeAllocatorInside(MemoryAllocator* allocator);
void printAllocatedObjects(MemoryAllocator* allocator);

//------------------------------------------------------------------------------
///
/// Creates a memory allocator.
///
/// @return NULL if memory error, else the memory allocator
//
MemoryAllocator* createAllocator(void)
{
  AllocatedObject* allocated_objects = (AllocatedObject*) malloc(sizeof(AllocatedObject) * INITIAL_SIZE);
  MemoryAllocator* allocator = (MemoryAllocator*) malloc(sizeof(MemoryAllocator));

  if (allocated_objects == NULL || allocator == NULL)
  {
    free(allocated_objects);
    free(allocator);
    return NULL;
  }

  allocator->alloced_objects_ = allocated_objects;
  allocator->size_ = INITIAL_SIZE;
  allocator->num_allocated_ = 0;

  return allocator;
}

//------------------------------------------------------------------------------
///
/// Adds an allocated object to the memory allocator.
///
/// @param allocator the memory allocator
/// @param object the object to add
///
/// @return NULL if memory error, else the memory allocator
//
MemoryAllocator* addAllocatedObject(MemoryAllocator* allocator, void* object)
{
  if (isObjectTracked(allocator, object))
  {
    return allocator;
  }

  if (allocator->num_allocated_ == allocator->size_)
  {
    AllocatedObject* new_alloced_objects = (AllocatedObject*) 
      realloc(allocator->alloced_objects_, sizeof(AllocatedObject) * (allocator->size_ + CHUNK_SIZE));

    if (new_alloced_objects == NULL)
    {
      freeAllocatorInside(allocator);
      return NULL;
    }

    allocator->alloced_objects_ = new_alloced_objects;
    allocator->size_ += CHUNK_SIZE;
  }

  AllocatedObject* current = &allocator->alloced_objects_[allocator->num_allocated_];
  current->object_ = object;
  current->freeFunction_ = NULL; //free_function;

  allocator->num_allocated_++;

  return allocator;
}

//------------------------------------------------------------------------------
///
/// Checks if an object is tracked by the memory allocator.
///
/// @param allocator the memory allocator
/// @param object the object to check
///
/// @return true if the object is tracked, else false
//
bool isObjectTracked(MemoryAllocator* allocator, void* object)
{
  for (int i = 0; i < allocator->num_allocated_; i++)
  {
    if (allocator->alloced_objects_[i].object_ == object)
    {
      return true;
    }
  }

  return false;
}

//------------------------------------------------------------------------------
///
/// Frees all allocated objects from heap and sets the memory allocator to NULL.
///
/// @param allocator pointer to the memory allocator
//
void freeAll(MemoryAllocator** allocator)
{
  freeAllocatorInside(*allocator);
  free(*allocator);
  *allocator = NULL;
}

//------------------------------------------------------------------------------
///
/// Frees all allocated objects from heap.
///
/// @param allocator the memory allocator
//
void freeAllocatorInside(MemoryAllocator* allocator)
{
  for (int i = 0; i < allocator->size_; i++)
  {
    AllocatedObject object = allocator->alloced_objects_[i];

    // conditional jump fehler
    if (object.object_ == NULL)
    {
      continue;
    }

    void (*free_fn)(void**) = object.freeFunction_;
    if (free_fn == NULL)
    {
      free_fn = myFree;
    }

    free_fn(&object.object_);
    object.object_ = NULL;
  }

  free(allocator->alloced_objects_);
  allocator->alloced_objects_ = NULL;

  allocator->size_ = 0;
}

//------------------------------------------------------------------------------
///
/// Prints all allocated objects.
///
/// @param allocator the memory allocator
//
void printAllocatedObjects(MemoryAllocator* allocator)
{
  printf("Allocated objects (%d):\n", allocator->num_allocated_);

  for (int i = 0; i < allocator->num_allocated_; i++)
  {
    printf("\t- %d: %p\n", i, allocator->alloced_objects_[i].object_);
  }
}

//------------------------------------------------------------------------------
///
/// Allocates memory for an object and adds it to the memory allocator.
///
/// @param size the size of the object
/// @param allocator the memory allocator
///
/// @return NULL if memory error, else the object
//
void* myMalloc(size_t size, MemoryAllocator* allocator)//, void (*free_function)(void**)) 
{
  void* object = malloc(size);
  if (object == NULL)
  {
    return NULL;
  }

  if (addAllocatedObject(allocator, object) == NULL)
  {
    free(object);
    return NULL;
  }

  return object;
}

//------------------------------------------------------------------------------
///
/// Frees an object from heap and sets it to NULL.
///
/// @param object the object which to free.
//
void myFree(void** object)
{
  if (object == NULL || *object == NULL)
  {
    return;
  }

  free(*object);
  *object = NULL;
}

#endif // MEMORY_ALLOCATOR_H
