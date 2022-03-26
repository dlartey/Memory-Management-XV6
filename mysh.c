// References: https://www.youtube.com/watch?v=z4LEuxMGGs8
// References: https://aticleworld.com/implement-strtok-function-in-c/

#include "kernel/types.h"
#include "user/user.h"

void _split(char *buff, char *cmd[]){
    int arg_count = 0;
    char *temp = buff;
    char *temp2;

    while (arg_count == 0){
        buff++;
        if (*buff == ' '){
            temp2 = buff+1;
            *buff = '\0';
            cmd[arg_count] = temp; // set the cmd to contain
            //printf("arg: %d, is:%s\n",arg_count,temp);
            arg_count++;
            // what the word has so far
            if (*temp2 != '\0'){
                cmd[arg_count] = temp2;
                //printf("temp2 = %s\n",temp2);
                arg_count++;
            }
            
        }
        //printf("index = %d\n",index);
        //printf("buff = %s\n",buff);
    }
    cmd[arg_count] = 0;
    printf("arg_count = %d\n",arg_count);
    
    /*
    for (int i = 0; i < arg_count; i++){
         printf("cmd[%d] = %s\n",i,cmd[i]);
    }
    */
    exec(cmd[0],cmd);
}

int main(int argc, char *argv[]){
    char buff[256];
    char *cmd[20]; // Array of pointers that holds the parameter list
    for (;;){ 
    printf(">>>");
    memset(buff,0,256);
    gets(buff, 256); // Gets user input from the command line
   

    *strchr(buff, '\n') = '\0';
    if (buff[0] == 'c' && buff[1] == 'd'){
            buff[strlen(buff)-1] = 0;
            chdir(buff);
        }
    if (fork()){

        wait(0);
        // You can't do chdir in child as it will only change the directory in the child process
        
    // to call exec split the string into 1st half and 2nd half (look for the space)
    }else{
        _split(buff,cmd);
        /// This is the child process
        // check whether there is a pipe
        // check whether there is a > or <
        // check whether it is a normal command and execute it normally
    }


    }
   
    exit(0); // exit the program
}