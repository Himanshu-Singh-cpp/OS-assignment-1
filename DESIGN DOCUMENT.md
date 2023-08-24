**DESIGN DOCUMENT**

In this assignment, we have created an ELF loader from scratch using C. 

We primarily have three functions in our loader.c file:

1. load_and_run_elf
2. check_elf
3. loader_cleanup



1) load_and_run_elf:

We first found out the size of the elf executable using lseek. We then allocated a buffer memory of this size into which
we subsequently read the entire binary content. We then iterated through the program header table (starting at its offset) and
found the program header of type PT_LOAD containing the entry point address. We then allocated a memory of size p_memsz
using the mmap function. To the start of this virtual address, we added the difference between e_entry and p_vaddr, giving us the 
proper entry point address. We then typecast this final entry point address to the function pointer matching _start, i.e. which returns
int and takes no arguments. Finally, we call the _start method and print the returned value. We also used munmap to free the memory that
we allocated using mmap.

2) check_elf:

The checks we performed are:

a) To check that the file descriptor is not negative.

b) If the first four characters of the elf header magic match those given in the manual pages.

c) To check if the byte order in the header is Little Endian. Here, we have assumed that the system the code is being run on is of 
Little Endian type.

d) To check that the class given in the header is not invalid.

e) To check that the version of the elf specification is not invalid.

f) To check that the file version is not invalid.


3) loader_cleanup:

We just freed ehdr (The pointer to the elf header) and closed the file descriptor.



For our Makefiles, we have used the following flags:

1. -w : to suppress warnings
2. -m32: to create suitable code for a 32-bit system
3. -I : to look for header files in other directories
4. -o : to set the name of the output file
5. -L : to search the list of directories for libraries.
6. -w1, -rpath : to search for shared library during runtime
7. -fpic : to generate position-independent code.

Contributions

Vijval Ekbote:
  1. Loader.c
  2. Error checking ELF files


Himanshu Singh:
  1. Loader.c
  2. Makefile


We both have equal contributions to the project.

     
Link to the GitHub repository: https://github.com/Singh-Himanshu-cpp/OS-assignment-1 
