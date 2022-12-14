#include  <stdio.h>
#include  <sys/types.h>
#include  <stdlib.h>


#define   MAX_COUNT  200

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{

     
     pid_t PID;
     pid_t PID2;
 
     PID = fork(); 

     if (PID > 0) 
          {
               PID2 = fork();
               if (PID2 > 0) 
                    {
                         ParentProcess();
                         exit(0);
                    }
               else if (PID2 == 0) 
               {
                    ChildProcess();
                    exit(0);
               }
          }
     else if (PID == 0)
          {
                ChildProcess();
                exit(0);
          }
      
   
  
}

void  ChildProcess(void)
{
     // established limits - Child Process
     int ItterationLim = 30;
     int SleepTime = 10;
     srandom(time(0));
     int randIteration = (random()% ItterationLim);         // sets the actual iteartion limit to somthing at or below 30.
     int randSleep = (random()% SleepTime);                 // sets the actual sleep time to somthing at or below 10  
     int SLeepNumber, i;                                   // A sleep and iterator variable.  
     
                                                            // running a for loop for the required print statements. 
     for (i = 1; i <= randIteration; i++)                   // " for i equals one, i is less than or equal to ranndom interation variable. incease i by one."
          {
              printf( "Child Pid: %d is going to sleep!\n", getpid() );
               SLeepNumber = sleep(randSleep);
               if (SLeepNumber == 0)
                         {
                          printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());      

                         }


          }
          exit(0);                                 // leaves the method...
}

void  ParentProcess(void)
{

          int childStat;
          int ChildPid_Terminated = wait(&childStat);

          
          printf("Child Pid: %d has completed\n", terminatedChildPid);
          printf(" Parent is done, Child exited with exit status %d \n", WEXITSTATUS(status));
            
}