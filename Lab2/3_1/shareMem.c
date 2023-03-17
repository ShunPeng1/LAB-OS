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

struct Rating{
    int userId;
    int movieId;
    int rating;
    int timeStamp;
};


void Regex(char *source){
    char * regexString = "([0-9]+)\t([0-9]+)\t([0-9]+)\t([0-9]+)";
    size_t maxMatches = 1;
    size_t maxGroups = 5;
    
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    unsigned int m;
    char * cursor;

    //struct Rating result = {0,0,0,0};
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("Could not compile regular expression.\n");
        return ;
    };

    m = 0;
    cursor = source;
    for (m = 0; m < maxMatches; m ++)
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
            //printf("Match %u, Group %u: [%2u-%2u]: %s\n", m, g, groupArray[g].rm_so, groupArray[g].rm_eo, cursorCopy + groupArray[g].rm_so);
            saveData[g] = atoi( cursorCopy + groupArray[g].rm_so);
            
        }
        cursor += offset;
        

        //struct Rating getData = {saveData[1],saveData[2],saveData[3],saveData[4]};
        //result = getData;
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
    //printf("%u, %u, %u, %u\n", result.userId, result.movieId, result.rating, result.timeStamp);
    regfree(&regexCompiled);
    return ;
}

int ReadFile(){
    FILE    *textfile;
    int MAX_LINE_LENGTH = 100;
    char    *line;
     
    textfile = fopen("movie-100k_1.txt", "r");
    if(textfile == NULL)
        return 1;
     
    while(fgets(line, MAX_LINE_LENGTH, textfile)){
        //printf(line);
        Regex(line);
    }
     
    fclose(textfile);
    return 0;
}



int main(){
       
       
    double (*vector)[n];
       
       
    shmid = shmget(IPC_PRIVATE, sizeof(double)*n*m*4,0666|IPC_CREAT);
       
    if(shmid<0){
	    perror("Fail to create shm \n");
	    exit(1);
    }
    else{
	    printf("shmid = %d\n",shmid);
	       
        vector = shmat(shmid,0,0);
        if(vector==(void *)-1){
            perror("could not get shm \n");
	        exit(1);
        } 
      
       	       
        for(int i=0;i<n;i++)
	        for(int j=0;j<m;j++)
		        vector[i][j]= -1;
        int pid= fork();

        if(!pid){
            printf("pid = %d \n",pid);
            double (*vec)[n];
            vec = shmat(shmid,0,0);
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)
                    ;//vec[i][j]=2;

            }
            ReadFile();
            if(shmdt(vec)==-1){
                perror("Problem of detachment");
                exit(1);
            }
        }
        else{
            wait(NULL);
            printf("parent childpid = %d\n",pid);
            for(int j=0;j<m;j++){

                double sum = 0, person = 0;

                for(int i=0;i<n;i++)
                    if(vector[i][j] != -1){
                        sum+= vector[i][j];
                        person+=1;
                    }
                    
                if(person >0) printf("Movie ID = %d, Number of User = %d, Averager Rating = %f\n", j,(int) person,sum/person);
                
            }  
            if(shmdt(vector)==-1){
                perror("Fail to detach.");
                exit(1);
            }
            if(shmctl(shmid,IPC_RMID,0)==-1){
                perror("Fail to destroy the segment");
                exit(1);
            }

        }
    }
       return 0;

}