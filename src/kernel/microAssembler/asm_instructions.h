/**
 * This is micro assembler instruction list
 */

#ifndef _PPDOS_KERNEL_MICRO_ASSEMBLER_INSTRUCTION_SET_
#define _PPDOS_KERNEL_MICRO_ASSEMBLER_INSTRUCTION_SET_

#include "../../common/shared_fn.h"

#define ASM_REG(register) (register & 0x1F)
#define ASM_MASK(lo, hi) ((0xFFFFFFFF >> hi) & (0xFFFFFFFF << lo))

#define ASM_ENCODING_BASE(argv) \
  uint32_t opBinBase = ((uint32_t*)argv)[0]; \
  uint32_t argType[3] = { ((uint32_t*)argv)[1], ((uint32_t*)argv)[2], ((uint32_t*)argv)[3] }; \
  uint32_t args[3] = { ((uint32_t*)argv)[4], ((uint32_t*)argv)[5], ((uint32_t*)argv)[6] } 


/**
 * This is helper enum describing basic values that instrucions can operate on
 */
typedef enum {
  asmArg_non = 0,  // none
  asmArg_reg = 1,  // register
  asmArg_imm = 2,  // immediate  
  asmArg_mem = 3,  // memory/label
  asmArg_shf = 4,  // shift
} asmArg_t;

/**
 * Encoding function template, must return valid 32 bit instruction, argv is accessible to assembler, tho must
 * follow the formula: { opBinBase, argType[3], 1st parsed argument, 2nd parsed ardument, 3rd parsed argument }.
 * These should be made to the most wide use case, so for example MOV, MOVZ, MOVK, etc. should be grupped together
 * and chacked at encoding stage. After passing 7 required argument, there could be more to describe current instruction,
 * tho this should be done by checking opBinBase
 */
typedef uint32_t (*PFN_asmEncode)(void* argv, int argc);

/**
 * This struct describe the instruction internals
 */
typedef struct asmInstruction_s {
  /* Mnematic of a instruction */
  const char* name;
  /* Binary base of a instruction */
  const uint32_t binBase;
  /* Amount of arguments that an instruction have */
  const uint32_t argCount;
  /* Types of arguments that an instruction have */
  asmArg_t argType[3];
  /* Instruction encoding function */
  PFN_asmEncode encode;
} asmInstruction_t;

/*************************
 * Encoiding functions 
 *************************/

/**
 * This function is used to encode MOV instructions
 */
uint32_t asmEncodeMOVx(void* argv, int argc);

/**
 * Function to encode RET instrucstions
 */
uint32_t asmEncodeRET(void* argv, int argc);

/**
 * Function to encode all B.<cond>, BC.<cond>, B, BL and BR instruction
 */
uint32_t asmEncodeBRANCH(void* argv, int argc);

/**
 * Function to encode all compare instructions
 */
uint32_t asmEncodeCMP(void* argv, int argc);

// TODO: Finish all instructions
const asmInstruction_t ASM_INSTRUCTIONS_MINIMUM_KERNEL[] = {
  // 
  // Base arithmetic and logic
  //
  {"ADD", 0x8B200000, 3, {asmArg_reg, asmArg_reg, asmArg_reg}},
  {"SUB", 0xCB000000, 3, {asmArg_reg, asmArg_reg, asmArg_reg}},
  {"CMP", },
  {"MOV", 0xAA0003E0, 2, {asmArg_reg, asmArg_reg, asmArg_non}, asmEncodeMOVx},
  {"MOV", 0xB20003E0, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  {"MOVZ", 0xD2800000, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  {"MOVK", 0xF2800000, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  {"MOVN", 0x92800000, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  {"AND"},
  {"ORR"},
  // XOR
  {"EOR", 0xD2000000, 3, {asmArg_reg, asmArg_reg, asmArg_imm}},
  // NOT
  {"MVN", 0xAA4001E0},
  {"TST"},
  {"LSL"},
  {"LSR"},
  {"ASR"},
  {"NEG"},
  {"ANDS"},
  {"ADDS"},

  //
  // Branching
  //
  {"B", 0x14000000, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BL", 0x94000000, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BR", 0xD61F0000, 1, {asmArg_reg, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"RET", 0xD65F0000, 1, {asmArg_reg, asmArg_non, asmArg_non}, asmEncodeRET},
  // Branch conditionally
  // On equal
  {"B.EQ", 0x54000000, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On not equal
  {"B.NE", 0x54000001, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.CS", 0x54000002, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.CC", 0x54000003, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.MI", 0x54000004, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.PL", 0x54000005, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.VS", 0x54000006, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.VC", 0x54000007, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.HI", 0x54000008, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.LS", 0x54000009, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On greater or equal
  {"B.GE", 0x5400000A, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.LT", 0x5400000B, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.GT", 0x5400000C, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On less or equal
  {"B.LE", 0x5400000D, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.AL", 0x5400000E, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.NV", 0x5400000F, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},

  {"CBZ", 0xB4000000, 2, {asmArg_reg, asmArg_mem, asmArg_non}, asmEncodeCMP},
  {"CBNZ", 0xB5000000, 2, {asmArg_reg, asmArg_mem, asmArg_non}, asmEncodeCMP},
  {"TBNZ", 0xB7000000, 3, {asmArg_reg, asmArg_imm, asmArg_mem}, asmEncodeCMP},
  {"TBZ", 0xB6000000, 3, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeCMP},

  //
  // Memory and stack
  //
  {"LDR", 0x58000000, 2, {asmArg_reg, asmArg_mem, asmArg_non}},
  {"STR"},
  {"LDRB"},
  {"STRB"},
  {"LDRH"},
  {"STRH"},
  {"LDRSW"},
  {"LDUR"},
  {"STUR"},
  {"LDP"},
  {"STP"},
  {"ADD"},
  {"SUB"},
  {"ADR"},
  {"ADRP"},
  
  //
  // System control
  //
  {"SVC"},
  {"MSR"},
  {"MRS"},
  {"ISB"},
  {"DSB"},
  {"DMB"},
  {"CLREX"},
  {"WFI"},
  {"SEV"},
  {"WFE"},
  {"HLT"},
  {"BRK"},
  {"ERET"},
  {"TLBI"},
  {"DC"},
  {"IC"},
  {"YIELD"},
  {"NOP"},
  {"AT"},
  {"SYS"},
  {"SYSL"},

  //
  // Sync/atomics
  //
  {"LDXR"},
  {"STXR"},
  {"LDAXR"},
  {"STLXR"},
  {"CLREX"}
};

const asmInstruction_t ASM_INSTRUCTIONS_RICH_KERNEL[] = {
  //
  // Control flow and select
  //
  {"CSEL"},
  {"CSINC"},
  {"CSNEG"},
  {"CCMP"},
  {"CINC"},
  {"CINV"},

  //
  // Multiply and divide
  //
  {"MUL"},
  {"MADD"},
  {"MSUB"},
  {"SMULL"},
  {"UMULL"},
  {"SDIV"},
  {"UDIV"},

  //
  // Bitfield
  //
  {"BFM"},
  {"UBFM"},
  {"SBFM"},
  {"BFXIL"},
  {"EXTR"},
  {"RBIT"},
  {"CLZ"},
  {"CLS"},
  {"REV"},
  {"REV16"},
  {"REV32"},
  {"REV64"},
  {"CNT"},
  {"CTZ"},

  //
  // System ops and debug
  //
  {"DCPS1"},
  {"DCPS2"},
  {"DCPS3"},
  {"ERETAA"},
  {"ERETAB"},
  {"PSB"},
  {"CSDB"},
  {"SB"},
  {"SSBB"},
  {"PSSBB"},
  {"TSB"},
  {"GCSB"},

  //
  // Extras
  //
  {"CRC32B"},
  {"CRC32H"},
  {"CRC32W"},
  {"CRC32X"},
  {"CRC32CB"},
  {"CRC32CH"},
  {"CRC32CW"},
  {"CRC32CX"},
  {"ABS"},
  {"NGC"},
  {"NGCS"},
  {"ORN"},
  {"BIC"},
  {"EON"},
  {"ASRV"},
  {"LSRV"},
  {"RORV"},
};

/* Unfinished  */
const asmInstruction_t ASM_INSTRUCTIONS_FULL[] = {
  // Move bitmask immediate
  {"MOV", 0xB20003E0, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  // Move register
  {"MOV", 0xAA0003E0, 2, {asmArg_reg, asmArg_reg, asmArg_non}, asmEncodeMOVx},
  // MOVZ
  {"MOV", 0xD2800000, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  // Move inverted wide immediate
  {"MOV", 0x92800000, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  // Move wide with not
  {"MOVN", 0x92800000, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  // Move wide with zero
  {"MOVZ", 0xD2800000, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},
  // Move wide with keep
  {"MOVK", 0xF2800000, 2, {asmArg_reg, asmArg_imm, asmArg_non}, asmEncodeMOVx},

  // Branch conditionally
  // On equal
  {"B.EQ", 0x54000000, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On not equal
  {"B.NE", 0x54000001, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.CS", 0x54000002, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.CC", 0x54000003, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.MI", 0x54000004, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.PL", 0x54000005, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.VS", 0x54000006, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.VC", 0x54000007, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.HI", 0x54000008, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.LS", 0x54000009, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On greater or equal
  {"B.GE", 0x5400000A, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.LT", 0x5400000B, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.GT", 0x5400000C, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On less or equal
  {"B.LE", 0x5400000D, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.AL", 0x5400000E, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"B.NV", 0x5400000F, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},

  // Branch consistent conditionally
  // On equal
  {"BC.EQ", 0x54000010, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On not equal
  {"BC.NE", 0x54000011, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.CS", 0x54000012, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.CC", 0x54000013, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.MI", 0x54000014, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.PL", 0x54000015, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.VS", 0x54000016, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.VC", 0x54000017, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.HI", 0x54000018, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.LS", 0x54000019, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On greater or equal
  {"BC.GE", 0x5400001A, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.LT", 0x5400001B, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.GT", 0x5400001C, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  // On less or equal
  {"BC.LE", 0x5400001D, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.AL", 0x5400001E, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},
  {"BC.NV", 0x5400001F, 1, {asmArg_mem, asmArg_non, asmArg_non}, asmEncodeBRANCH},

  {"CBNZ"},
  {"CBZ"},
  {"TBNZ"},
  {"TBZ"},
  {"B"},
  {"BL"},
  {"BLR"},
  {"BR"},
  {"BLRAA"},
  {"BLRAAZ"},
  {"BLRAB"},
  {"BLRABZ"},
  {"BRAA"},
  {"BRAAZ"},
  {"BRAB"},
  {"BRABZ"},

  // Return from subroutine
  {"RET", 0xD65F0000, 1, {asmArg_reg, asmArg_non, asmArg_non}, asmEncodeRET},
  {"RETAA"},
  {"RETAB"},
  {"RETAASPPC"},
  {"RETABSPPC"},
  {"RETAASPPCR"},
  {"RETABSPPCR"},
  {"ERET"},
  {"ERETAA"},
  {"ERETAB"},

  {"BRK"},
  {"HLT"},
  {"HVC"},
  {"SMC"},
  {"SVC"},

  {"DCPS1"},
  {"DCPS2"},
  {"DCPS3"},
  {"DRPS"},

  {"MRS"},
  {"MSR"},
  {"MRRS"},
  {"MSRR"},

  {"SYS"},
  {"SYSL"},
  {"SYSP"},
  {"IC"},
  {"DC"},
  {"AT"},
  {"TLBI"},

  {"NOP"},
  {"YIELD"},
  {"WFE"},
  {"WFET"},
  {"WFI"},
  {"WFIT"},
  {"SEV"},
  {"SEVL"},
  {"HINT"},
  {"DGH"},
  {"CLRBHB"},
  {"CHKFEAT"},

  {"CLREX"},
  {"DMB"},
  {"DSB"},
  {"ISB"},

  {"CSDB"},
  {"ESB"},
  {"PSB"},
  {"PSSBB"},
  {"SB"},
  {"SSBB"},
  {"TSB"},
  {"GCSB"},

  {"LDR"},
  {"LDRB"},
  {"LDRSB"},
  {"LDRH"},
  {"LDRSH"},
  {"LDRSW"},
  {"STR"},
  {"STRB"},
  {"STRH"},

  {"LDUR"},
  {"LDURB"},
  {"LDURSB"},
  {"LDURH"},
  {"LDURSH"},
  {"LDURSW"},
  {"STUR"},
  {"STURB"},
  {"STURH"},

  {"ADD"},
  {"ADDS"},
  {"SUB"},
  {"SUBS"},
  {"CMP"},
  {"CMN"},

  {"SMAX"},
  {"SMIN"},
  {"UMAX"},
  {"UMIN"},

  {"AND"},
  {"ANDS"},
  {"EOR"},
  {"ORR"},
  {"TST"},

  {"ADRP"},
  {"ADR"},
  {"BFM"},
  {"SBFM"},
  {"UBFM"},
  
  {"BFC"},
  {"BFI"},
  {"BFXIL"},
  {"SBFIZ"},
  {"SBFX"},
  {"UBFIZ"},
  {"UBFX"},
  {"EXTR"},

  {"ASR"},
  {"LSL"},
  {"LSR"},
  {"ROR"},

  {"SXTB"},
  {"SXTH"},
  {"UXTB"},
  {"UXTH"},

  {"SUBP"},
  {"SUBPS"},

  {"ADDG"},
  {"GMI"},
  {"IRG"},
  {"SUBG"},

  {"ADD"},
  {"ADDS"},
  {"SUB"},
  {"SUBS"},
  {"CMN"},
  {"CMP"},
  {"NEG"},
  {"NEGS"},

  {"ADD"},
  {"ADDS"},
  {"SUB"},
  {"SUBS"},
  {"CMN"},
  {"CMP"},

  {"ADC"},
  {"ADCS"},
  {"SBC"},
  {"SBCS"},
  {"NGC"},
  {"NGCS"},
  
  {"SMAX"},
  {"SMIN"},
  {"UMAX"},
  {"UMIN"},

  {"AXFLAG"},
  {"CFINV"},
  {"RMIF"},
  {"SETF8"},
  {"SETF16"},
  {"XAFLAG"},

  {"AND"},
  {"ANDS"},
  {"BIC"},
  {"BICS"},
  {"EON"},
  {"EOR"},
  {"ORR"},
  {"MVN"},
  {"ORN"},
  {"TST"},

  {"ABS"},

  {"ASRV"},
  {"LSLV"},
  {"LSRV"},
  {"RORV"},

  {"ASR"},
  {"LSL"},
  {"LSR"},
  {"ROR"},

  {"MADD"},
  {"MSUB"},
  {"MNEG"},
  {"MUL"},
  {"SMADDL"},
  {"SMSUBL"},
  {"SMNEGL"},
  {"SMULL"},
  {"SMULH"},
  {"UMADDL"},
  {"UMSUBL"},
  {"UMNEGL"},
  {"UMULL"},
  {"UMULH"},

  {"SDIV"},
  {"UDIV"},
  
  {"CRC32B"},
  {"CRC32H"},
  {"CRC32W"},
  {"CRC32X"},
  {"CRC32CB"},
  {"CRC32CH"},
  {"CRC32CW"},
  {"CRC32CX"},

  {"CLS"},
  {"CLZ"},
  {"CNT"},
  {"CTZ"},
  {"RBIT"},
  {"REV"},
  {"REV16"},
  {"REV32"},
  {"REV64"},
};

typedef struct asmRegister_s {
  const char* name;
  const uint32_t regValue;
} asmRegister_t;

/**
 * All 64 bit registers mapped to their names
 */
const asmRegister_t ASM_REGISTERS64[] = {
  {"X0", ASM_REG(0)},
  {"X1", ASM_REG(1)},
  {"X2", ASM_REG(2)},
  {"X3", ASM_REG(3)},
  {"X4", ASM_REG(4)},
  {"X5", ASM_REG(5)},
  {"X6", ASM_REG(6)},
  {"X7", ASM_REG(7)},
  {"X8", ASM_REG(8)},
  {"X9", ASM_REG(9)},
  {"X10", ASM_REG(10)},
  {"X11", ASM_REG(11)},
  {"X12", ASM_REG(12)},
  {"X13", ASM_REG(13)},
  {"X14", ASM_REG(14)},
  {"X15", ASM_REG(15)},
  {"X16", ASM_REG(16)},
  {"X17", ASM_REG(17)},
  {"X18", ASM_REG(18)},
  {"X19", ASM_REG(19)},
  {"X20", ASM_REG(20)},
  {"X21", ASM_REG(21)},
  {"X22", ASM_REG(22)},
  {"X23", ASM_REG(23)},
  {"X24", ASM_REG(24)},
  {"X25", ASM_REG(25)},
  {"X26", ASM_REG(26)},
  {"X27", ASM_REG(27)},
  {"X28", ASM_REG(28)},
  {"X29", ASM_REG(29)},
  {"X30", ASM_REG(30)},

  {"XZR", ASM_REG(31)},
  {"SP", ASM_REG(31)},

  /* Map for all small letters as well */
  {"x0", ASM_REG(0)},
  {"x1", ASM_REG(1)},
  {"x2", ASM_REG(2)},
  {"x3", ASM_REG(3)},
  {"x4", ASM_REG(4)},
  {"x5", ASM_REG(5)},
  {"x6", ASM_REG(6)},
  {"x7", ASM_REG(7)},
  {"x8", ASM_REG(8)},
  {"x9", ASM_REG(9)},
  {"x10", ASM_REG(10)},
  {"x11", ASM_REG(11)},
  {"x12", ASM_REG(12)},
  {"x13", ASM_REG(13)},
  {"x14", ASM_REG(14)},
  {"x15", ASM_REG(15)},
  {"x16", ASM_REG(16)},
  {"x17", ASM_REG(17)},
  {"x18", ASM_REG(18)},
  {"x19", ASM_REG(19)},
  {"x20", ASM_REG(20)},
  {"x21", ASM_REG(21)},
  {"x22", ASM_REG(22)},
  {"x23", ASM_REG(23)},
  {"x24", ASM_REG(24)},
  {"x25", ASM_REG(25)},
  {"x26", ASM_REG(26)},
  {"x27", ASM_REG(27)},
  {"x28", ASM_REG(28)},
  {"x29", ASM_REG(29)},
  {"x30", ASM_REG(30)},
  
  {"xzr", ASM_REG(31)},
  {"sp", ASM_REG(31)},

  /* My additional mappings */
  {"zero", ASM_REG(31)},
  {"stack", ASM_REG(31)}
};

/**
 * All 32 bit registers
 */
const asmRegister_t ASM_REGISTERS32[] = {
  {"W0", ASM_REG(0)},
  {"W1", ASM_REG(1)},
  {"W2", ASM_REG(2)},
  {"W3", ASM_REG(3)},
  {"W4", ASM_REG(4)},
  {"W5", ASM_REG(5)},
  {"W6", ASM_REG(6)},
  {"W7", ASM_REG(7)},
  {"W8", ASM_REG(8)},
  {"W9", ASM_REG(9)},
  {"W10", ASM_REG(10)},
  {"W11", ASM_REG(11)},
  {"W12", ASM_REG(12)},
  {"W13", ASM_REG(13)},
  {"W14", ASM_REG(14)},
  {"W15", ASM_REG(15)},
  {"W16", ASM_REG(16)},
  {"W17", ASM_REG(17)},
  {"W18", ASM_REG(18)},
  {"W19", ASM_REG(19)},
  {"W20", ASM_REG(20)},
  {"W21", ASM_REG(21)},
  {"W22", ASM_REG(22)},
  {"W23", ASM_REG(23)},
  {"W24", ASM_REG(24)},
  {"W25", ASM_REG(25)},
  {"W26", ASM_REG(26)},
  {"W27", ASM_REG(27)},
  {"W28", ASM_REG(28)},
  {"W29", ASM_REG(29)},
  {"W30", ASM_REG(30)},

  {"WZR", ASM_REG(31)},
  {"WSP", ASM_REG(31)},

  /* Map for all small letters as well */
  {"w0", ASM_REG(0)},
  {"w1", ASM_REG(1)},
  {"w2", ASM_REG(2)},
  {"w3", ASM_REG(3)},
  {"w4", ASM_REG(4)},
  {"w5", ASM_REG(5)},
  {"w6", ASM_REG(6)},
  {"w7", ASM_REG(7)},
  {"w8", ASM_REG(8)},
  {"w9", ASM_REG(9)},
  {"w10", ASM_REG(10)},
  {"w11", ASM_REG(11)},
  {"w12", ASM_REG(12)},
  {"w13", ASM_REG(13)},
  {"w14", ASM_REG(14)},
  {"w15", ASM_REG(15)},
  {"w16", ASM_REG(16)},
  {"w17", ASM_REG(17)},
  {"w18", ASM_REG(18)},
  {"w19", ASM_REG(19)},
  {"w20", ASM_REG(20)},
  {"w21", ASM_REG(21)},
  {"w22", ASM_REG(22)},
  {"w23", ASM_REG(23)},
  {"w24", ASM_REG(24)},
  {"w25", ASM_REG(25)},
  {"w26", ASM_REG(26)},
  {"w27", ASM_REG(27)},
  {"w28", ASM_REG(28)},
  {"w29", ASM_REG(29)},
  {"w30", ASM_REG(30)},
  
  {"wzr", ASM_REG(31)},
  {"wsp", ASM_REG(31)},

  /* My additional mappings */
  {"zero32", ASM_REG(31)},
  {"stack32", ASM_REG(31)}
};

#endif
