#include "loader.h"

// Header of ELF file
Elf32_Ehdr *ehdr;
// Program Header
Elf32_Phdr *phdr;
// File discriptor
int fd; 

/*
 * release memory and other cleanups
 */ 
void loader_cleanup()
{
  free(ehdr);
  close(fd);
}

/*
 * Load and run the ELF executable file
 */
void load_and_run_elf(char **argv)
{
  check_elf(argv);
  fd = open(argv, O_RDONLY);
  if (fd==-1) printf("File not found\n");
  
  // 1. Load entire binary content into the memory from the ELF file.
  int total_size=lseek(fd,0,SEEK_END);
  lseek(fd,0,SEEK_SET);
  void* buffer=malloc(total_size);
  read(fd, buffer, total_size);
  ehdr = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr));
  ehdr=(Elf32_Ehdr*)buffer;

  // 2. Iterate through the PHDR table and find the section of PT_LOAD
  //    type that contains the address of the entrypoint method in fib.c
  int number_of_program = ehdr->e_phnum;
  int program_header_size = ehdr->e_phentsize;
  for (int i = 0; i < number_of_program; i++)
  {
    phdr = (Elf32_Phdr *)(buffer + ehdr->e_phoff + i * program_header_size);
    if ((phdr->p_type == PT_LOAD)&&((phdr->p_vaddr <= ehdr->e_entry) && (ehdr->e_entry < phdr->p_vaddr + phdr->p_memsz))) break;
  }

  // 3. Allocate memory of the size "p_memsz" using mmap function
  //    and then copy the segment content
  void *virtual_mem = mmap(NULL, (*phdr).p_memsz, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
  memcpy(virtual_mem, buffer + phdr->p_offset, phdr->p_memsz);

  // 4. Navigate to the entrypoint address into the segment loaded in the memory in above step
  Elf32_Addr entry_pt_addr=(Elf32_Addr)virtual_mem+ehdr->e_entry-phdr->p_vaddr;

  // 5. Typecast the address to that of function pointer matching "_start" method in fib.c.
  typedef int(*fpp)();
  fpp _start=(fpp)(entry_pt_addr);

  // 6. Call the "_start" method and print the value returned from the "_start"
  int result = _start();
  printf("User _start return value = %d\n", result);
  munmap(virtual_mem,phdr->p_memsz);
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Usage: %s <ELF Executable> \n", argv[0]);
    exit(1);
  }
  // 1. carry out necessary checks on the input ELF file
  // 2. passing it to the loader for carrying out the loading/execution
  load_and_run_elf(argv + 1);
  // 3. invoke the cleanup routine inside the loader
  loader_cleanup();
  return 0;
}
