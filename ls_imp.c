
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

#define D_LEN   30 // Length of the date  
#define U_LEN   40
#define G_LEN   40

void getGroup(char *grp_string, gid_t grpNum) {
  struct group *grp;

  grp = getgrgid(grpNum); 
  
  if (grp) {
   strcpy(grp_string, grp->gr_name);
  } else {
    printf("No group name for %u found\n", grpNum);
  }
}



void getUserName(char *usr_string, uid_t uid) {

  struct passwd *pw = NULL;
  pw = getpwuid(uid);

  if (pw) {
    // printf("The user ID %u -> %s\n", uid, pw->pw_name);
    strcpy(usr_string,pw->pw_name);
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


void print_l(char *dirToPrint){
  DIR *directory;

  
  struct dirent *dir;
  struct stat i_num;
  char permission[12];
  char * p_per = permission;
  int check = -6;
  char path[1024];
  
  // struct stat i_arr[100];
    // char localDir[400];
    // memset(localDir, 0, sizeof(localDir));
    // strncpy(localDir, dirToPrint, strlen(dirToPrint));
    // chdir(dirToPrint);
  
  directory = opendir(dirToPrint);
  if (directory) {
    while ((dir = readdir(directory)) != NULL) {
    
    sprintf(path,"%s/%s",dirToPrint,dir->d_name);

    check = stat(path, &i_num);

      if(check != 0){
        printf("BIG ERROR error: %s\n", strerror(errno));
        
      }
        char *dateString = (char *)malloc(sizeof(char) * D_LEN);
        char *Usr_string = (char *)malloc(sizeof(char)*U_LEN);
        char *Grp_string = (char *)malloc(sizeof(char)*G_LEN);

        getUserName(Usr_string, i_num.st_uid);
        getGroup(Grp_string,i_num.st_gid);

        change_date(dateString, &(i_num.st_mtime));

        if(S_ISDIR(i_num.st_mode )){
          permission[0] = 'd';
        }else{
          permission[0] = '-';
        }

      get_permissions(p_per, i_num.st_mode);


      if((dir ->d_type) == DT_DIR && (strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' )){
        continue;
      }else{
        printf("%s %3lu %s  %s  %9lu %s %s\n", permission, i_num.st_nlink, Usr_string,Grp_string, i_num.st_size, dateString, dir->d_name);
      }

      free(dateString);
      free(Usr_string);
      free(Grp_string);
         
    }


    closedir(directory);
  }else{
    printf("The directory is not valid\n");

  }
}

void print_i(char *dirToPrint){
  DIR *directory;
  
  struct dirent *dir;
  struct stat i_num;
  int check = -6;
  char path[1024];
  
  // struct stat i_arr[100];
  
  // chdir(dirToPrint);
  
  directory = opendir(dirToPrint);
  if (directory) {
    while ((dir = readdir(directory)) != NULL) {

    sprintf(path,"%s/%s",dirToPrint,dir->d_name);

    check = stat(path, &i_num);

    // check = stat(dir->d_name, &i_num);
    if(check != 0){
      printf("Error - recvfrom error: %s\n", strerror(errno));
    }

    if((dir ->d_type) == DT_DIR && (strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' )){
      continue;
    }else{
      printf("%-2ld  %s ", i_num.st_ino, dir->d_name);
    }




    }
    printf("\n");
  }

}

void print_ls(char *dirToPrint){
  DIR *directory;
  
  struct dirent *dir;
  struct stat i_num;
  int check = -6;
  char path[1024];


  
  // struct stat i_arr[100];
  // chdir(dirToPrint);
  
  directory = opendir(dirToPrint);
  if (directory) {
    while ((dir = readdir(directory)) != NULL) {

    if((dir ->d_type) == DT_DIR && (strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' )){
      continue;
    }else{
      printf(" %-5s ",dir->d_name);
    }



    }
    printf("\n");
  }


}

void print_r(){








}
// void 
int main(int argc, char *argv[]) {

  // char path[1024];
  //   sprintf(path,"%s/%s",dlabel,dir->d_name);
  //   scan = stat(path, &f_stat);


  print_i(argv[1]);

  // DIR *directory;
  
  // struct dirent *dir;
  // struct stat i_num;
  // int check = -6;
  
  // // struct stat i_arr[100];

  // for(int i = 0; i<argc; i++){
  //   printf("%s",argv[i]);
  //   printf("\n");
  // }

  
  // directory = opendir(argv[1]);
  // if (directory) {
  //   while ((dir = readdir(directory)) != NULL) {

  //   if(dir->d_type == DT_REG || dir->d_type == DT_DIR){
  //     printf(" %-5s ",dir->d_name);
  //   }    





  //   }
  //   printf("\n");
  // }

  // print_i(argv[1]);

  return(0);


}

