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
//int n=1682;
//int m=943;
int n=10;
int m=5;
int shmid;

int main(){
       
       
    double (*vector)[n];
       
       
    shmid = shmget(IPC_PRIVATE, sizeof(double)*n*m*2,0666|IPC_CREAT);
       
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
		        vector[i][j]=-1;
        int pid= fork();
        if(!pid){
            printf("pid = %d \n",pid);
            double (*vec)[n];
            vec = shmat(shmid,0,0);
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)
                    vec[i][j]=2;

            }
            
            if(shmdt(vec)==-1){
                perror("Problem of detachment");
                exit(1);
            }
        }
        else{
            wait(NULL);
            printf("parent childpid = %d\n",pid);
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)
                    printf( "%f ", vector[i][j]);
                printf("\n");
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