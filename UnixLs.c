#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "infodemo.h"

//ls simulation//


int count;

int main(int argc, char const *argv[])
{
        listall_ls();
        // for (int i = 4; i < 9; i= i+2)
    // {
    //     if (int argv[i] == "i" || int argv[i] =="R" ||int argv[i]=="l")
    //     {
    //         printf("have to do the command here");
    //         count ++;
    //     }

    

    // }
    // if (count)
    // {
    //     for (int i = 0; i < count; i++)
    //     {
    //         if(argv[i] =="i") {
    //             printf("run the program at the i option")
    //         }
            // if(argv[i] =="l") {
            //     printf("run the program at the l option");
            //     char* 
            // }
    //         if(argv[i] =="R") {
    //             printf("run the program at the R option")
    //         }          
    //     }
        
    // }
    // else{
            // DIR * d;
        // struct dirent* dirr;
        // d = opendir(argv[1]);
        // if (d== NULL){
        //     printf("no directory given\n");
        //     return 0;
        // }
        // else{
        //     printf("dir exists\n");
        // }
        // while ((dirr = readdir(d))!=  NULL){
        //     if((strcmp(dirr->d_name,".")==0 || strcmp(dirr->d_name,"..")==0 || (*dirr->d_name) == '.' ))
        //     {
        //     }
        //     else{
        //         printf("%s \n", dirr -> d_name);
        //     }
        // }
        // closedir(d);
    // }

    
    return 0;
}

