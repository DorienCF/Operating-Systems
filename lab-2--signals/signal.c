/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
//#include "timer.c"

int AlarmStatus = 0;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  sleep(1);                             // goes to sleep for a ssccond  
  AlarmStatus = 1;
}
// ADMIN: handler gtg; close

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler);//register handler to handle SIGALRM
  alarm(1);                           // alarm is trigered for one seccond
  while(!AlarmStatus); 
  printf("Turing was right!\n");      // after the handeler is called "Turing is right" 
  
  return 0; //never reached
}         
  //ADMIN: Main gtg; close