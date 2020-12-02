
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

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
  
  directory = opendir(".");
  if (directory) {
    while ((directory = readdir(directory)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(directory);
  }else{
    printf("The directory is not valid\n");

  }

  return(0);


	// return 0;

}

