#include "libnotify/notify.h"
#include <dirent.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

char* TARGET = "/home/dell/jit/dotfiles";
char* TARGET_TEST = "/home/dell/learndev/c/backdots/test/target";

char* list_dir[] = {
    "/home/dell/.config/pkglist.txt",
    "/home/dell/.config/mpd",
    "/home/dell/.config/ncmpcpp",
    "/home/dell/.config/hypr",
    "/home/dell/.config/waybar",
    "/home/dell/.config/vimium.css",
    "/home/dell/.config/starship.toml",
    "/home/dell/.config/kitty",
    "/home/dell/.config/tmux",
    "/home/dell/.config/wofi",
    "/home/dell/.config/fontconfig",
    "/home/dell/bin",
    "/home/dell/.bashrc",
    "/home/dell/learndev/c/backdots",
    "/home/dell/learndev/c/splash",
    "/home/dell/learndev/c/mm",
};

char* list_test[] = {
    "/home/dell/learndev/c/backdots/test/dummy/mpd",
    "/home/dell/learndev/c/backdots/test/dummy/ncmpcpp",
    "/home/dell/learndev/c/backdots/test/dummy/here.txt",
    "/home/dell/learndev/c/backdots/test/dummy/hypr",
};

bool is_cancelled = false;

void backup();
void rec_dir(char* dir_src, char* dir_dst);
int copy_file(char* source_file, char* dst_file);
NotifyNotification* warn(char* title, char* message, int timeout);
void log_date();
bool check_run();
void signal_handler(int signo);

int main(int argc, char** argv)
{
    signal(SIGINT, signal_handler);
    signal(SIGHUP, signal_handler);

    if (argc > 1 && !strcmp(argv[1], "daemon")) {
        printf("starting daemon\n");

        while (true) {
            if (!check_run()) {
                printf("already ran today\n");
                sleep(24 * 60 * 60);
            } else {
                printf("starting backup in 10 minutes\n");
                NotifyNotification* warnNotif = warn("backdots warning",
                    "Starting dotfiles backup in 10 min\n$(~/bin/canback.sh) "
                    "to cancel",
                    1000 * 60 * 5);
                sleep(10 * 60);

                if (is_cancelled) {

                    notify_notification_close(warnNotif, NULL);
                    warn("backdots", "backup cancelled", 1000 * 5);
                    printf("backup cancelled\n");
                    is_cancelled = false;
                    sleep(6 * 60 * 60);

                } else {

                    printf("backup starting...\n");
                    backup();
                    printf("backup complete\n");
                    log_date();
                    sleep(24 * 60 * 60);
                }
            }
        }

        return 0;
    }

    backup();
    return 0;
}

void backup()
{
    system("pacman -Qqe > /home/dell/.config/pkglist.txt");
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

void rec_dir(char* dir_src, char* dir_dst)
{
    mkdir(dir_dst, 0755);
    DIR* dstream = opendir(dir_src);

    if (dstream == NULL) {
        return;
    }

    struct dirent* entry;

    while (entry = readdir(dstream), entry) {
        if (!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) {
            continue;
        }

        if (entry->d_type == DT_REG) {
            char source_file[strlen(dir_src) + strlen(entry->d_name) + 1 + 1];
            char dst_file[strlen(dir_dst) + strlen(entry->d_name) + 1 + 1];

            strcat(strcat(strcpy(source_file, dir_src), "/"), entry->d_name);
            strcat(strcat(strcpy(dst_file, dir_dst), "/"), entry->d_name);

            copy_file(source_file, dst_file);

        } else if (entry->d_type == DT_DIR) {
            char source_dir[strlen(dir_src) + strlen(entry->d_name) + 1 + 1];
            char dst_dir[strlen(dir_dst) + strlen(entry->d_name) + 1 + 1];

            strcat(strcat(strcpy(source_dir, dir_src), "/"), entry->d_name);
            strcat(strcat(strcpy(dst_dir, dir_dst), "/"), entry->d_name);

            if (!strcmp(source_dir, "/home/dell/.config/tmux/plugins"))
                continue;

            rec_dir(source_dir, dst_dir);
        }
    }

    closedir(dstream);
}

int copy_file(char* source_file, char* dst_file)
{

    FILE* src_cp = fopen(source_file, "r");
    FILE* dst_cp = fopen(dst_file, "w");

    char buf_cp[50];

    while (fgets(buf_cp, 50, src_cp) != NULL) {
        fputs(buf_cp, dst_cp);
    };

    fclose(src_cp);
    fclose(dst_cp);

    return 0;
}

NotifyNotification* warn(char* title, char* message, int timeout)
{
    notify_init("backdots");

    NotifyNotification* notif;

    notif = notify_notification_new(title, message, NULL);

    notify_notification_set_urgency(notif, NOTIFY_URGENCY_LOW);

    notify_notification_set_timeout(notif, timeout);

    notify_notification_show(notif, NULL);

    notify_uninit();
    return notif;
}

void log_date()
{
    FILE* log_file = fopen("/home/dell/learndev/c/backdots/date.log", "w");

    struct tm* tm;
    time_t t = time(NULL);
    tm = localtime(&t);
    char date_now[11];

    strftime(date_now, 11, "%d-%m-%Y", tm);

    fputs(date_now, log_file);
    fclose(log_file);
}

bool check_run()
{
    FILE* log_file = fopen("/home/dell/learndev/c/backdots/date.log", "r");

    struct tm* tm;
    time_t t = time(NULL);
    tm = localtime(&t);
    char date_now[11];
    char date_then[11];

    strftime(date_now, 11, "%d-%m-%Y", tm);

    fgets(date_then, 11, log_file);
    fclose(log_file);

    return strcmp(date_then, date_now);
}

void signal_handler(int signo)
{
    if (signo == SIGHUP) {
        printf("received SIGHUP\n");
        is_cancelled = true;
    }

    if (signo == SIGINT) {
        printf("received SIGINT\n");
        exit(0);
    }
}
