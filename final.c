#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char account[41];
    char description[71];
    int length;
}INTAGRAM;

int cmp(const void *a, const void *b){
    INTAGRAM *left = (INTAGRAM *)a;
    INTAGRAM *right = (INTAGRAM *)b;

    if(strcmp(left->description, right->description) != 0){
        return -(strcmp(left->description, right->description));
    }
    if(strcmp(left->account, right->account)!= 0){
        return strcmp(left->account, right->account);
    }

    return -(left->length - right->length);
}

int main(int argc, char *argv[]){

    FILE *inputfile = fopen(argv[1], "r");

    char line[119];
    INTAGRAM intagram[150];
    int urefu = 0;

    while(1){
        fgets(line, sizeof(line), inputfile);

        line[strlen(line)-1] = '\0';

        if(!strcmp(line, "END")){
            break;
        }

        strcpy(intagram[urefu].account, strtok(line, ","));
        strcpy(intagram[urefu].description, strtok(NULL, ","));
        intagram[urefu].length = atoi(strtok(NULL, ","));
        urefu++;
    }

    fclose(inputfile);

    qsort(intagram, urefu, sizeof(INTAGRAM), cmp);

    FILE *outputfile = fopen(argv[2], "w");

    for(int i =0; i<urefu; i++){
        fprintf(outputfile, "%s,%s,%d\n", intagram[i].account, intagram[i].description, intagram[i].length);
    }

    fprintf(outputfile, "END\n");

    fclose(outputfile);

    return EXIT_SUCCESS;
}