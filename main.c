#include <stdio.h>


#include "usefullFunctions.h"
#include "mtm_ex3.h"

#define FREE_CLOSE{}


static MtmErrorCode passArgument(int argc , char** argv, FILE* F_input ,
                                FILE* F_output);
static MtmErrorCode passTwoArguments(char** argv, FILE* F_input,
                                     FILE* F_output);
static MtmErrorCode readBuffer(EscapeTechnion sys,char * buffer, char* first_word,
FILE* output_channel);

static MtmErrorCode readRoom(EscapeTechnion sys,char* buffer);

static MtmErrorCode readCompany(EscapeTechnion sys,char* buffer);

static MtmErrorCode readEscaper(EscapeTechnion sys, char* buffer);

static MtmErrorCode readReport(EscapeTechnion sys, char* buffer, FILE* output);

int main(int argc, char** argv) {
    MtmErrorCode result;
    FILE* input= stdin;
    FILE* output= stdout;
    switch(argc){
        case(1):
                break;
        case(3):
                result = passArgument(argc,argv,input, output);
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
    EscapeTechnion system;
    result=createEscapeTechnion(&system);
    if (result!=MTM_SUCCESS){
        mtmPrintErrorMessage(output,result);
        if (output!=stdout)
            fclose(output);
        if (input!=stdin)
            fclose(input);
        return 0;
    }
    char buffer[MAX_LEN];
    char* first_word;
    while(fgets(buffer,MAX_LEN-1,input) !=NULL){
        first_word = strtok(buffer," \t");
        result = readBuffer(system,buffer, first_word,output);
        if(result!=MTM_SUCCESS){
            if (result==MTM_OUT_OF_MEMORY){
                mtmPrintErrorMessage(output,MTM_OUT_OF_MEMORY);
                if(output!=stdout)
                    fclose(output);
                if (input!=stdin)
                    fclose(input);
                resetSystem(system);
                return 0;
            }
            mtmPrintErrorMessage(output,result);
            continue;
        }

    }
    if(output!= stdout)
        fclose(output);
    if(input!= stdin)
        fclose(input);
    resetSystem(system);
    return 0;
}
static MtmErrorCode passArgument(int argc , char** argv,FILE* F_input,
                                 FILE* F_output){
    if(strcmp(argv[argc-1],"-o")!=0 && strcmp(argv[argc-1],"-i")!=0)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    FILE* input = stdin;
    FILE* output = stdout;
    if (!strcmp(argv[argc-1],"-i")){
        input= fopen(argv[argc-1],"r");
        if (input==NULL)
            return MTM_CANNOT_OPEN_FILE;
    }
    else{
    assert(strcmp(argv[argc-1],"-o")==0);
    output= fopen(argv[argc-1],"w");
    if (output==NULL)
        return MTM_CANNOT_OPEN_FILE;
    }
    F_input= input;
    F_output= output;
    return  MTM_SUCCESS;
}
static MtmErrorCode passTwoArguments(char** argv,FILE* F_input,
                                     FILE* F_output){
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

static MtmErrorCode readBuffer(EscapeTechnion sys,char* buffer, char* first_word,
                               FILE* output_channel){
    if(first_word[0]=='#')
        return MTM_SUCCESS; //just continue to the next line
    if (!strcmp(first_word,"room")){
        return readRoom(sys,buffer);
    }
    if(!strcmp(first_word,"company")){
        return readCompany(sys,buffer);
    }
    if(!strcmp(first_word,"escaper")){
        return readEscaper(sys,buffer);
    }
    if(!strcmp(first_word,"report")){
        return readReport(sys,buffer,output_channel);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;

}

static MtmErrorCode readRoom(EscapeTechnion sys,char* buffer){
    char* current = buffer;
    current=strtok(buffer, " \t");
    if(!current)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if (!strcmp(current,"remove")){
        current=strtok(NULL," \t");
        int faculty = atoi(current);
        current= strtok(NULL," \t");
        int id= atoi(current);
        return roomRemove(sys,faculty,id);
    }
    else if(!strcmp(current,"add")){
        current=strtok(NULL," \t");
        char* email=current;
        current=strtok(NULL," \t");
        int id=atoi(current);
        current=strtok(NULL," \t");
        int price=atoi(current);
        current=strtok(NULL," \t");
        int num_ppl=atoi(current);
        current=strtok(NULL," \t");
        char* working_hours=current;
        current=strtok(NULL," \t");
        int difficulty= atoi(current);
        return roomAdd(sys,email,id,price,num_ppl,working_hours,
                                     difficulty);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}

static MtmErrorCode readCompany(EscapeTechnion sys,char* buffer){
    char* current =buffer;
    current=strtok(NULL," \t");
    if (!current)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if(!strcmp(current,"remove")){
        current=strtok(NULL," \t");
        return companyRemove(sys,current);

    }
    else if(!strcmp(current,"add")){
        current=strtok(NULL," \t");
        char* email=current;
        current=strtok(NULL," \t");
        int faculty= atoi(current);
        return companyAdd(sys, email,faculty);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}
static MtmErrorCode readReport(EscapeTechnion sys, char* buffer, FILE* output){
    char * current = buffer;
    current=strtok(NULL," \t");
    if(!current)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if(!strcmp(current,"day"))
        return reportDay(sys,output);
    else if(!strcmp(current, "best")){
        return reportBest(sys,output);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}
static MtmErrorCode readEscaper(EscapeTechnion sys, char* buffer){
    char* current = buffer;
    current=strtok(NULL, " \t");
    if (!current)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if(!strcmp(current,"add")){
        current=strtok(NULL," \t");
        char* email= current;
        current=strtok(NULL," \t");
        int faculty= atoi(current);
        current=strtok(NULL," \t");
        int skill=atoi(current);
        return escaperAdd(sys,email,faculty,skill);
    }
    else if(!strcmp(current,"remove")){
        current=strtok(NULL," \t");
        return escaperRemove(sys,current);
    }
    else if(!strcmp(current, "order")){
        current=strtok(NULL," \t");
        char* email=current;
        current=strtok(NULL," \t");
        int faculty=atoi(current);
        current=strtok(NULL," \t");
        int id=atoi(current);
        current=strtok(NULL," \t");
        char* time=current;
        current=strtok(NULL," \t");
        int num_ppl=atoi(current);
        return escaperOrder(sys,email,faculty,id,time,num_ppl);
    }
    else if(!strcmp(current,"recommend")){
        current=strtok(NULL," \t");
        char* email=current;
        current=strtok(NULL," \t");
        int num_ppl=atoi(current);
        return escaperRecommend(sys,email,num_ppl);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}