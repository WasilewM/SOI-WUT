# SOI-LAB3

/*
Compile program with the command presented below:
g++ -o prog main.cpp -Wall -fsanitize=thread,undefined -fsanitize=thread,undefined -lpthread -lm
Launch program with command:
./prog
*/

sample_results_1.txt file containse sample results of the program output when BUFFER_SIZE = 1
sample_results_10.txt file containse sample results of the program output when BUFFER_SIZE = 10

It is normal that same prints may happen after the semaphores has been closed, due to the fact that
after leaving the critical section that context of the CPU may be changed.

Schema for 1 producer and 1 consument solution:

#define N 10
semaphore mutex = 1;
semaphore empty = N;
semaphore full = 0;
int count = 0;

void producer(void) {
&nbsp;&nbsp;while (TRUE) {
&nbsp;&nbsp;&nbsp;&nbsp;procude_item();
&nbsp;&nbsp;&nbsp;&nbsp;down(empty);
&nbsp;&nbsp;&nbsp;&nbsp;down(mutex);
&nbsp;&nbsp;&nbsp;&nbsp;enter_item();
&nbsp;&nbsp;&nbsp;&nbsp;up(mutex);
&nbsp;&nbsp;&nbsp;&nbsp;up(full);
&nbsp;&nbsp;}
}

void consumer(void) {
&nbsp;&nbsp;while (TRUE) {
&nbsp;&nbsp;&nbsp;&nbsp;down(full);
&nbsp;&nbsp;&nbsp;&nbsp;down(mutex);
&nbsp;&nbsp;&nbsp;&nbsp;remove_item();
&nbsp;&nbsp;&nbsp;&nbsp;up(mutex);
&nbsp;&nbsp;&nbsp;&nbsp;up(empty);
&nbsp;&nbsp;&nbsp;&nbsp;consume_item();
&nbsp;&nbsp;}
}
