#include <stdio.h> // Don't use this for the actual exercise
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int opt_num_lines = 10;
char *filename;
int buf_size = 16;

static void parse_opts(int argc, char **argv) {
    int c;

    while ((c = getopt(argc, argv, "hn:")) != -1) {
        switch (c) {
            case 'h': printf("help\n"); break;
            case 'n': opt_num_lines = atoi(optarg); break;
        }
    }

    if (optind < argc) {
        filename = argv[optind];
    } else {
        printf("need a file\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    // It's so fine and yet so terrible to stand in front of a blank
    // canvas. - Paul Cezanne

    // compile with: gcc -Wall main.c -o main
    parse_opts(argc, argv);

    char buf[buf_size];
    int fd;
    off_t offset;
    int line_count = 0;
    int last_newline_pos;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Could not open file.\n");
    }

    while (line_count <= opt_num_lines) {
        offset = lseek(fd, -buf_size, SEEK_END);
        read(fd, buf, buf_size);

        for (int i = 0; i < buf_size; ++i) {
            if (buf[i] == '\n') {
                line_count++;
                last_newline_pos = i;
            }
        }
    }



    return EXIT_SUCCESS;
}
