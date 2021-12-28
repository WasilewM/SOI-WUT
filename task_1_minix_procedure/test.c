#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <minix/callnr.h>
#include <errno.h>

int getprocnr(int nr)
{
    message m;
    m.m1_i1 = nr;
    _syscall(MM, GETPROCNR, &m);
    return m.m_type;
}

int main(int argc, char** argv)
{
    int find_proc_id;
    int proc_id;
    int found_index;
    if(argc != 2)
    {
    	printf("Invalid number of arguments");
    	printf("Please enter \"./a.out number\" where number is process id you want to be found.");
    	
    	return 0;
    }
    
    find_proc_id = atoi(argv[1]);
    proc_id = find_proc_id - 10;
    
    for (; proc_id <= find_proc_id; proc_id++)
    {
    	found_index = getprocnr(proc_id);
    	if (found_index >= -1)
    	{
    	    printf("process %d at index number %d\n", proc_id, found_index);
    	}
    	else
    	{
    	    printf("process %d not found - error code %d\n", proc_id, errno);
    	}
    }

    return 0;
}
