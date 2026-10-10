#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertStrToByteCode(char *str, unsigned char inst[], int size);

int main(int argc, char **argv) {
  FILE *pFile = NULL;

  char buffer[22];

  if (argc < 2) {
    pFile = fopen("./test2.txt", "r");
  } else {
    pFile = fopen(argv[1], "r");
  }

  if (pFile == NULL) {
    printf("Error open test file, please make sure they exist.\n");

    return 0;
  }

  while (fgets(buffer, 22, pFile) != NULL) { //&& strlen(buffer) > 1) {
    // This unsigned char array stores an instruction read from the file
    // As the largest y86 instruction is 10 bytes, there are 10 unsigned char in
    // the array where each represents a byte.
    unsigned char instruction[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    convertStrToByteCode(buffer, instruction, 10);

    // TODO: From here, your task is to complete the implementation so that all
    // y86 opcodes can be disassembled. Any undisassembled opcode should display
  switch (instruction[0])
  {
  case 0x00: 
    printf("halt\n");
    break;
  
  
  case 0x40: 
    printf("rmmovq\n");
    break;
  
  
  case 0x50: 
    printf("mrmovq\n");
    break;
  
  
  case 0x70: 
    printf("jmp\n");
    break;
  
  
  case 0x71: 
    printf("jle\n");
    break;
  
  
  case 0x72: 
    printf("jl\n");
    break;
  
  
  case 0x73: 
    printf("je\n");
    break;
  
  
  case 0x74: 
    printf("jne\n");
    break;
  
  
  case 0x75: 
    printf("jge\n");
    break;
  
  
  case 0x76: 
    printf("jg\n");
    break;

  
  case 0x80: 
    printf("call\n");
    break;
  }
  }

  fclose(pFile);

  return 0;
}

/****************************************************************************
N.B. You do not need to modify or work in this function.
Description:
This function converts a line of machine code read from the text file
into machine byte code.
The machine code is stored in an unsigned char array.
******************************************************************************/
int convertStrToByteCode(char *str, unsigned char inst[], int size) {
  int numHexDigits = 0;
  char *endstr;
  // Each instruction should consist of at most 20 hex digits
  numHexDigits = strlen(str);

  int byteCount = 0; // numHexDigits >> 1;

  endstr = str;

  while (*endstr != '\n' && *endstr != '\0') {
    char byteValue[3];
    byteValue[0] = *endstr;
    byteValue[1] = *(endstr + 1);
    byteValue[2] = '\0';

    long long value = strtol(byteValue, NULL, 16);
    inst[byteCount++] = value;
    endstr += 2;
  }

  // Return the size of the instruction in bytes
  return numHexDigits >> 1;
}