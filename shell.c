#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUFF_SIZE 100

void cmd_pwd(void){
  char *pwd = getcwd(NULL, 0);
  printf("%s\n", pwd ? pwd : "getcwd() error");
  if(pwd)free(pwd);
}

void cmd_cd(char* p_arg){ 
  if(chdir(p_arg) != 0){
    perror("cd failed, couldn't change directory");
  }
}

void cmd_mkdir(char* p_arg){ 
 if(mkdir(p_arg, 0755) == 0){
    printf("Directory created successfully\n");
 }else{
    perror("Error creating directory");
  }
}

void cmd_ls(char* p_arg){
   struct dirent* entry;
   DIR* dp = opendir(p_arg ? p_arg : ".");

   if(dp == NULL){
     perror("opendir");
     return;
   }

  while((entry = readdir(dp)) != NULL){
      printf("%s\n", entry -> d_name);
  }
  closedir(dp);
}

int main(int argc, char* argv[]){
 char *save_ptr;
 char buffer[BUFF_SIZE];
  while(true){
    printf("Enter command: \t");
    if(fgets(buffer, sizeof(buffer), stdin) != NULL){
        buffer[strcspn(buffer, "\n")] = '\0';
    }
    char* v_cmd = strtok_r(buffer, " ", &save_ptr);
    char* v_arg = strtok_r(NULL, " ", &save_ptr);
    if(v_cmd == NULL){
      continue;
    }
    char* p_cmd = strdup(v_cmd);
    char* p_arg = (v_arg != NULL)?strdup(v_arg):NULL;   
    if(strcmp(p_cmd, "pwd") == 0){
      printf("pwd active\n");
      cmd_pwd();
    }else if(strcmp(p_cmd, "ls") == 0){
      printf("ls active\n");
      if(p_arg == NULL){
        cmd_ls(NULL);
      }else{
        cmd_ls(p_arg);
      }
    }else if(strcmp(p_cmd, "mkdir") == 0){
      printf("mkdir active\n");
      (!p_arg)?printf("mkdir requires arguments!\n"):cmd_mkdir(p_arg);
    }else if(strcmp(p_cmd, "cd") == 0){
      printf("cd is active\n");
      (!p_arg)?printf("cd requires arument!\n"):cmd_cd(p_arg);
    }else if(strcmp(p_cmd, "clear") == 0){
       printf("\033[H\033[J");
    }else if(strcmp(p_cmd, "exit") == 0){
      printf("Exited...");
      break;
    }else{
        printf("Invalid command detected");
    }
    free(p_cmd);
    free(p_arg);
  }
  
  return 0;
}
