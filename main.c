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


/**
 *
 * WARNING : THIS CODE USES THE OLD METHOD OF RETRIEVING INPUT FROM THE USER INSTEAD OF USING
 * THE GNU C "getline()".
 *
 * I will include a version of the code with the getline() method as well .*/

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *lin){
        int bufsize = LSH_TOK_BUFSIZE, pos = 0 ; 
        char **tokens = malloc(bufsize * sizeof(char*));
        char *token;

        if(!tokens){
                fprintf(stderr, "lsh: allocation error \n");
                exit(EXIT_FAILURE);

        }
        token = strtok(line, LSH_TOK_DELIM);
        while(token != NULL) {
                tokens[pos] = token;
                pos++;
                if(pos >= bufsize){
                        bufsize += LSH_TOK_BUFSIZE; 
                        tokens = realloc(tokens, bufsize * sizeof(char*));

                        if(!tokens){
                                fprintf(stderr, "lsh: allocation error \n");
                                exit(EXIT_FAILURE);

                        }
                }
        }
}
#define LSH_RL_BUFSIZE 1024 
char *lsh_read_line(void){
        /** Allocate memory for the line of input. */
        /** TODO: Why does bufsize need to be allocated?  */
        int bufsize = LSH_RL_BUFSIZE; /** Local declaration of the size of the buffer used for storing input from the user */
        int pos = 0; /** Position of the character being read from the user.*/
        /** Allocate a space of memory for the user input in the shell. */
        char *buf = malloc(sizeof(char) * bufsize);  /** Pre-allocated buffer for user input */
        int c ; /** Variable used for reading characters from the user . */

        /** If the buffer for storing user input is not initialized, then the shell will throw an error. */
        if(!buf){
                fprintf(stderr, "lsh: MEMORY ALLOCATION ERROR\nBuffer needs to be allocated");
                exit(EXIT_FAILURE); /** Return the status code associated with an un-initialized buffer. */
        }

        /** Reminder: In this application, you store the character input from the user as an INTEGER , as EOF is 
         * a number, not a character.
         */
        while(1){
                /** Read a single character from the user. */
                c = getchar();

                /** If the shell reads EOF ( End Of File ) then the character will be converted into a NULL character.*/
                if(c == EOF || c == '\n'){
                        buf[pos] = '\0'; /** Replace the EOF or newline character with a null character and return. */
                        return buf; /** Return the buffer */
                } else{
                        buf[pos] = c ; /** Put the character input into the buffer memory */
                }

                /** Increment to the next space in memory */
                pos++;

                /** If the space is exceeded the allocated space of the buffer. then reallocate the memory.*/
               
                if(pos >= bufsize){
                        bufsize += LSH_RL_BUFSIZE;
                        buf = realloc(buf, bufsize);/** Give the buffer more space for user input .*/
                        
                        if(!buf){
                                fprintf(stderr, "lsh: MEMORY ALLOCATION ERROR\nBuffer needs to be allocated");
                                exit(EXIT_FAILURE); /** Return the status code associated with an un-initialized buffer. */
                        }
                } 
                

        }
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


