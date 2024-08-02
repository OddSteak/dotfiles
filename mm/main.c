#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define MAX_RUN_CMD_LENGTH 1024

struct timespec lastmoddedtimes = {.tv_sec = 0, .tv_nsec = 0};
char *lastmoddedpath;
char *lastmoddeddir;
char *lastmoddedname;

void rec_dir(char *dir);
void write_makefile(char *path);
void makefile(char *dir, char *stripped_name, int argc, char **argv);
void stripname(char *name, char *buf);

int main(int ac, char **av) {
  rec_dir(getcwd(NULL, 50));

  char strippedname[strlen(lastmoddedname) - 2 + 1];
  stripname(lastmoddedname, strippedname);
  makefile(lastmoddeddir, strippedname, ac, av);
  return 0;
}

void rec_dir(char *dir) {
  DIR *dstream = opendir(dir);

  if (dstream == NULL) {
    return;
  }

  struct dirent *entry;

  while (entry = readdir(dstream), entry) {
    if (!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) {
      continue;
    }

    if (!strcmp(entry->d_name, "builds") || !strcmp(entry->d_name, ".git"))
      continue;

    if (entry->d_type == DT_REG || entry->d_type == DT_LNK) {
      if (strcmp(&(entry->d_name[strlen(entry->d_name) - 2]), ".c")) {
        continue;
      }

      char path[strlen(dir) + strlen(entry->d_name) + 2];
      strcat(strcat(strcpy(path, dir), "/"), entry->d_name);

      struct stat statbuf;
      stat(path, &statbuf);

      if (statbuf.st_mtim.tv_sec > lastmoddedtimes.tv_sec ||
          (statbuf.st_mtim.tv_sec == lastmoddedtimes.tv_sec &&
           statbuf.st_mtim.tv_nsec > lastmoddedtimes.tv_nsec)) {
        lastmoddedtimes = statbuf.st_mtim;

        free(lastmoddedpath);
        lastmoddedpath = (char *)malloc((strlen(path) + 1));
        strcpy(lastmoddedpath, path);

        free(lastmoddeddir);
        lastmoddeddir = (char *)malloc(strlen(dir) + 1);
        strcpy(lastmoddeddir, dir);

        free(lastmoddedname);
        lastmoddedname = (char *)malloc(strlen(entry->d_name) + 1);
        strcpy(lastmoddedname, entry->d_name);
      }

      continue;

    } else if (entry->d_type == DT_DIR) {
      char path[strlen(dir) + strlen(entry->d_name) + 2];

      strcat(strcat(strcpy(path, dir), "/"), entry->d_name);

      rec_dir(path);
    }
  }

  closedir(dstream);
}

void stripname(char *name, char *buf) {
  if (name[strlen(name) - 1] != 'c' && name[strlen(name) - 2] != '.') {
    exit(1);
  }

  for (int i = 0; i < (int)strlen(name) - 2 + 1; i++) {
    if (i == (int)strlen(name) - 2)
      buf[i] = 0;
    else
      buf[i] = name[i];
  }
}

void makefile(char *dir, char *stripped_name, int ac, char **av) {
  chdir(dir);

  char makepath[strlen(dir) + 10];

  strcat(strcat(strcpy(makepath, dir), "/"), "Makefile");

  if (access(makepath, F_OK)) {
    mkdir("builds", 0755);
    write_makefile(makepath);
  }

  char makecmd[strlen(stripped_name) + 6];
  strcat(strcpy(makecmd, "make "), stripped_name);

  system(makecmd);

  char run_cmd[MAX_RUN_CMD_LENGTH];
  strcat(strcpy(run_cmd, "./builds/"), stripped_name);

  if (access(run_cmd, F_OK)) {
    return;
  }

  if (ac > 1) {
    for (int i = 1; i < ac; i++) {
      if ((strlen(run_cmd) + strlen(av[i]) + 2) >= MAX_RUN_CMD_LENGTH) {
        fprintf(stderr, "mm ERROR: arguments too big\n");
        exit(EXIT_FAILURE);
      }
      strcat(strcat(run_cmd, " "), av[i]);
    }
  }

  system(run_cmd);
}

void write_makefile(char *path) {
  printf("Makefile not found, writing default\n");

  char *flags = "CC=gcc\nCFLAGS=-Wall -W -pedantic -ansi -std=c11\n\n";
  char *target = "%: %.c\n\t$(CC) $(CFLAGS) -o ";
  char *build_path = "builds/$@ $<";

  FILE *mkfile = fopen(path, "w");

  fputs(flags, mkfile);
  fputs(target, mkfile);
  fputs(build_path, mkfile);

  fclose(mkfile);
}
