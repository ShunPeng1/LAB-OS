#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>
#include<regex.h>
int m=1682;
int n=943;
//int n=10;
//int m=5;
int shmid;

void Regex(char *source){
    char * regexString = "([0-9]+)\t([0-9]+)\t([0-9]+)\t([0-9]+)";
    size_t maxMatches = 1;
    size_t maxGroups = 5;
    
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    unsigned int match;
    char * cursor;

    
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("Could not compile regular expression.\n");
        return ;
    };

    
    cursor = source;
    for (match = 0; match < maxMatches; match ++)
    {
        if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
            break;  // No more matches

        unsigned int g = 0;
        unsigned int offset = 0;
        int saveData[5];

        for (g = 0; g < maxGroups; g++)
        {
            if (groupArray[g].rm_so == (size_t)-1)
                break;  // No more groups

            if (g == 0){
                offset = groupArray[g].rm_eo;
                //continue;
            }
                

            char cursorCopy[strlen(cursor) + 1];
            strcpy(cursorCopy, cursor);
            cursorCopy[groupArray[g].rm_eo] = 0;
            //printf("Match %u, Group %u: [%2u-%2u]: %s\n", match, g, groupArray[g].rm_so, groupArray[g].rm_eo, cursorCopy + groupArray[g].rm_so);
            saveData[g] = atoi( cursorCopy + groupArray[g].rm_so);
            
        }
        cursor += offset;
        
        //printf("%u, %u, %u, %u\n", saveData[1],saveData[2],saveData[3],saveData[4]);

        double (*getter)[n];
        getter = shmat(shmid,0,0);
        getter[saveData[1]][saveData[2]] = saveData[3];
        //printf("say %f\n", getter[saveData[1]][saveData[2]]);
        if(shmdt(getter)==-1){
            perror("Problem of detachment");
            exit(1);
        }
    }
    
    regfree(&regexCompiled);
    return ;
}
/*
int ReadFile(char * fileName){
    FILE    *textfile;
    static int MAX_LINE_LENGTH = 50;
    char    *line;
     
    textfile = fopen(fileName, "r");
    if(textfile == NULL){
        printf("Fail get the file\n");
        return 1;
    }
        
    printf("File %s\n" , fileName);
    while(fgets(line, MAX_LINE_LENGTH, textfile)){
        printf("Print line : %s \n",line);
        Regex(line);
    }
     
    fclose(textfile);
    return 0;
}
*/

int ReadFile(char *fileName){
    FILE *textfile;
    static int MAX_LINE_LENGTH = 50;
    char *line = malloc(MAX_LINE_LENGTH * sizeof(char));  // Allocate memory for line
     
    textfile = fopen(fileName, "r");
    if(textfile == NULL){
        printf("Fail get the file\n");
        return 1;
    }
        
    printf("File %s\n", fileName);
    while(fgets(line, MAX_LINE_LENGTH, textfile)){
        //printf("Print line : %s \n", line);
        Regex(line);
    }
     
    fclose(textfile);
    free(line);  // Free memory allocated for line
    return 0;
}


void PrintBuffer(){
    double (*vector)[n];
    vector = shmat(shmid,0,0);
    if(vector==(void *)-1){
        perror("could not get shm \n");
        exit(1);
    } 
    
    for(int j=0;j<m;j++){

        double sum = 0, person = 0;

        for(int i=0;i<n;i++)
            if(vector[i][j] != -1.0){
                sum+= vector[i][j];
                person+=1;
            }
            
        if(person >0) printf("Movie ID = %d, Number of User = %d, Averager Rating = %f\n", j,(int) person,sum/person);
        
    }  
    if(shmdt(vector)==-1){
        perror("Fail to detach.");
        exit(1);
    }
}

void ResetBuffer(){
    double (*vector)[n];
    vector = shmat(shmid,0,0);
    if(vector==(void *)-1){
        perror("Reset could not get shm \n");
        exit(1);
    } 

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            vector[i][j]= -1.0;

    
    if(shmdt(vector)==-1){
        perror("Fail to detach.");
        exit(1);
    }
}


void InitBuffer(){
       
    shmid = shmget(IPC_PRIVATE, sizeof(double)*n*m*4,0666|IPC_CREAT);
       
    if(shmid<0){
	    perror("Fail to create shm \n");
	    exit(1);
    }
    
    ResetBuffer();
}

void CalculateAverage(char *filename){
    double (*vector)[n];
    vector = shmat(shmid,0,0);
    
    
    ReadFile(filename);
    if(shmdt(vector)==-1){
        perror("Problem of detachment");
        exit(1);
    }   
}

void DestroyBuffer(){
    if(shmctl(shmid,IPC_RMID,0)==-1){
        perror("Fail to destroy the segment");
        exit(1);
    }
}

int main(){
    InitBuffer();
    pid_t child_a, child_b;

    child_a = fork();

    if (child_a == 0) {
        /* Child A code */
        printf("Test case 1\n");
        char *file = "movie-100k_1.txt";
        CalculateAverage(file);
        //printf("1 finish");
        
        return 0;
    } 

    wait(NULL);
    PrintBuffer();
    ResetBuffer();
    child_b = fork();


    if (child_b == 0) {
        /* Child B code */

        printf("Test case 2\n");
        CalculateAverage("movie-100k_2.txt");
        
        //printf("Hi");
    }
    else {
        /* Parent Code */
        
        wait(NULL);
        PrintBuffer();
        ResetBuffer();
        
        DestroyBuffer();   
    }

    return 0;
}