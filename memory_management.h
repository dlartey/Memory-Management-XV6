//References: https://www.youtube.com/watch?v=sZ8GJ1TiMdk&t=3965s
typedef struct block{
    struct block *start;
    int size;
} block;

#define BLOCK 4096

void *_malloc(int size);
void _free(void *ptr);
