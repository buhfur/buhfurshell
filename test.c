#include <stdio.h>
#include <string.h>

int main(){
        char str[80] = "This is a string here - in - my room - ";
        //token you are trying to parse out ?
        const char s[2] = "-" ; 
        char *token; // buffer to hold the parsed text? 

        token = strtok(str , s ) ; 

        while( token != NULL) {
                printf(" %s\n", token);

                token = strtok(NULL, s );
        }
}
