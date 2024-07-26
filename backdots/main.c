#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *TARGET = "/home/dell/jit/dotfiles";
char *TARGET_TEST = "/home/dell/target";

char *list_dir[] = {
    "/home/dell/.config/mpd",
    "/home/dell/.config/ncmpcpp",
    "/home/dell/.config/hypr",
    "/home/dell/.config/vimium.css",
    "/home/dell/.config/starship.toml",
    "/home/dell/.config/tmux",
    "/home/dell/bin",
    "/home/dell/.bashrc",
    "/home/dell/learndev/c/backdots",
    "/home/dell/learndev/c/splash",
};

char *list_test[] = {
  "/home/dell/dummy/mpd",
  "/home/dell/dummy/ncmpcpp",
  "/home/dell/dummy/here.txt",
  "/home/dell/dummy/hypr",
};

void backup();
void rec_dir(char *src, char *dst);
int copy_file(char *source_file, char *dst_file);

int main() { backup(); }

void backup() {
  for (long unsigned i = 0; i < sizeof(list_dir) / sizeof(list_dir[0]); i++) {
    int delim;

    for (int j = 0; *(list_dir[i] + j) != 0; j++) {
      if (*(list_dir[i] + j) == '/') {
        delim = j;
      }
    }

    char final_target[strlen(TARGET) + strlen(list_dir[i] + delim) + 1 + 1];

    strcat(strcpy(final_target, TARGET), list_dir[i] + delim);

    struct stat buf;
    stat(list_dir[i], &buf);

    if (S_ISREG(buf.st_mode)) {
      copy_file(list_dir[i], final_target);
    } else {
      rec_dir(list_dir[i], final_target);
    }
  }
}

void rec_dir(char *dir_src, char *dir_dst) {
  mkdir(dir_dst, 0755);
  DIR *dstream = opendir(dir_src);

  if (dstream == NULL) {
    return;
  }

  struct dirent *entry;

  while (entry = readdir(dstream), entry) {
    if (!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) {
      continue;
    }

    if (entry->d_type == DT_REG) {
      char source_file[strlen(dir_src) + 1 + strlen(entry->d_name) + 1 + 1];
      char dst_file[strlen(dir_dst) + 1 + strlen(entry->d_name) + 1 + 1];

      strcat(strcat(strcpy(source_file, dir_src), "/"), entry->d_name);
      strcat(strcat(strcpy(dst_file, dir_dst), "/"), entry->d_name);

      copy_file(source_file, dst_file);

    } else if (entry->d_type == DT_DIR) {
      char source_dir[strlen(dir_src) + 1 + strlen(entry->d_name) + 1 + 1];
      char dst_dir[strlen(dir_dst) + 1 + strlen(entry->d_name) + 1 + 1];

      strcat(strcat(strcpy(source_dir, dir_src), "/"), entry->d_name);
      strcat(strcat(strcpy(dst_dir, dir_dst), "/"), entry->d_name);

      if (!strcmp(source_dir, "/home/dell/.config/tmux/plugins"))
        continue;

      rec_dir(source_dir, dst_dir);
    }
  }

  closedir(dstream);
}

int copy_file(char *source_file, char *dst_file) {

  FILE *src_cp = fopen(source_file, "r");
  FILE *dst_cp = fopen(dst_file, "w");

  char buf_cp[50];

  while (fgets(buf_cp, 50, src_cp) != NULL) {
    fputs(buf_cp, dst_cp);
  };

  fclose(src_cp);
  fclose(dst_cp);

  return 0;
}
