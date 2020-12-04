
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
 #include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define D_LEN    30 // Length of the date  

void getAndPrintGroup(gid_t grpNum) {
  struct group *grp;

  grp = getgrgid(grpNum); 
  
  if (grp) {
    printf("The group ID %u -> %s\n", grpNum, grp->gr_name);
  } else {
    printf("No group name for %u found\n", grpNum);
  }
}



void getAndPrintUserName(uid_t uid) {

  struct passwd *pw = NULL;
  pw = getpwuid(uid);

  if (pw) {
    printf("The user ID %u -> %s\n", uid, pw->pw_name);
  } else {
    perror("Hmm not found???");
    printf("No name found for %u\n", uid);
  }
}

void change_date(char *string, time_t *time){

  strftime(string, D_LEN, "%b %e %Y %R", localtime(time));

}


int main() {

  struct group *grp;

  // getAndPrintGroup(1001);
  // getAndPrintGroup(514378);
  // getAndPrintGroup(103);
  // getAndPrintGroup(1000);
  
  // getAndPrintUserName(59894);
  // getAndPrintUserName(23524);
  // getAndPrintUserName(20746);
  // getAndPrintUserName(5970);
  // getAndPrintUserName(10485);

  DIR *directory;
  
  struct dirent *dir;
  struct stat i_num;
  int check = -6;
  
  // struct stat i_arr[100];
  
  directory = opendir(".");
  if (directory) {
    while ((dir = readdir(directory)) != NULL) {

      printf("\n%s\n", dir->d_name);

      check = stat(dir->d_name, &i_num);
      // printf("this is the inode number: %li", i_num.st_ino);
      getAndPrintUserName(i_num.st_uid);
      getAndPrintGroup(i_num.st_gid);
      //  printf("Last file modification:   %s", ctime(&i_num.st_mtime));

       char *dateString = (char *)malloc(sizeof(char) * D_LEN);

       change_date(dateString, &(i_num.st_mtime));

       printf("%s", dateString);
//i_num.st_ino
    

      if(check != 0){
        printf("Error - recvfrom error: %s\n", strerror(errno));
      }
      // getAndPrintUserName(i_num->st_ino);

    
    }
    closedir(directory);
  }else{
    printf("The directory is not valid\n");

  }
  printf("\n");


  // printf("this is the inode number: %li", i_num->st_ino);
  return(0);


	// return 0;

}

