#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <minix/callnr.h>
#include <errno.h>

int main(int argc, char** argv)
{
    int i;
    message m;
    m.m1_i1 = 0;
    _syscall(MM, CHANGEGROUP, &m);
    
    m.m1_i1 = 30;
    _syscall(MM, CHANGEPROC, &m);
    m.m1_i1 = 51;
    _syscall(MM, CHANGEPROC, &m);
    m.m1_i1 = 50;
    _syscall(MM, CHANGEPROC, &m);
    
    for (i = 10; i < 20; i++) {
        m.m1_i1 = i;
        _syscall(MM, CHANGEGROUP, &m);
    }
    return 0;
}
