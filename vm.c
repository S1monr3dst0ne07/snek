
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char src_buffer[2048] = { 0 };
char* src_ptr = src_buffer;

enum insts_t
{
    INST_CONST,
    INST_ADD,
    INST_SUB,
    INST_LOAD,
    INST_STORE,
    INST_PRINT,
    INST_JUMP,
    INST_HALT,
};


struct cmd
{
    char inst_raw[16];
    char arg_raw[16];

    enum insts_t inst;
    int arg;

} prog[128] = { 0 };
int prog_len = 0;



void lex_eier(char* src_path)
{

    FILE* f = fopen(src_path, "r");
    fread(src_buffer, sizeof(src_buffer), 1, f);
}



void parse()
{
    enum
    {
        STATE_INIT = 1,
        STATE_INST,
        STATE_ARG,
        STATE_DONE,
    } state = STATE_INIT;
   
    int inst_index = 0;
    int arg_index = 0;

    while (state != STATE_DONE)
    {
        switch(*src_ptr)
        {
            case '\n':
                prog[prog_len].inst_raw[inst_index] = '\0';
                prog[prog_len++].arg_raw[arg_index] = '\0';
                src_ptr++; 
                state = STATE_INIT;
                break;
            case '\0':
            case EOF:
                prog[prog_len].inst_raw[inst_index] = '\0';
                prog[prog_len].arg_raw[arg_index] = '\0';
                src_ptr++; 
                state = STATE_DONE;
                break;
        }

        switch(state)
        {
            case STATE_INIT:
                if (*src_ptr == ' ')  continue;
                if (*src_ptr == '\n') continue;

                inst_index = 0;
                arg_index = 0;

                state = STATE_INST;
                break;

            case STATE_INST:
                if (*src_ptr == ' ')
                {
                    src_ptr++; 
                    prog[prog_len].inst_raw[inst_index] = '\0';
                    state = STATE_ARG;
                }
                else
                    prog[prog_len].inst_raw[inst_index++] = *src_ptr++;

                break;
            
            case STATE_ARG:
                prog[prog_len].arg_raw[arg_index++] = *src_ptr++;
                
                break;
        }
    }
}


void map()
{
    //map instruction into enum
    for (int i = 0; i < prog_len; i++)
        /**/ if (!strcmp(prog[i].inst_raw, "const")) prog[i].inst = INST_CONST;
        else if (!strcmp(prog[i].inst_raw, "add"))   prog[i].inst = INST_ADD;
        else if (!strcmp(prog[i].inst_raw, "sub"))   prog[i].inst = INST_SUB;
        else if (!strcmp(prog[i].inst_raw, "load"))  prog[i].inst = INST_LOAD;
        else if (!strcmp(prog[i].inst_raw, "store")) prog[i].inst = INST_STORE;
        else if (!strcmp(prog[i].inst_raw, "print")) prog[i].inst = INST_PRINT;
        else if (!strcmp(prog[i].inst_raw, "jump"))  prog[i].inst = INST_JUMP;
        else if (!strcmp(prog[i].inst_raw, "halt"))  prog[i].inst = INST_HALT;

    //map argument
    for (int i = 0; i < prog_len; i++)
        prog[i].arg = prog[i].arg_raw ? atoi(prog[i].arg_raw) : 0;
}



int main(int argc, char** argv)
{
    char* src_path = argv[1];
    printf("starting from: %s\n", src_path);
    lex_eier(src_path);
    parse();
    map();

    int pc = 0;
    int acc = 0;
    int mem[128] = { 0 };

    while (pc < prog_len)
    {
        struct cmd* command = &prog[pc++];
        int arg = command->arg; 

        switch(command->inst)
        {
            case INST_CONST: acc = arg;             break;
            case INST_ADD:   acc += mem[arg];       break;
            case INST_SUB:   acc -= mem[arg];       break;
            case INST_LOAD:  acc = mem[arg];        break;
            case INST_STORE: mem[arg] = acc;        break;
            case INST_PRINT: printf("%d\n", acc);   break;
            case INST_JUMP:  pc = arg;              break;
            case INST_HALT:  pc = prog_len;         break;
        }

    }

}







