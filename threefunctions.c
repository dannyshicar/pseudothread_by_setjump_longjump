#include "threadutils.h"

void BinarySearch(int thread_id, int init, int maxiter)
{
    
    ThreadInit(thread_id, init, maxiter);
    /*
    Some initilization if needed.
    */
    // setjmp(Current -> Environment);

    Current -> z = Current -> x;
    // printf("ans = %d\n", Current -> z);
    Current-> x = 0, Current -> y = 100;
    for (Current->i = 0; Current->i < Current->N; ++Current->i)
    {
        sleep(1);
        /*
        Do the computation, then output result.
        Call ThreadExit() if the work is done.
        */  
        printf("BinarySearch: %d\n", (Current -> x + Current -> y)/ 2); 
        // printf("%d\n%d\n", Current -> x, Current -> y);
        if((Current -> x + Current -> y)/ 2 == Current -> z){ 
            break;
        }
        if((Current -> x + Current -> y)/2 > Current -> z){
            Current -> y = (Current -> x + Current -> y) / 2 - 1;
        }    
        else{
            Current -> x = (Current -> x + Current -> y) / 2  + 1;
        }
        ThreadYield() 
        
    }

    ThreadExit()
}

void BlackholeNumber(int thread_id, int init, int maxiter)
{
    ThreadInit(thread_id, init, maxiter);
    /*
    Some initilization if needed.
    */
    int arr[3], tmp;
    for (Current->i = 0; Current->i < Current->N; ++Current->i)
    {
        sleep(1);
        arr[0] = Current -> x % 10;
        arr[1] = Current -> x / 100;
        arr[2] = (Current -> x /10) % 10;
        for(int i = 0; i < 3; i++){
            for(int j = i + 1; j < 3; j++){
                if(arr[i] > arr[j]){
                    tmp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = tmp;
                }
            }
        }
        Current -> y = arr[0] * 100 + arr[1] * 10 + arr[2];
        Current -> z = arr[2] * 100 + arr[1] * 10 + arr[0];
        Current -> x = Current -> z - Current -> y;
        printf("BlackholeNumber: %d\n", Current -> x);

        /*
        Do the computation, then output result.
        Call ThreadExit() if the work is done.
        */   
        if(Current -> x == 495) break;  
        ThreadYield()
    }
    ThreadExit()
}

void FibonacciSequence(int thread_id, int init, int maxiter)
{
    ThreadInit(thread_id, init, maxiter);
    /*
    Some initilization if needed.
    */
    Current -> x = 0, Current -> y = 1; 
    for (Current->i = 0; Current->i < Current->N; ++Current->i)
    {
        sleep(1);
        /*
        Do the computation, then output result.
        */    
        Current -> z = Current -> x + Current -> y;
        printf("FibonacciSequence: %d\n", Current -> z);
        Current -> x = Current -> y, Current -> y = Current -> z;
        // if(Current -> i == Current -> N - 1) break;
        ThreadYield()
    }
    ThreadExit()
}
