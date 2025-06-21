#include "asm_instructions.h"

/**
 * Encoding function template, must return valid 32 bit instruction, argv is accessible to assembler, tho must
 * follow the formula: { opBinBase, argType[3], 1st parsed argument, 2nd parsed ardument, 3rd parsed argument }.
 * These should be made to the most wide use case, so for example MOV, MOVZ, MOVK, etc. should be grupped together
 * and chacked at encoding stage. After passing 7 required argument, there could be more to describe current instruction,
 * tho this should be done by checking opBinBase
 */

uint32_t asmEncodeMOVx(void *argv, int argc) {
  if(argc < 7) 
    return 0;

  ASM_ENCODING_BASE(argv); 

  uint32_t retVal = opBinBase;

  if(opBinBase == 0xB20003E0) {
    retVal |= ASM_REG(args[0]);
    retVal |= ((args[1] & ASM_MASK(0, 5)) << 16);
    retVal |= ((args[1] & ASM_MASK(6, 11)) << 4);
  }
  else if(opBinBase == 0xAA0003E0) {
    retVal |= ASM_REG(args[0]);
    retVal |= (ASM_REG(args[1]) << 16);
  }
  else {
    retVal |= ASM_REG(args[0]);
    retVal |= ((args[1] & 0xFFFF) << 5);
  }

  return retVal;
}

uint32_t asmEncodeRET(void *argv, int argc) {
  if(argc < 7)
    return 0;

  ASM_ENCODING_BASE(argv);

  uint32_t retVal = opBinBase;
  retVal |= (ASM_REG(args[0]) << 5);

  return retVal;
}

uint32_t asmEncodeBRANCH(void* argv, int argc) {
  if(argc < 7)
    return 0;

  ASM_ENCODING_BASE(argv);

  uint32_t retVal = opBinBase;
  retVal |= (args[0] << 5) & ASM_MASK(5, 23);

  return retVal;
}
