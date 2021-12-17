# pseudothread_by_setjump_longjump

## 0. The Goal
0. simulate the concept of context switch.
1. handle some system calls about signals.
2. use `setjmp()`, `longjmp()`.

## 1. Description
1. simulate a user-thread library by using `longjmp()`, `setjmp()`, etc. 
2. use a function to represent a thread. 
3. "context switch" between functions by non-local jumps between functions, which is arranged by a `scheduler()`:
4. each time a function needs to "context switch" to another, it needs to jump back to `scheduler()`, and `scheduler()` will schedule next function to be executed, thus jump to it.
5. handle signal: if caught a signal, I will print it and context switch


## 2. What three "PseudoThread" do 
0. BlackholeNumber, BinarySearch,or FibonacciSequence.
1. `BlackholeNumber()` : start from `init`(100-999), update the value by the alogrithm mentioned in the URL below and then print. The function stops when the output is 495.  (https://zh.wikipedia.org/wiki/黑洞數) 
2. `BinarySearch()` : conduct binary search between range(0,100) to find `init` of this function. You only have to do one step of binary search in each iteration. The function stops when the output is `init`.  
3. `FibonacciSequence()` : print one entry of the Fibonacci Sequence (1,2,3,5,8,13,...) in each iteration. There's no stopping condition for this function.  

## 3. Usage
executed by the following command:
```
$ ./main {bi_init} {bi_maxiter} {bl_init} {bl_maxiter} {fi_init} {fi_maxiter} {timeslice} {switchmode}
```
Below are argument explainations:
```
bi_init = The initial value pass into BinarySearch
bi_maxiter = The max iteration for BinarySearch to process
bl_init = The initial value pass into BlackholeNumber
bl_maxiter = The max iteration for BlackholeNumber to process
fi_init = The initial value pass into FibonacciSequence
fi_maxiter = The max iteration for FibonacciSequence to process
timeslice = time limit for a function to process until next "context switch"
switchmode = 0 for "context switch" after each iteration; 1 for "context switch" due to signal caught and timeslice reached
```

sample execution 
```
$ ./main 55 10 712 10 1 10 3 1
BinarySearch: 50
^ZBinarySearch: 75
TSTP signal!
BlackholeNumber: 495
FibonacciSequence: 1
ALRM signal!
BinarySearch: 62
BinarySearch: 56
BinarySearch: 53
ALRM signal!
FibonacciSequence: 2
FibonacciSequence: 3
^ZFibonacciSequence: 5
TSTP signal!
BinarySearch: 54
ALRM signal!
FibonacciSequence: 8
FibonacciSequence: 13
FibonacciSequence: 21
ALRM signal!
BinarySearch: 55
FibonacciSequence: 34
FibonacciSequence: 55
ALRM signal!
FibonacciSequence: 89
```
Note: ^Z is where `SIGTSTP` delivered to process, it is not output by process itself.
