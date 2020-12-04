#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <math.h>



void getAndPrintGroup(gid_t grpNum) {
  struct group *grp;

  grp = getgrgid(grpNum); 
  
  if (grp) {
    printf(" %s", grp->gr_name);
  } else {
    printf("No group name for %u found\n", grpNum);
  }
}

void getAndPrintUserName(uid_t uid) {

  struct passwd *pw = NULL;
  pw = getpwuid(uid);

  if (pw) {
    printf(" %s", pw->pw_name);
  } else {
    perror("Hmm not found???");
    printf("No name found for %u\n", uid);
  }
}

void inode_ls(){
    DIR *di;
    struct dirent* dir;
    ino_t inde;  
    struct stat f_stat;  
    int scan; 
    di = opendir("./");
    if (di== NULL){
        printf("no directory given\n");
        return;
    }
    while ((dir = readdir(di))!=  NULL){
        if((strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' ))
        {
        }
        else{
            printf("%s \n", dir -> d_name);
        }
        scan = stat(dir->d_name, &f_stat);  
        inde = f_stat.st_ino;
        printf("inode : %ld\n", inde);
        getAndPrintGroup(f_stat.st_gid);
        getAndPrintUserName(f_stat.st_uid) ;
        printf (" \n");
    }
    closedir(di);
}

void listall_ls(){
    const char * months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    DIR *di;
    struct dirent* dir;
    ino_t inde;  
    struct stat f_stat;  
    int scan; 
    di = opendir("./");
    if (di== NULL){
        printf("no directory given\n");
        return;
    }
    while ((dir = readdir(di))!=  NULL){
        scan = stat(dir->d_name, &f_stat); 
        // printf("File Permissions: \t");
        printf( (S_ISDIR(f_stat.st_mode)) ? "d" : "-");
        printf( (f_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (f_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (f_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (f_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (f_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (f_stat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (f_stat.st_mode & S_IROTH) ? "r" : "-");
        printf( (f_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (f_stat.st_mode & S_IXOTH) ? "x" : "-"); 
        printf(" %ld",f_stat.st_nlink);
        inde = f_stat.st_ino;
        ino_t convert  = floor(log10(abs(inde)))+1;    
        printf(" %ld", inde);
        if (convert < 7)
        {
          printf(" ");
        }
        getAndPrintGroup(f_stat.st_gid);
        getAndPrintUserName(f_stat.st_uid) ;
        printf(" %ld", f_stat.st_size);
        off_t convert2 =  floor(log10(abs(f_stat.st_size)))+1; 
        if (convert2 < 5 )
        {
          printf(" ");
        }
        if (convert2 < 4 )
        {
          printf(" ");
        }
        if (convert2 < 3 )
        {
          printf(" ");
        }
        struct timespec st_mtim;
        char day[20]; 
        char mon[20] ; 
        char year[20] ; 
        strftime(mon, 20, "%b %d %Y %H:%M  ", localtime(&(f_stat.st_ctime)));
        printf(" %s", mon);
        if((strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' ))
        {
        }
        else{
            printf( "%s", dir -> d_name);
        }
        printf (" \n");
    }
    closedir(di);
    return;
}

// void recursive_ls(char * dlabel , int ind ){
//   struc dirent *read;
//   DIR * d; 
//   //basecase = 
//   while(read = readdir(d)==NULL)
//   {
//     if (read){
      
//     }
//     else
//     {
//       recursive_ls(read, index + 2);
//     }
    
    
//   }
  
//   return;    
// }


// int main() {

//   struct group *grp;

//   getAndPrintGroup(1001);
//   getAndPrintGroup(514378);
//   getAndPrintGroup(103);
//   getAndPrintGroup(1000);
  
//   getAndPrintUserName(59894);
//   getAndPrintUserName(23524);
//   getAndPrintUserName(20746);
//   getAndPrintUserName(5970);
//   getAndPrintUserName(10485);

// 	return 0;

// }
