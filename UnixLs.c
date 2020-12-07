#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "infodemo.h"

//ls simulation//


int count;

int main(int argc,  char *argv[])
{
    
        // 
        // printf("current : %s\n", argv[1]);

            if (argc == 1)
            {         
                printf("run the program at the standard option\n");
                    printf("this is the file path : ./\n");
                standardls("./"); 
                return 1;
            }
            else
            {
                
                if(strcmp(argv[1], "-l" ) ==0) {
                    printf("run the program at the l option\n");
                        printf("this is the file path :%s\n",argv[2] );
                    listall_ls(argv[2]);
                }    
                if(strcmp(argv[1], "-R" ) ==0) {
                    printf("run the program at the R option\n");
                        printf("this is the file path :%s\n", argv[2]);
                    recursive_ls(argv[2], 0);
                }   
                if(strcmp(argv[1], "-i" ) ==0) {
                    printf("run the program at the i option\n");
                        printf("this is the file path :%s\n", argv[2]);
                    inode_ls(argv[2]);
                }  
                else
                {
                printf("run the program at the standard option\n");
                    printf("this is the file path : ./\n");
                standardls(argv[1]); 
                }
                
            }
            


                                             
    
    //     if (int argv[1] == "i" || int argv[1] =="R" ||int argv[1]=="l")
    //     {
    //         printf("have to do the command here");
    //         count ++;
    //     }

    // if (count)
    // {
    //     for (int i = 0; i < count; i++)
    //     {
    //         if(argv[1] =="-i") {
    //             printf("run the program at the i option")
    //         }
    //         if(argv[1] =="-l") {
    //             printf("run the program at the l option");
    //             char* 
    //         }
    //         if(argv[1] =="-R") {
    //             printf("run the program at the R option")
    //         }          
    //     }
    // }
    // else{
        //    DIR * d;
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

