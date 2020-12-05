
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

void get_permissions(char *per_string, mode_t per){

  if(per & S_IRUSR){
    per_string[1] = 'r';
  }
  else{
   per_string[1] = '-'; 
  }

  if(per & S_IWUSR){
    per_string[2] = 'w';
  }
  else{
   per_string[2] = '-'; 
  }

  if(per & S_IXUSR){
    per_string[3] = 'x';
  }
  else{
   per_string[3] = '-'; 
  }
  
  if(per & S_IRGRP){
    per_string[4] = 'r';
  }
  else{
   per_string[4] = '-'; 
  }

  if(per & S_IWGRP){
    per_string[5] = 'w';
  }
  else{
   per_string[5] = '-'; 
  }

  if(per & S_IXGRP){
    per_string[6] = 'x';
  }
  else{
   per_string[6] = '-'; 
  }


  if(per & S_IROTH){
    per_string[7] = 'r';
  }
  else{
   per_string[7] = '-'; 
  }

  if(per & S_IWOTH){
    per_string[8] = 'w';
  }
  else{
   per_string[8] = '-'; 
  }


  if(per & S_IXOTH){
    per_string[9] = 'x';
  }
  else{
   per_string[9] = '-'; 
  }




}

int main() {

  DIR *directory;
  
  struct dirent *dir;
  struct stat i_num;
  int check = -6;
  char permission[12];
  char * p_per = permission;
  
  // struct stat i_arr[100];
  
  directory = opendir(".");
  if (directory) {
    while ((dir = readdir(directory)) != NULL) {

      printf("\n%s\n", dir->d_name);

      check = stat(dir->d_name, &i_num);
      // printf("this is the inode number: %li", i_num.st_ino);
      getAndPrintUserName(i_num.st_uid);
      getAndPrintGroup(i_num.st_gid);

       char *dateString = (char *)malloc(sizeof(char) * D_LEN);

       change_date(dateString, &(i_num.st_mtime));

       printf("%s", dateString);
       

       if(S_ISDIR(i_num.st_mode )){
         permission[0] = 'd';
       }else{
         permission[0] = '-';
       }
      
      get_permissions(p_per, i_num.st_mode);
      printf("\n%s\n", p_per);

      free(dateString);
      // free(permission);

      printf("\nThe number of hard links: %ld\n", i_num.st_nlink);      

      printf("\nthese is the size of the file: %ld\n", i_num.st_size);

      // printf("%s%c%s %3u %s  %s  %9llu %s %s%s\n", permission, )

      if(check != 0){
        printf("Error - recvfrom error: %s\n", strerror(errno));
      }
         
    }


    closedir(directory);
  }else{
    printf("The directory is not valid\n");

  }
  printf("\n");



  return(0);


}

