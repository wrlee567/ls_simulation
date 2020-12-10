
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

void print_li(char *dirToPrint){
  DIR *directory;

  
  struct dirent *dir;
  struct stat i_num;
  char permission[12];
  char * p_per = permission;
  int check = -6;
  char path[1024];
  
  
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
        printf("%ld  %s %3lu %s  %s  %9lu %s %s\n", i_num.st_ino,permission, i_num.st_nlink, Usr_string,Grp_string, i_num.st_size, dateString, dir->d_name);
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

    check = lstat(path, &i_num);

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

void do_recur(char * dirToPrint){
DIR * directory;
struct dirent *dir;
struct stat i_num;
int check = -6;
char path_1 [1024];
char path_2 [1024];


directory = opendir(dirToPrint);
  printf("\n");
  printf("\n");
  puts(dirToPrint);

  if(directory == NULL){
    return ;
  }

  print_ls(dirToPrint);
  rewinddir(directory);
  while ((dir = readdir(directory)) != NULL){

    if((strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' )){
      continue;
    }else{
      sprintf(path_1,"%s/%s",dirToPrint,dir->d_name);
      check = lstat(path_1, &i_num);

    if(check != 0){
      printf("Error - recvfrom error: %s\n", strerror(errno));
    }

      if((i_num.st_mode & S_IFMT) == S_IFDIR){
        strcpy(path_2,dirToPrint);
        strcat(path_2, "/");
        strcat(path_2, dir->d_name);
        do_recur(path_2);

      }

    }


  }
  printf("\n");

}


void do_recur_i(char * dirToPrint){
DIR * directory;
struct dirent *dir;
struct stat i_num;
int check = -6;
char path_1 [1024];
char path_2 [1024];


directory = opendir(dirToPrint);
  printf("\n");
  printf("\n");
  puts(dirToPrint);

  if(directory == NULL){
    return ;
  }

  print_i(dirToPrint);
  rewinddir(directory);
  while ((dir = readdir(directory)) != NULL){

    if((strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' )){
      continue;
    }else{
      sprintf(path_1,"%s/%s",dirToPrint,dir->d_name);
      check = lstat(path_1, &i_num);

    if(check != 0){
      printf("Error - recvfrom error: %s\n", strerror(errno));
    }

      if((i_num.st_mode & S_IFMT) == S_IFDIR){
        strcpy(path_2,dirToPrint);
        strcat(path_2, "/");
        strcat(path_2, dir->d_name);
        do_recur_i(path_2);

      }

    }


  }
  printf("\n");

}


void do_recur_l(char * dirToPrint){
DIR * directory;
struct dirent *dir;
struct stat i_num;
int check = -6;
char path_1 [1024];
char path_2 [1024];


directory = opendir(dirToPrint);
  printf("\n");
  printf("\n");
  puts(dirToPrint);

  if(directory == NULL){
    return ;
  }

  print_l(dirToPrint);
  rewinddir(directory);
  while ((dir = readdir(directory)) != NULL){

    if((strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' )){
      continue;
    }else{
      sprintf(path_1,"%s/%s",dirToPrint,dir->d_name);
      check = lstat(path_1, &i_num);

    if(check != 0){
      printf("Error - recvfrom error: %s\n", strerror(errno));
    }

      if((i_num.st_mode & S_IFMT) == S_IFDIR){
        strcpy(path_2,dirToPrint);
        strcat(path_2, "/");
        strcat(path_2, dir->d_name);
        do_recur_l(path_2);

      }

    }


  }
  printf("\n");

}

void do_recur_il(char * dirToPrint){
DIR * directory;
struct dirent *dir;
struct stat i_num;
int check = -6;
char path_1 [1024];
char path_2 [1024];


directory = opendir(dirToPrint);
  printf("\n");
  printf("\n");
  puts(dirToPrint);

  if(directory == NULL){
    return ;
  }

  print_li(dirToPrint);
  rewinddir(directory);
  while ((dir = readdir(directory)) != NULL){

    if((strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' )){
      continue;
    }else{
      sprintf(path_1,"%s/%s",dirToPrint,dir->d_name);
      check = lstat(path_1, &i_num);

    if(check != 0){
      printf("Error - recvfrom error: %s\n", strerror(errno));
    }

      if((i_num.st_mode & S_IFMT) == S_IFDIR){
        strcpy(path_2,dirToPrint);
        strcat(path_2, "/");
        strcat(path_2, dir->d_name);
        do_recur_il(path_2);

      }

    }


  }
  printf("\n");

}

void track_arg(char * arg, int * arr){
int i = 0;

  for(i = 0; i< strlen(arg); i++){
    if(arg[i] == 'l'){
      arr[0] = 1;
    }

    if(arg[i] == 'i'){
      arr[1] = 1;
    }

    if(arg[i] == 'R'){
      arr[2] = 1;
    }


  }



}

int main(int argc, char *argv[]) {

  int arg_ind = 1;

  int j = 0;

  int track[3];
  int * p = track;

  char *curr = argv[arg_ind];

  while (arg_ind < argc && curr[0] == '-') {
        track_arg(argv[arg_ind], p);
        curr = argv[++arg_ind];
    }

  if(argc == 1){
    print_ls("./");
    return 1;
  }else{

    if(track[0] == 1 && track[1] != 1 && track[2] != 1) {
      if (argc <= arg_ind)
      {
          printf("this is the file path : cur\n");
          print_l("./");
          return 1;
      }
      print_l(argv[argc -1]);
      return 1;
  }    
  if(track[2] == 1 && track[0] != 1 && track[1] != 1) {
      if (argc<= arg_ind)
      {
          do_recur("./");
          return 1;
      }
      do_recur(argv[argc -1]);
      return 1;
  }   
  if(track[1] == 1 && track[2] != 1 && track[0] != 1) {
      if (argc<= arg_ind){
          print_i("./");
          return 1;
      }
      print_i(argv[argc -1]);
      return 1;
  }  
  if(track[2] == 1 && track[1] == 1 && track[0] != 1) {  
      if (argc<= arg_ind){
          do_recur_i("./");
          return 1;
      }
      do_recur_i(argv[argc -1]);
      return 1;
  }  
  if(track[0] == 1 && track[1] == 1 && track[2] != 1) {
    printf("in here");
      if (argc<= arg_ind){
          print_li("./");
          return 1;
      }
      print_li(argv[argc -1]);
      return 1;
  }  
  if((track[2] == 1) && (track[0] == 1) &&(track[1] != 1)) {
      if (argc<= arg_ind){
          do_recur_l("./");
          return 1;
      }
      do_recur_l(argv[argc -1]);
      return 1;
  } 
  if(track[0] == 1 && track[1] == 1 && track[2] == 1) {
      if (argc<= arg_ind){
          do_recur_il("./");
          return 1;
      }
      do_recur_il(argv[argc -1]);
      return 1;
  } 

  else{
    print_ls(argv[1]);
  }


  }




  return(0);


}

 