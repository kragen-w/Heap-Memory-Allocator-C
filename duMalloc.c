#include <stdio.h>
#include <stdlib.h>
#include "dumalloc.h"
#define HEAP_SIZE (128*8)
unsigned char heap[HEAP_SIZE];



typedef struct memoryBlockHeader {
     int size; // size of the reserved block
     struct memoryBlockHeader* next;  // the next block in the integrated free list
} memoryBlockHeader;

memoryBlockHeader* freeListHead;




void duInitMalloc(){
    
    for (int i = 0; i < HEAP_SIZE; i++){
        heap[i] = 0;
    }
    memoryBlockHeader* currentBlock = (memoryBlockHeader*)heap;
    currentBlock->size = HEAP_SIZE - sizeof(memoryBlockHeader);
    currentBlock->next = NULL;
    freeListHead = currentBlock;
    
   
    
    
}

void duMemoryDump(){
    printf("MEMORY DUMP\n");
    printf("Free list:\n");
    
    memoryBlockHeader* currentFreeBlock = freeListHead;
    while (1){
        printf("Free block at %p, size, %d.\n", currentFreeBlock, currentFreeBlock->size);
        if (currentFreeBlock->next == NULL){
            break;
        }
        currentFreeBlock = currentFreeBlock->next;
    }
}


void* duMalloc(int size){
    int nearestEight = (((size-1) / 8) + 1) * 8; //finds the byte value for just the data
    memoryBlockHeader* currentFreeBlock = freeListHead;
    
    
    unsigned char endReached = 0;
    unsigned char foundBlock = 0;

    if (currentFreeBlock->size >= nearestEight){
        foundBlock = 1; 
    }
    

    if (currentFreeBlock->next == NULL){
        endReached = 1;
    }
    
    //CASE OF FIRST ELEMENT
    if (foundBlock){ //if the one node works
        memoryBlockHeader* newFreeBlock = (memoryBlockHeader*)((unsigned char*)(currentFreeBlock) + nearestEight + sizeof(memoryBlockHeader));


        newFreeBlock->size = (currentFreeBlock->size - nearestEight - sizeof(memoryBlockHeader));
        currentFreeBlock->size = nearestEight;

        newFreeBlock->next = currentFreeBlock->next;
        freeListHead = newFreeBlock;
        currentFreeBlock->next = NULL;
        return (void*)(currentFreeBlock + 1);
    }
    
    memoryBlockHeader* previousFreeBlock = currentFreeBlock;
    currentFreeBlock = currentFreeBlock->next;
    while (!endReached && !foundBlock){
        
        if (currentFreeBlock->next == NULL){
            endReached = 1;
            break;
        }
        if (currentFreeBlock->size >= nearestEight){
            foundBlock = 1;
            break;
        }
        currentFreeBlock = currentFreeBlock->next;
        previousFreeBlock = previousFreeBlock->next;
    }

    // CASE IF THERE IS NO ROOM
    if (endReached && !foundBlock){
        return NULL;
    }
    else{
        memoryBlockHeader* newFreeBlock = (memoryBlockHeader*)((unsigned char*)(currentFreeBlock) + nearestEight + sizeof(memoryBlockHeader));
        newFreeBlock->size = currentFreeBlock->size - nearestEight - sizeof(memoryBlockHeader);

        currentFreeBlock->size = nearestEight;

        newFreeBlock->next = currentFreeBlock->next;
        previousFreeBlock->next=newFreeBlock;
        currentFreeBlock->next = NULL;
        
        return currentFreeBlock + 1;
    }
    
}



void duFree(void* ptr){
    memoryBlockHeader* addressToFree = (memoryBlockHeader*)((unsigned char *)ptr - sizeof(memoryBlockHeader));
    memoryBlockHeader* currentFreeBlock = freeListHead;
   

    if (currentFreeBlock > addressToFree){//freed block is head
       
        memoryBlockHeader** pointerToFreeHead = &freeListHead;
        addressToFree->next = *pointerToFreeHead;
        *pointerToFreeHead = addressToFree;


    }else{
       
        while (currentFreeBlock < addressToFree){
            currentFreeBlock = currentFreeBlock->next;
        }
       
       

        memoryBlockHeader** pointerToCurrentBlock = &freeListHead;
        addressToFree->next = (*pointerToCurrentBlock)->next;//putting it back
        (*pointerToCurrentBlock)->next = addressToFree;
    }

  // FIRST BLOCK IS FREED
  
    

}
