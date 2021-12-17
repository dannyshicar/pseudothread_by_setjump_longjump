#include "threadutils.h"

jmp_buf MAIN;
jmp_buf SCHEDULER;

TCB_ptr Head;
TCB_ptr Current;
TCB_ptr Work;

struct sigaction act;
sigset_t base_mask, waiting_mask;
sigset_t tstp_mask, alrm_mask;

int mainstate;
int timeslice;
int switchmode;
void BinarySearch(int thread_id, int init,int maxiter);
void BlackholeNumber(int thread_id, int init, int maxiter);
void FibonacciSequence(int thread_id, int init,int maxiter);

int main(int argc, char *argv[])
{
    int bi_init = atoi(argv[1]);    //The initial value pass into BinarySearch
    int bi_maxiter = atoi(argv[2]); //The max iteration for BinarySearch to process
    int bl_init = atoi(argv[3]);    //The initial value pass into BlackholeNumber
    int bl_maxiter = atoi(argv[4]); //The max iteration for BlackholeNumber to process
    int fi_init = atoi(argv[5]);    //The initial value pass into FibonacciSequence
    int fi_maxiter = atoi(argv[6]); //The max iteration for FibonacciSequence to process
    timeslice = atoi(argv[7]);      //time limit for a function to process until next "context switch"
    switchmode = atoi(argv[8]);     //0 for "context switch" after each iteration; 1 for "context switch" due to signal caught and timeslice reached

    sigemptyset(&base_mask);
    sigaddset(&base_mask, SIGTSTP);
    sigaddset(&base_mask, SIGALRM);
    sigemptyset(&tstp_mask);
    sigemptyset(&alrm_mask);
    sigaddset(&tstp_mask, SIGTSTP);
    sigaddset(&alrm_mask, SIGALRM);

    act.sa_handler = sighandler;
    sigaction(SIGTSTP, &act, NULL);
    sigaction(SIGALRM, &act, NULL);
    sigprocmask(SIG_SETMASK, &base_mask, NULL);

    Head = Current = NULL;

    ThreadCreate(BinarySearch,1,bi_init,bi_maxiter);
    ThreadCreate(BlackholeNumber,2,bl_init,bl_maxiter);
    ThreadCreate(FibonacciSequence,3,fi_init,fi_maxiter);
    // printf("%d\n", Head -> x);
    // printf("%d")
    alarm(timeslice);
    mainstate = setjmp(MAIN);
    if (mainstate == 0)
        scheduler();
    else
        return 0;
}