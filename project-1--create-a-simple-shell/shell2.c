#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_PATH 1024
#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = ">";
char delimiters[] = " \t\r\n";
extern char **environ;
pid_t pid;
void sighandler(int);
bool Background = true;


int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
    char cwd[MAX_PATH];
    char sY [100];
    
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    	
    while (true) {
      
        do{ 
            // Print the shell prompt.
            printf("%s", prompt);
            fflush(stdout);

            // Read input from stdin and store it in command_line. If there's an
            // error, exit immediately. (If you want to learn more about this line,
            // you can Google "man fgets")
        
            if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
                fprintf(stderr, "fgets error");
                exit(0);
            }
 
        }
        while(command_line[0] == 0x0A);  // while just ENTER pressed

      
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 
        
		 // 0. Modify the prompt to print the current working directory
                printf("%s> ", getcwd(cwd, sizeof(cwd))); // prints the current working direcotry behind the prompt.
                fflush(stdout); // cleards out the display buffer			  
                    
        // 1. Tokenize the command line input (split it on whitespace)

        arguments[0] = strtok(command_line, delimiters);        
        int i=0;
        while(arguments[i] != NULL)
        {
          arguments[++i] = strtok(NULL,delimiters);
        }
          arguments[i] == NULL;
        
// Tokenized [*]

      
        // 2. Implement Built-In Commands
        if (strcmp(arguments[0],"cd") == 0)
        {
         
          chdir(arguments[1]);
        } 
        else if (strcmp(arguments[0],"exit") == 0)
        {
          exit(0);
        }
        else if (strcmp(arguments[0],"env") == 0)
        {
          if (arguments[1] == NULL)
          {
            for (i = 0; environ[i] != NULL; i++)
            {
                printf("\n%s", environ[i]);
             }
            printf("\n");
          } 
          else
            {
              printf("%s\n",getenv(arguments[1]));
            }
        }
        else if (strcmp(arguments,"setenv"))
        {
            printf("%s\n", getenv(arguments[1]));
        }
        else if (strcmp(arguments[0],"echo") == 0)
        {
          i=1;
    
          while(arguments[i] != NULL){
            
            if(strchr(arguments[i],'$') != NULL){
              memmove(arguments[i], arguments[i]+1, strlen(arguments[i]));
              arguments[i] = getenv(arguments[i]);
            }
            printf("%s ",arguments[i]);
            i++; 
          }
          printf("\n");
        }
        else if ( (strcmp(arguments[0],"pwd") == 0))
        {
          printf("%s\n", getcwd(sY, 100)); 
        }
        
    
        // 3. Create a child process which will execute the command line input

          alarm(10);
          pid = fork();
          if (pid < 0) 
          {
            perror("Fork failed, no child created\n"); 
            exit(1);
          } else if (pid == 0) 
          {
            if (execvp(arguments[0], arguments) == -1)
                perror("Input not executable");
          } else 
          {
            if(!Background)  // if & was found on command line
              pid = wait(NULL);
               
            Background = false; // then we wait
          }
          break;
        
        // 4. The parent process should wait for the child to complete unless its a background process
      
      
        // Hints (put these into Google):
        // man fork
        // man execvp
        // man wait
        // man strtok
        // man environ
        // man signals
        
        // Extra Credit
        // man dup2
        // man open
        // man pipes
    }
    // This should never be reached.
    return -1;
}