//References: https://www.youtube.com/watch?v=sZ8GJ1TiMdk&t=3965s

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "memory_management.h"

uint alloc_count = 0; // number of times malloc is called
block allocBlocks[100];
uint memorySize = 0;
uint sbrkCount = 0;

void *_malloc(int size){
    if (size <=0){
        return 0;
    }
    block head;

    if (alloc_count == 0){
        void *start = sbrk(0) + sizeof(block); // Get the start of the heap
        int tempSize = size;
        sbrk(4096); // allocate a page of memory
        //printf("INITIAL PAGE ALLOCATED\n");
        tempSize -=4096;
        while (tempSize > 0){
            sbrk(4096);
            sbrkCount++;
            //printf("Sbrk called\n");
            tempSize -=4096;
        }
        sbrkCount++;
        head.start = start;
        //printf("Start = %d\n",head.start);
        head.size = size;
        //printf("Size = %d\n",head.size);
        allocBlocks[0] = head;
        memorySize =  memorySize + size + sizeof(block);
        alloc_count+=1; 
        //printf("memory size = %d\n",memorySize);
        //printf("*********************\n");

        return start;
    }else{
        // check whether it will be greater than 4096 when you allocate
        if (size > 4096 || memorySize > 4096*sbrkCount){ // check whether the size is too big
        // for one page
            //printf("NEW PAGE CREATED FOR BLOCK: %d\n",alloc_count);
            void* start = (sbrk(0) - 4096*sbrkCount) + memorySize + sizeof(block);
            sbrk(4096);
            sbrkCount++;
            memorySize = memorySize +sizeof(block) + size;
            head.size=size;
            //printf("Head size for block %d :%d\n",alloc_count,head.size);
            head.start=start;
            //printf("Head start for block %d :%d\n",alloc_count,head.start);
            allocBlocks[alloc_count] = head;
            alloc_count+=1;
            //printf("memory size = %d\n",memorySize);
            //printf("*********************\n");
            return start;

        }else{
            void* start = (sbrk(0) - 4096*sbrkCount) + memorySize + sizeof(block); 
            //printf("start for block %d %d\n",alloc_count,start);
            memorySize = memorySize +sizeof(block) + size;
            head.size=size;
            //printf("Head size for block %d :%d\n",alloc_count,head.size);
            head.start=start;
            //printf("Head start for block %d :%d\n",alloc_count,head.start);
            allocBlocks[alloc_count] = head;
            alloc_count+=1;
            //printf("memory size = %d\n",memorySize);
            //printf("*********************\n");
            return start;

        }
        
        
    }
}

void _free(void *ptr){
    if (alloc_count > 0 && allocBlocks[alloc_count-1].start==ptr){
        //printf("sbrkcount = %d\n",sbrkCount);
        memorySize = memorySize - sizeof(block) - allocBlocks[alloc_count-1].size;
        alloc_count--;
        if ((unsigned long)(sbrk(0) - 4096*sbrkCount) > 4096){
            sbrk(-4096);
            sbrkCount--;
            //printf("sbrkcount = %d\n",sbrkCount);
        }
    }
}

/*
int main(int argc, char *argv[])
{  
    printf("sbrk(0) = %d\n",sbrk(0));
    printf("Size of header = %d\n",sizeof(block));
    printf("malloc = %d\n",_malloc(5000));
    printf("malloc = %d\n",_malloc(2000));

    int *p1 = _malloc(20);
    printf("malloc = %d\n",p1);
    _free(p1);
    
    int *p2 = _malloc(5000);
    printf("malloc = %d\n",p2);
    printf("sbrk(0) = %d\n",sbrk(0));
    _free(p2);

    int *p3 = _malloc(50);
    printf("malloc = %d\n",p3);
    printf("sbrk(0) = %d\n",sbrk(0));


   
    exit(0); // exits the program
}
*/