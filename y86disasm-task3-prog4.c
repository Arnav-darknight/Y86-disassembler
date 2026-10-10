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
  int data_mode = 0;

  if (argc < 2)
  {
    printf("Usage: please specify a y86 binary program file in the argument.\n");
    return -1;
  }

  unsigned int program_size = loadBinFromFile(argv[1], memory, MAX_MEMSIZE);

  if (program_size == 0)
    return 0;


  while (PC < program_size)
  {
    if (memory[PC]==0x00 && memory[PC+1]==0x0B)
    {
      long long value = ((long long)memory[PC]) + ((long long)memory[PC+1] << 8) + ((long long)memory[PC+2] << 16) + ((long long)memory[PC+3] << 24) +((long long)memory[PC+4] << 32) + ((long long)memory[PC+5] << 40) + ((long long)memory[PC+6] << 48) + ((long long)memory[PC+7] << 56);

      printf(".quad 0x%016llX\n", value);
      PC += 8;
    }
    else if (memory[PC]==0x00)
    {
      printf("halt\n");
      PC++;
    }
    else if (memory[PC]==0x30){
      printf("irmovq ");
      long long operandA = memory[PC+1] % 0x10;
      long long value = memory[PC+2]+(memory[PC+3]<<8)+(memory[PC+4]<<16)+(memory[PC+5]<<24);
      printf("$%lld, ", value);
      printf("%s\n", register_names[operandA]);
      PC+=10;
    }
    else if (memory[PC]==0x80){
      printf("call\n");
      PC+=9;
      
    }

    else if (memory[PC]==0x00 && memory[PC+1]==0x60)
    {
      long long value = ((long long)memory[PC]) + ((long long)memory[PC+1] << 8) + ((long long)memory[PC+2] << 16) + ((long long)memory[PC+3] << 24) + ((long long)memory[PC+4] << 32) + ((long long)memory[PC+5] << 40) + ((long long)memory[PC+6] << 48) + ((long long)memory[PC+7] << 56);

      printf(".quad 0x%016llx\n", value);
      PC += 8;
    }
    else if (memory[PC]==0x90)
    {
      printf("ret\n");
      PC++;
    }
    else if (memory[PC]==0x63)
    {
      printf("xorq ");
      long long operandA = memory[PC+1] % 0x10;
      long long operandB = memory[PC+1] / 0x10;
      printf("%s, %s\n", register_names[operandA], register_names[operandB]);

      PC+=2;
    }
    else if (memory[PC]==0x62)
    {
      printf("andq ");
      long long operandA = memory[PC+1] % 0x10;
      long long operandB = memory[PC+1] / 0x10;
      printf("%s, %s\n", register_names[operandA], register_names[operandB]);

      PC+=2;
    }
    else if (memory[PC]==0x70)
    {
      printf("jmp\n");
      PC+=9;
    }
    else if (memory[PC]==0x50)
    {
      printf("mrmovq ");
      long long operandA = memory[PC+1] % 0x10;
      long long operandB = memory[PC+1] / 0x10;
      printf("(%s), %s\n", register_names[operandA], register_names[operandB]);

      PC+=10;
    }
    else if (memory[PC]==0x61)
    {
      printf("subq ");
      long long operandA = memory[PC+1] % 0x10;
      long long operandB = memory[PC+1] / 0x10;
      printf("%s, %s\n", register_names[operandB], register_names[operandA]);
      PC+=2;
    }
    else if (memory[PC]==0x26)
    {
      printf("cmovg ");
      long long operandA = memory[PC+1] % 0x10;
      long long operandB = memory[PC+1] / 0x10;
      printf("%s, %s\n", register_names[operandB], register_names[operandA]);
      PC+=2;
    }
    else if (memory[PC]==0x60)
    {
      printf("addq ");
      long long operandA = memory[PC+1] % 0x10;
      long long operandB = memory[PC+1] / 0x10;
      printf("%s, %s\n", register_names[operandB], register_names[operandA]);
      PC+=2;
    }
    else if (memory[PC]==0x74)
    {
      printf("jne\n");
      PC+=9;
    }
    else
    {
      // if (data_mode && PC + 7 < program_size)
      // {
        long long value = ((long long)memory[PC]) + ((long long)memory[PC+1] << 8) + ((long long)memory[PC+2] << 16) + ((long long)memory[PC+3] << 24) + ((long long)memory[PC+4] << 32) + ((long long)memory[PC+5] << 40) + ((long long)memory[PC+6] << 48) + ((long long)memory[PC+7] << 56);

        printf(".quad 0x%016llx\n", value);
        PC += 8;
      // }
      
    }

  }

  return 0;
}

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
