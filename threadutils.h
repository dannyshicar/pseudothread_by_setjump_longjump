#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

extern int timeslice;
extern int switchmode;

typedef struct TCB_NODE *TCB_ptr;
typedef struct TCB_NODE
{
    jmp_buf  Environment;   // The jmp_buf of each function
    int      Thread_id;     // Not necessary for any tasks, but one may found it useful while debuging
    TCB_ptr  Next;          // TCB_ptr points to next TCB_NODE in the circular linked-list
    TCB_ptr  Prev;          // TCB_ptr points to previous TCB_NODE in the circular linked-list
    int i,N;                // See threefunctions.c for their usage
    int x,y,z;              // Three integers for you to store data you want.

}TCB;

extern jmp_buf MAIN;        // The jmp_buf for main()
extern jmp_buf SCHEDULER;   // The jmp_buf for scheduler()

extern TCB_ptr Head;        // Three TCB_ptr for you to initialize your circular linked-list
extern TCB_ptr Current;     // The Current TCB_ptr will move during "context switch"
extern TCB_ptr Work;



extern sigset_t base_mask, waiting_mask;   // See main for meanings of each sigset_t
extern sigset_t tstp_mask, alrm_mask;


void sighandler(int signo);
void scheduler();

/*
Call function in the argument that is passed in
*/
#define ThreadCreate(function,thread_id,init,maxiter)   \
{ \
    if(setjmp(MAIN) == 0) {    \
        function(thread_id, init, maxiter);    \
    } \
} 


/*
Build up TCB_NODE for each function, insert it into circular linked-list
*/
#define ThreadInit(thread_id,init,maxiter)             \
{                                                      \
    TCB_ptr a = (TCB_ptr)malloc(sizeof(TCB));          \
    a -> x = init; \
    a -> N = maxiter; \
    if(Head == NULL){ \
        Head = a; \
    }\
    else if(Head -> Next == NULL){ \
        Head -> Next = a; \
        a -> Prev = Head; \
    } \
    else{ \
        Head -> Next -> Next = a; \
        a -> Prev = Head -> Next; \
        a -> Next = Head; \
        Head -> Prev = a; \
    } \
    if(setjmp(a -> Environment) == 0) \
        longjmp(MAIN,1);                  \
} 

/*
Call this while a thread is terminated
*/
#define ThreadExit()                                   \
{                                                      \
    longjmp(SCHEDULER, 2); \
} 
/*
Decided whether to "context switch" based on the switchmode argument passed in main.c
*/
#define ThreadYield()                                 \
{                                                     \
    int stat = setjmp(Current -> Environment); \
    if(stat == 0){ \
        if(switchmode == 0){ \
                longjmp(SCHEDULER,1); \
        } \
        else{ \
            sigpending( &waiting_mask); \
            if( sigismember( &waiting_mask, SIGTSTP)){ \
                sigsuspend( &alrm_mask); \
            } \
            else if(sigismember( &waiting_mask, SIGALRM)){ \
                sigsuspend( &tstp_mask); \
            } \
        } \
    } \
} 








