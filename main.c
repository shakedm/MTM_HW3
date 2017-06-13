#include <stdio.h>


#include "usefullFunctions.h"


#define FREE_CLOSE {if (output!=stdout)\
                fclose(output);\
            if (input!=stdin)\
                fclose(input);}

/* in case of one flag use this function determine the flag and returns the
 * input and output channels accordingly after opening file*/
static MtmErrorCode passArgument(int argc , char** argv, FILE** F_input ,
                                FILE** F_output);

/*this function is called in case of use in both flags, open the  input and
 * output files and update the pointer to them*/
static MtmErrorCode passTwoArguments(char** argv, FILE** F_input,
                                     FILE** F_output);
/*function reads from the input channels and calles functions according to the
 * first word in the caommand*/
static MtmErrorCode readBuffer(EscapeTechnion sys,char * buffer, char* first_word,
FILE* output_channel);

/* in case of the first command being "room" this function continue to read
 * from the input and calls the functions of the ADT*/
static MtmErrorCode readRoom(EscapeTechnion sys,char* buffer);

/* in case of the first command being "company" this function continue to read
 * from the input and calls the functions of the ADT*/
static MtmErrorCode readCompany(EscapeTechnion sys,char* buffer);

/* in case of the first command being "escaper" this function continue to read
 * from the input and calls the functions of the ADT*/
static MtmErrorCode readEscaper(EscapeTechnion sys, char* buffer);

/* in case of the first command being "report" this function continue to read
 * from the input and calls the functions of the ADT*/
static MtmErrorCode readReport(EscapeTechnion sys, char* buffer, FILE* output);

//function translate the escapeTechnion enum of erorcode to those of MTM
static MtmErrorCode reverse(EscapeTechnionError result);

int main(int argc, char** argv) {
    MtmErrorCode result;
    FILE* input= stdin;
    FILE* output= stdout;
    switch(argc){
        case(1):
                break;
        case(3):
                result = passArgument(argc,argv,&input, &output);
                if(result!=MTM_SUCCESS){
                    mtmPrintErrorMessage(stdout,result);
                    return 0;
                }
        case(5):
                result = passTwoArguments(argv,&input, &output);
                if(result!=MTM_SUCCESS){
                    mtmPrintErrorMessage(stdout,result);
                    return 0;
                }
        default:
            mtmPrintErrorMessage(stdout,MTM_INVALID_COMMAND_LINE_PARAMETERS);
        }
    EscapeTechnion system;
    EscapeTechnionError result2=createEscapeTechnion(&system);
    result = reverse(result2);
    if (result!=MTM_SUCCESS){
        mtmPrintErrorMessage(output,result);
        FREE_CLOSE;
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
                FREE_CLOSE;
                resetSystem(system);
                return 0;
            }
            mtmPrintErrorMessage(output,result);
            continue;
        }

    }
    FREE_CLOSE;
    resetSystem(system);
    return 0;
}
static MtmErrorCode passArgument(int argc , char** argv,FILE** F_input,
                                 FILE** F_output){
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
    *F_input= input;
    *F_output= output;
    return  MTM_SUCCESS;
}
static MtmErrorCode passTwoArguments(char** argv,FILE** F_input,
                                     FILE** F_output){
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
    *F_input = input;
    *F_output = output;
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
    char* current;
    current=strtok(buffer, " \t");
    if(!current)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if (!strcmp(current,"remove")){
        current=strtok(NULL," \t");
        int faculty = atoi(current);
        current= strtok(NULL," \t");
        int id= atoi(current);
        EscapeTechnionError result = roomRemove(sys,faculty,id);
        return reverse(result);
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
        EscapeTechnionError result = roomAdd(sys,email,id,price,num_ppl,
                                             working_hours, difficulty);
        return reverse(result);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}

static MtmErrorCode readCompany(EscapeTechnion sys,char* buffer){
    char* current;
    current=strtok(NULL," \t");
    if (!current)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if(!strcmp(current,"remove")){
        current=strtok(NULL," \t");
        EscapeTechnionError result = companyRemove(sys,current);
        return reverse(result);

    }
    else if(!strcmp(current,"add")){
        current=strtok(NULL," \t");
        char* email=current;
        current=strtok(NULL," \t");
        int faculty= atoi(current);
        EscapeTechnionError result = companyAdd(sys, email,faculty);
        return reverse(result);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}
static MtmErrorCode readReport(EscapeTechnion sys, char* buffer, FILE* output){
    char * current = buffer;
    current=strtok(NULL," \t");
    if(!current)
        return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    if(!strcmp(current,"day")){
        EscapeTechnionError result = reportDay(sys,output);
        return reverse(result);
    }
    else if(!strcmp(current, "best")){
        EscapeTechnionError result = reportBest(sys,output);
        return reverse(result);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}
static MtmErrorCode readEscaper(EscapeTechnion sys, char* buffer){
    char* current;
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
        EscapeTechnionError result = escaperAdd(sys,email,faculty,skill);
        return reverse(result);
    }
    else if(!strcmp(current,"remove")){
        current=strtok(NULL," \t");
        EscapeTechnionError result = escaperRemove(sys,current);
        return reverse(result);
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
        EscapeTechnionError result = escaperOrder(sys,email,faculty,id,time,
                                                  num_ppl);
        return reverse(result);
    }
    else if(!strcmp(current,"recommend")){
        current=strtok(NULL," \t");
        char* email=current;
        current=strtok(NULL," \t");
        int num_ppl=atoi(current);
        EscapeTechnionError result = escaperRecommend(sys,email,num_ppl);
        return reverse(result);
    }
    return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}

static MtmErrorCode reverse(EscapeTechnionError result){
    switch (result){
        case ESCAPE_OUT_OF_MEMORY:
            return MTM_OUT_OF_MEMORY;
        case ESCAPE_NULL_PARAMETER:
            return MTM_NULL_PARAMETER;
        case ESCAPE_INVALID_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case ESCAPE_EMAIL_ALREADY_EXISTS:
            return MTM_EMAIL_ALREADY_EXISTS;
        case ESCAPE_COMPANY_EMAIL_DOES_NOT_EXIST:
            return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
        case ESCAPE_CLIENT_EMAIL_DOES_NOT_EXIST:
            return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
        case ESCAPE_ID_ALREADY_EXIST:
            return MTM_ID_ALREADY_EXIST;
        case ESCAPE_ID_DOES_NOT_EXIST:
            return MTM_ID_DOES_NOT_EXIST;
        case ESCAPE_CLIENT_IN_ROOM:
            return MTM_CLIENT_IN_ROOM;
        case ESCAPE_ROOM_NOT_AVAILABLE:
            return MTM_ROOM_NOT_AVAILABLE;
        case ESCAPE_RESERVATION_EXISTS:
            return MTM_RESERVATION_EXISTS;
        case ESCAPE_NO_ROOMS_AVAILABLE:
            return MTM_NO_ROOMS_AVAILABLE;
        case ESCAPE_SUCCESS:
            return MTM_SUCCESS;
    }
    return MTM_SUCCESS;
}