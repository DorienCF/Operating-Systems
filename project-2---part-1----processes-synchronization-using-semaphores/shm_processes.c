#include <fcntl.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int BankAccount = 0;

void ChildProcess(int[], int);
void MumProcess(int[]);

sem_t *mutex;

int main(int argc, char *argv[]) 
{
  int ShmID;
  int *ShmPTR;
  pid_t pid;
  int status;
  int localBalance;
  int amount ;
  int even_or_odd;
  srandom(getpid());

  printf("Process has received a shared memory of 1 integer...\n");



  ShmPTR[BankAccount] = 0;  // global variable

  printf("Process has attached the shared memory...\n");
  pid = fork();

  if (pid < 0) {
    printf("Fork Error, try agian...\n");
    exit(1);
  } 
  else if (pid == 0)
  {
    ChildProcess(ShmPTR, 1);
    exit(0);
  } 
  else 
  {
     int localBalance;
    while (1) {
      
      sleep(random() % 6); // sleep for 0-5 secconds
      sem_wait(mutex);
      printf("Dear Old Dad: Attempting to Check Balance\n");
      localBalance = ShmPTR[BankAccount];
      even_or_odd = random(); 
      if (even_or_odd % 2 == 0)
        {
          if (localBalance < 100)
            {
              amount  = random() % 101; // random deposit between 0-100
              if (amount  % 2 == 0) // random number is even-> 
                {
                  localBalance += amount ;
                  printf("Dear old Dad: Deposits $%d / Balance = $%d\n", // If the random number is even: Deposit the amount into the BankAccount, then call printf("Dear old Dad: Deposits $%d / Balance = $%d\n", amount, localBalance);
                  amount , localBalance);
                }
              else
                {
                printf("Dear old Dad: Doesn't have any money to give\n");// Number is odd| printf("Dear old Dad: Doesn't have any money to give\n");
                }
              } 
          else
            {
              printf("Dear old Dad: Thinks student has enough Cash ($%d)\n", localBalance);
            }
        }  
     else
        {
        printf("Dear old Dad: Last Checking Balance = $%d\n", localBalance);
        }
      ShmPTR[BankAccount] = localBalance; //Copy contents of non-shared local variable localBalance bank into the shared variable BankAccount
      sem_post(mutex);
    }
    wait(&status);
    printf("Process has detected the completion of its child...\n");
    shmdt((void *)ShmPTR);
    printf("Process has detached its shared memory...\n");
    shmctl(ShmID, IPC_RMID, NULL);
    printf("Process has removed its shared memory...\n");
    printf("Process exits...\n");
    exit(0);
  }
}

void ChildProcess(int SharedMem[], int nth) {
  int localBalance;
  int Withdraw;
  int even_or_odd;
  srandom(getpid());
  while (1) {
    sleep(random() % 6); // Sleep some random amount of time between 0 - 5 seconds
    sem_wait(mutex);
    printf("Poor Student #%d: Attempting to Check Balance\n", nth); // After waking up, call printf("Poor Student: Attempting to Check Balance\n");
    localBalance = SharedMem[BankAccount]; // COPYING LOCAL BALANCE FROM GLOBAL BALANCE
    even_or_odd = random(); 
    if (even_or_odd % 2 == 0) // even or odd
    {
      Withdraw = random() % 51;  // Randomly generate another number (need) that the Student needs between   0− 50, 
      printf("Poor Student needs $%d\n", Withdraw);
      if (Withdraw <= localBalance)
        {
        localBalance -= Withdraw;
        printf("Poor Student #%d: Withdraws $%d / Balance = $%d\n", nth, Withdraw, localBalance);
        } 
      else 
        {
          printf("Poor Student #%d: Not Enough Cash ($%d)\n", nth, localBalance);
        }
    }
    else 
    {
      printf("Poor Student #%d: Last Checking Balance = $%d\n", nth,localBalance);
    }
    SharedMem[BankAccount] = localBalance;
    sem_post(mutex);
  }
}