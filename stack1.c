#define MaxSize 100
 
int stackA[MaxSize],stackB[MaxSize],stackC[MaxSize];
 
int sizeA=0,sizeB=0,sizeC=0;
 
void Push(int *stack,int item, int *size)
{
    if((*size)>MaxSize)
    {
        printf("OVERFLOW\n");
    }
    else
    {
        stack[*size] = item;
        (*size)++;
    }
}
 
int Pop(int *stack, int *size)
{
    if( (*size) <= 0 )
    {
        return -1;
    }
    else
    {
        int x = stack[(*size)-1];
        (*size)--;
        return x;
    }
}
 
void copy_A_to_C()
{
    int x;
    while ( sizeA > 0 )  
    {
        x = Pop( stackA, &sizeA);
        Push( stackB, x, &sizeB);
    }
    while ( sizeB > 0 )
    {
        x = Pop( stackB, &sizeB);
        Push( stackC, x, &sizeC);
    }
}
 
int main()
{
    int size, iterI, item;
    scanf("%d",&size);
 
    for(iterI = 0; iterI<size; iterI++)
    {
        scanf("%d",&item);
        Push( stackA, item, &sizeA);
    }
    copy_A_to_C();
    return 0;
}