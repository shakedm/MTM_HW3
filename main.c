#include <stdio.h>

#include "usefullFunctions.h"
#include "mtm_ex3.h"

static MtmErrorCode passArgument(int argc , char** argv);
static MtmErrorCode passTwoArguments(char** argv, FILE* F_input,
                                     FILE* F_output);

int main(int argc, char** argv) {
    MtmErrorCode result;
    FILE* input= stdin;
    FILE* output= stdout;
    switch(argc){
        case(1):
                break;
        case(3):
                result = passArgument(argc,argv);
                if(result!=MTM_SUCCESS){
                    mtmPrintErrorMessage(stdout,result);
                    return 0;
                }
        case(5):
                result = passTwoArguments(argv,input, output);
                if(result!=MTM_SUCCESS){
                    mtmPrintErrorMessage(stdout,result);
                    return 0;
                }
        default:
            mtmPrintErrorMessage(stdout,MTM_INVALID_COMMAND_LINE_PARAMETERS);
        }
}
static MtmErrorCode passArgument(int argc , char** argv){
    if(strcmp(argv[argc-1],"-o")!=0 && strcmp(argv[argc-1],"-i")!=0)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if (!strcmp(argv[argc-1],"-i")){
        FILE* input= fopen(argv[argc-1],"r");
        if (input==NULL)
            return MTM_CANNOT_OPEN_FILE;
    }
    assert(strcmp(argv[argc-1],"-o")==0);
    FILE* output= fopen(argv[argc-1],"w");
    if (output==NULL)
        return MTM_CANNOT_OPEN_FILE;

}
static MtmErrorCode passTwoArguments(char** argv,FILE* F_input,
                                     FILE* F_output){
    MtmErrorCode result;
    FILE* input;
    FILE* output;
    if(strcmp(argv[1],"-o")!=0 && strcmp(argv[1],"-i")!=0 &&
            strcmp(argv[3],"-i")!=0 && strcmp(argv[3],"-0")!=0)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if(!strcmp(argv[1],"-i")){
        input = fopen(argv[2],"r");
        if (!input)
            return MTM_CANNOT_OPEN_FILE;
        output = fopen(argv[4],"w");
        if(!output){
            fclose(input);
            return MTM_CANNOT_OPEN_FILE;
        }
    }
    else{
    assert(strcmp(argv[1],"-o")==0);
    output= fopen(argv[2],"w");
        if (!output){
            return MTM_CANNOT_OPEN_FILE;
        }
        input = fopen(argv[4],"r");
        if(!input){
            fclose(output);
            return MTM_CANNOT_OPEN_FILE;
        }
    }
    F_input = input;
    F_output = output;
    return MTM_SUCCESS;
}