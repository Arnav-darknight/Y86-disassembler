#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertStrToByteCode(char *str, unsigned char inst[], int size);

int main(int argc, char **argv) {
  FILE *pFile = NULL;

  char buffer[22];

  if (argc < 2) {
    pFile = fopen("./test1.txt", "r");
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
      case 0x10: 
    printf("nop\n");
    break;
      case 0x20: 
    printf("rrmovq\n");
    break;
      case 0x21: 
    printf("cmovle\n");
    break;
      case 0x22: 
    printf("cmovl\n");
    break;
      case 0x23: 
    printf("cmove\n");
    break;
      case 0x24: 
    printf("cmovne\n");
    break;
      case 0x25: 
    printf("cmovge\n");
    break;
      case 0x26: 
    printf("cmovg\n");
    break;
      case 0x60: 
    printf("addq\n");
    break;
      case 0x61: 
    printf("subq\n");
    break;
      case 0x62: 
    printf("andq\n");
    break;
      case 0x63: 
    printf("xorq\n");
    break;
      case 0x90: 
    printf("ret\n");
    break;
      case 0x0A: 
    printf("pushq\n");
    break;
      case 0x0B: 
    printf("popq\n");
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