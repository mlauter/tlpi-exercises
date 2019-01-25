/* Exercise 15-4 */

/* eaccess.c

   checks permissions using the process’s effective user and group IDs

 */

#define _GNU_SOURCE
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int myEaccess(const char *path, int mode) {
    uid_t euid = geteuid();
    gid_t egid = getegid();
    struct stat stat_info;
    if (!stat(path, &stat_info)) {
        return -1;
    }

    if (uid_t == stat_info.st_uid) {
        // use the user perms
        stat_info.st_mode
    }

    if (gid_t == stat_info.st_gid) {
        // use the group perms
    }

    // use the other perms
}

int main(int argc, char *argv[]) {
    exit(0);
}
