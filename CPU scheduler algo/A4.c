
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


//CPU scheduler functions
void *fCFS (int jobs, int arrival[], int CPUburst[]);
void *NSJF(int job, int begin[], int CPU[]);
void *roundRobin(int jobs, int arrive[], int CPUtime[]);   
 
//Arrays to store arrival time and cpu burst
 int arrivalTime[50];
 int burst[50];

//Output file for storing results
 FILE *outPut;
    
int main()
{

    int noOfJobs;
    FILE *inputFile;                              //Initiate file
    char temp[100];                               //to store as string
    char *cutter;                                //will be used for tokenizing
    inputFile = fopen("TaskSpec.txt","r"); 

    //The whole implementation of fgets and the while loop is taken from:
    //https://stackoverflow.com/questions/12499219/using-fgets-and-strtok-to-read-in-a-file-line-by-line-in-c
    
    int a,b;
    a=b=0;
    
    //while end of file is not reached read the text file and store data	
    while(fgets(temp,sizeof(temp), inputFile)){

        //do nothing for first part
        cutter = strtok(temp, ",");
        
        //store arrival time in array
        cutter = strtok(NULL, ",");
        arrivalTime[a]=atoi(cutter);
        a++;
        
        //store cpuBurst in array
        cutter = strtok(NULL, " \n");
        burst[b]=atoi(cutter);
        b++;
        
    }
     fclose(inputFile);				//close file
     noOfJobs=b;
    
     outPut = fopen("Output.txt", "w");	      //Open file for writing
     fCFS(noOfJobs,arrivalTime, burst);        //writes to output file inside method

     NSJF(noOfJobs,arrivalTime,burst);        //writes to output file inside method
     fclose(outPut);			     //close file
        
       
    return 0;
 }


    void *NSJF(int job, int begin[], int CPU[]){
        int a, waitTime[job-1], avgWait=0, totalTime=0,startTime=0, endTime;
        int q,s;
        
	int e[50];
	int count=1;
        
	for(a=0;a<50;a++){			//create up to 50 task numbers
            e[a]=count;
	    count++;
        }

        s=0;
        int temp1,temp2, jobTemp1;  		//temporary variable to switch value in array
        
	fprintf(outPut, "\n %s \n", "NPSJF");   //print to output file
        
	for(q=0; q<job; q++){

            //start time for task
            startTime=totalTime;

            //update total time after first task
            totalTime=totalTime+CPU[q]; 

            //update end time of task
            endTime=totalTime;
            
            s++;    				//keep s updated with q for comparision
            fprintf(outPut, "T%d\t%d\t%d\n", e[q], startTime, endTime);
            
            if(s<job-1){
               if(CPU[s]>CPU[s+1]){		//when next cpu burst is smaller than current
                temp1 = CPU[s];
                temp2 = begin[s];
                jobTemp1=s;
                
		//swap contents
                CPU[s]= CPU[s+1];
                CPU[s+1]=temp1;
                
                e[s]=e[s+1];         
                e[s+1]=jobTemp1+1;
              
                
                begin[s]=begin[s+1];
                begin[s+1]=temp2;
                
                
               }
            }
             waitTime[q]=startTime-begin[q];       //update waitTime
                                                
        }
        for(q=0;q<job;q++){                      //Print wait time for each Task
            fprintf(outPut, "Waiting time T%d: %d\n", e[q], waitTime[q]);
        }
      
        //Calculate average time
        float average=0;                    //https://www.geeksforgeeks.org/g-fact-41-setting-decimal-precision-in-c/
        for(q=0;q<job;q++){
           average = average + waitTime[q];
        }
    	
        //Print average time taken
        fprintf(outPut, "Average Waiting time: %0.2f\n", average/job);
    }
    
    
    
    void *roundRobin(int jobs, int arrive[], int CPUtime[]){
        int a, waitTime[jobs-1], avgWait=0, totalTime=0,startTime=0, endTime;
        int quntum = 4;         //in milliseconds
        //finish when last task has ended
        while(CPUtime[jobs-1]!=0){
            for(a=4;a>0;a--){
                
            }
            
        }    
    }
    
    void *fCFS (int jobs, int arrival[], int CPUburst[]){
        
        int a, waitTime[jobs-1], avgWait=0, totalTime=0,startTime=0, endTime;
        //Algo will finish current then switch to next job

        fprintf(outPut, "\n %s \n", "FCFS");  		//print to output

        for(a=0; a<jobs; a++){
            
            //start time for task
            startTime=totalTime;
            //update total time after first task
            totalTime=totalTime+CPUburst[a]; 
            //update end time of task
            endTime=totalTime;
            
            fprintf(outPut, "T%d\t%d\t%d\n", a+1, startTime, endTime);
           
            waitTime[a]=startTime-arrival[a];       //update waitTime
        }
        
        for(a=0;a<jobs;a++){                      //Print wait time for each Task
            fprintf(outPut, "Waiting time T%d: %d\n", a+1, waitTime[a]);
        }
      
        //Calculate average time
        float average=0;                    //https://www.geeksforgeeks.org/g-fact-41-setting-decimal-precision-in-c/
        for(a=0;a<jobs;a++){
           average = average + waitTime[a];
        }
    	
        //Print average time taken
        fprintf(outPut, "Average Waiting time: %0.2f\n", average/jobs); //https://www.geeksforgeeks.org/g-fact-41-setting-decimal-precision-in-c/
        
    }