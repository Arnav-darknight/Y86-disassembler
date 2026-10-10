#include <stdio.h>
#include <stdlib.h>

const char *register_names[] =
    {
        "%rax",
        "%rcx",
        "%rdx",
        "%rbx",
        "%rsp",
        "%rbp",
        "%rsi",
        "%rdi",
        "%r8",
        "%r9",
        "%r10",
        "%r11",
        "%r12",
        "%r13",
        "%r14",
        "UNKNOWN_REGSITER"};


//This is the help function that reads y86 binary code from a file
unsigned int loadBinFromFile(const char *filename, unsigned char memory[], unsigned int memsize);

int main(int argc, char **argv)
{
  unsigned int MAX_MEMSIZE = 4096;
  unsigned char memory[MAX_MEMSIZE]; //This array represents the 4KB memory space
  unsigned int PC = 0;               //This is the initial program counter address

  if (argc < 2)
  {
    printf("Usage: please specify a y86 binary program file in the argument.\n");
    return -1;
  }

  unsigned int program_size = loadBinFromFile(argv[1], memory, MAX_MEMSIZE);

  if (program_size == 0)
    return 0;

  //TODO: Implement your disassembler from here
  //At the moment, it simply display each byte from the memory.
  while (PC < program_size)
  {
    switch (memory[PC])
    {
    case 0x30:
    {
      printf("irmovq ");

      int operandB = memory[PC+1] % 0x10;

      long long value = memory[PC+2]+(memory[PC+3]<<8)+(memory[PC+4]<<16)+(memory[PC+5]<<24);

      printf("$%lld,", value);
      printf(" %s\n", register_names[operandB]);
      PC+=10;
      break;
    }
      
      
    
    case 0x40:
    {
      printf("rmmovq ");
      int operandA = memory[PC+1] % 0x10;
      int operandB = memory[PC+1] / 0x10;
      long long value = memory[PC+2]+(memory[PC+3]<<8)+(memory[PC+4]<<16)+(memory[PC+5]<<24);
      printf("%s, %lld(%s)\n", register_names[operandB], value, register_names[operandA]);
      PC+=10;
      break;
    }
    case 0x50:
    {
      printf("mrmovq  ");
      int operandA = memory[PC+1] % 0x10;
      int operandB = memory[PC+1] / 0x10;
      int value = memory[PC+2];
      printf("%d(%s), %s\n", value, register_names[operandA], register_names[operandB]);
      PC+=10;
      break;
    }
    case 0x60:
    {
      printf("addq ");
      int operandA = memory[PC+1] % 0x10;
      int operandB = memory[PC+1] / 0x10;
      printf("%s, %s\n", register_names[operandA], register_names[operandB]);
      PC+=2;
      break; 
    }
    
    case 0x00:
    {
      printf("halt\n");
      PC++;
      break;
    }
}
    // else
    // {
    //   printf("%02X\n", memory[PC]);

    //   PC++; 
    // }
    
    
  }

  return 0;
}

/**************************
N.B. You do not need to modify or work in this function.
Description:
This function reads in a y86 machine bytecode from file and
store them in an unsigned char array.
**************************/
unsigned int loadBinFromFile(const char *filename, unsigned char memory[], unsigned int memsize)
{
  unsigned int bytes_read = 0;

  unsigned int file_size = 0;

  FILE *pfile = fopen(filename, "rb");

  if (!pfile)
  {
    printf("Unable to load file %s, please check if the path and name are correct.\n", filename);
    return 0;
  }

  fseek(pfile, 0, SEEK_END);
  file_size = ftell(pfile);
  rewind(pfile);

  if (file_size > memsize)
  {
    printf("Program size exceeds memory size of %d.\n", memsize);
    return 0;
  }

  bytes_read = fread(memory, 1, file_size, pfile);

  if (bytes_read != file_size)
  {
    printf("Bytes read does not match the file size.\n");
    return 0;
  }

  fclose(pfile);

  return bytes_read;
}