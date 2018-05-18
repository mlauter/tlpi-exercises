/* Exercise 4-1 */

/* mytee.c

   Reads standard input until end-of-file, write a copy of the input to standard output and to the file named in argv[1].
 */

#define _GNU_SOURCE
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> // feels like cheating but just using it for perror
#include <stdlib.h>

#ifndef BUF_SIZE        /* Allow "cc -D" to override definition <-- WHY?*/
#define BUF_SIZE 1024
#endif


static void usage(int exit_code) {
    printf("Usage: mytee [-a] FILE\n");
    exit(exit_code);
}

int main(int argc, char *argv[]) {
  int outputFd, openFlags;
  mode_t filePerms;
  int aflag = 0;
  char buf[BUF_SIZE + 1];
  ssize_t numRead;
  int c;

  while ((c = getopt(argc, argv, "ha")) != -1) {
    switch (c) {
      case 'h': usage(0); break;
      case 'a': aflag = 1; break;
    }
  }

  if (optind >= argc) {
    usage(1);
  }

  openFlags = O_CREAT | O_WRONLY;
  if (aflag == 1) {
    openFlags |= O_APPEND;
  } else {
    openFlags |= O_TRUNC;
  }
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
    S_IROTH | S_IWOTH;      /* rw-rw-rw- */
  outputFd = open(argv[optind], openFlags, filePerms);
  if (outputFd == -1) {
    perror("open");
    exit(1);
  }

  while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    buf[numRead] = '\0';
    // write to stdout
    printf("%s", buf);
    // write to output file (only up to numRead!)
    if (write(outputFd, buf, numRead) != numRead) {
      perror("write");
      exit(1);
    }
  }

  if (numRead == -1) {
    perror("read");
    exit(1);
  }

  // is this necessary?
  if (close(STDIN_FILENO) == -1) {
    perror("close stdin");
    exit(1);
  }
  if (close(outputFd) == -1) {
    perror("close output file");
    exit(1);
  }

  exit(0);
}
