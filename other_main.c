#include <stdio.h>
/** 
 * Most of this code came from a tutorial I followed on how to make a unix shell. 
 *  [link] (https://brennan.io/2015/01/16/write-a-shell-in-kc)
 *
 *
 * Basic loop of a shell
 *
 * Read -> the commands from standard input ( stdin ) 
 * Parse ->  separate the command string into a program and arguments 
 * Execute -> run parsed command
 */

/** This function will take a line of input 
 * from the user. However, the memory allocated may be exceeded when the user 
 * enters more input than the shell expects. To work around this, the same block of memory should 
 * be reallocated with the proper size of memory 
 */


#define LSH_RL_BUFSIZE 1024 

/** I would like to note that I am not a fan of this implementation. 
 * it does shorten the code and saves time. Yet I believe that it abstracts too much 
 * from the next person who needs to use this code. I'm not a fan of complexity, but 
 * I believe that the traditional approach should be fully understood before using this 
 * new addition to the C language 
 */
char *lsh_read_line(void){
        char *line = NULL;
        ssize_t buf = 0; /** getline() -> will allocate a buffer for the input */

        if(getline(&line, *bufsize, stdin) == -1 ){
                if(feof(stdin)){
                        exit(EXIT_SUCCESS); /** When an EOF is detected */
                } else{
                        perror("readline");
                        exit(EXIT_FAILURE);
                }
                
        }

        return line;

}
void lsh_loop(void) {
        char *line;
        char **args;
        char status;

      /** using a do-while loop allows us to check the stauts variable to check 
       * what state the shell is in , as a do-while loop will always execute at least once 
       */
        do {
                printf("> " ) ;
                line = lsh_read_line();        // Read the commands from stdin
                args = lsh_split_line(line);  // Parse the commands & arguments 
                status = lsh_execute(args);  // Execute the parsed commands 
               // === free up memory from arguments and any lines ===  
                free(line);
                free(args);

        }while(status) ;
}



int main(int argc, char **argv ) { 

        // this script is just a simple shell in C 
        // this is the usual life cycle of a shell 
        // 1. initialize  ( config files which change the behavior of the shell )
        // 2. interpret ( reading commands from stdin )
        // 3. terminate ( free up any memory , processes and then exit the shell)
        //
        // For this shell there won't be any config files ( yet ) or any shutdown command ( yet ) 
        // just going to call the looping function and terminate the shell 
        
        lsh_loop();
        return EXIT_SUCESS;
}


