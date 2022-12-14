/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

/****

COPY YOUR SIGNAL.C INTO THIS FILE

UPDATE YOUR MAKEFILE
*******/
int Alarm_Status = 0;
int num_of_alarms = 0;

time_t start;
time_t stop;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  sleep(2);
  Alarm_Status = 1;
  num_of_alarms++;
 
}
                                            // ADMIN: handler gtg; close

void handler2(int signum)                   // Excecutes prints on ctrl+c
{ //signal handler
  int ExecutionTime;
  stop = time(NULL);
  ExecutionTime = stop - start;  
  printf("##############\nNumber Of Alarms %d \n", num_of_alarms);
  printf("The Execution time was %d secconds\n##############\n",ExecutionTime);
}
                                            //ADMIN: handler2 is gtg; close

int main(int argc, char * argv[])           // copied and pasted from singnal.c
{
  signal(SIGALRM,handler);                  // SIGALRM 
  signal(SIGINT,handler2);                  //  SIGINT
  start = time(NULL);
  while(1)
  {
    Alarm_Status = 0;
    alarm(1);                                  // alarm is triggered for one seccond
    while(!Alarm_Status); 
    printf("Turing Was Right!\n");
  }
  return 0; //never reached
}
                                            //ADMIN: Main gtg; close