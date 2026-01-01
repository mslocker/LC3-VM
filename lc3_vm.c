#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <Windows.h>
#include <conio.h>

HANDLE hStdin = INVALID_HANDLE_VALUE;
DWORD fdwMode, fdwOldMode;

void disable_input_buffering()
{
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &fdwOldMode); /* save old mode */
    fdwMode = fdwOldMode
            ^ ENABLE_ECHO_INPUT  /* no input echo */
            ^ ENABLE_LINE_INPUT; /* return when one or
                                    more characters are available */
    SetConsoleMode(hStdin, fdwMode); /* set new mode */
    FlushConsoleInputBuffer(hStdin); /* clear buffer */
}

void restore_input_buffering()
{
    SetConsoleMode(hStdin, fdwOldMode);
}

uint16_t check_key()
{
    return WaitForSingleObject(hStdin, 1000) == WAIT_OBJECT_0 && _kbhit();
}

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX];

enum{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /* program counter */
    R_CONDITION,
    R_COUNT
};
uint16_t reg[R_COUNT];

enum{
    Flag_POS = 1 << 0, /* P */
    Flag_ZRO = 1 << 1, /* Z */
    Flag_NEG = 1 << 2  /* N */
};

enum{
    OP_BR = 0,   /* branch */
    OP_ADD,      /* add  */
    OP_LD,       /* load */
    OP_ST,       /* store */
    OP_JSR,      /* jump register */
    OP_AND,      /* bitwise and */
    OP_LDR,      /* load register */
    OP_STR,      /* store register */
    OP_RTI,      /* unused */
    OP_NOT,      /* bitwise not */
    OP_LDI,      /* load indirect */
    OP_STI,      /* store indirect */
    OP_JMP,      /* jump */
    OP_RES,      /* reserved (unused) */
    OP_LEA,      /* load effective address */
    OP_TRAP      /* execute trap */
};

int main(int argc, const char* argv[]){
    
    if (argc < 2){
        printf("lc3_vm [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; j++){
        if(!read_image(argv[j])){
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }

    reg[R_CONDITION] = Flag_ZRO;

    enum { PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    int running = 1;
    


    switch(op){
        case OP_AND:{
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t r1 = (instr >> 6) & 0x7;
            uint16_t imm_flag = (instr >> 5) & 0x1;
            if (imm_flag){
                uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                reg[r0] = reg[r1] & imm5;
            }
            else{
                uint16_t r2 = instr & 0x7;
                reg[r0] = reg[r1] & reg[r2];
            }
            update_flags(r0);
            break;
        }

        case OP_NOT:{
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t r1 = (instr >> 6) & 0x7;
            reg[r0] = ~reg[r1];
            update_flags(r0);
            break;
        }
    }


}