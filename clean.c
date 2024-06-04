#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char type[36];
    char manufacturer[16];
    int seats;
}AIRCRAFT;

int cmp(const void *a, const void *b){

    AIRCRAFT *left = (AIRCRAFT *)a;
    AIRCRAFT *right = (AIRCRAFT *)b;

    if(strcmp(left->manufacturer, right->manufacturer) !=0){
        return -(strcmp(left->manufacturer, right->manufacturer));
    }
    if(left->seats != right->seats){
        return left->seats - right->seats;
    }

    return -strcmp(left->type, right->type);
}

int main(int argc, char *argv[]){

    FILE *inputfile = fopen(argv[1], "r");

    char line[59];
    AIRCRAFT aircraft[150];
    int length = atoi(fgets(line, sizeof(line), inputfile));

    for(int i =0; i<length; i++){
        fgets(line, sizeof(line), inputfile);

        line[strlen(line)-1] = '\0';

        strcpy(aircraft[i].type, strtok(line, ";"));
        strcpy(aircraft[i].manufacturer, strtok(NULL, ";"));
        aircraft[i].seats = atoi(strtok(NULL, ";"));
    }
    fclose(inputfile);

    qsort(aircraft, length, sizeof(AIRCRAFT), cmp);

    FILE *outputfile = fopen(argv[2], "w");

    for(int i =0; i<length; i++){
        fprintf(outputfile, "#%d - %s;%s;%d\n", i+1, aircraft[i].type, aircraft[i].manufacturer, aircraft[i].seats);
    }

    fclose(outputfile);

    //char *manufacturer = "Boeing";

    return EXIT_SUCCESS;
}