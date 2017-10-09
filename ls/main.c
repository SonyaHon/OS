#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

// Terminal colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char **argv) {
    DIR *dp;
    struct dirent *ep;

    char* dir_name = "./"; 
    if(argc > 1) {
        dir_name = argv[1];
    }

    if((dp = opendir(dir_name)) == NULL) {
        perror("Error");
        (void)exit(1);
    }

    while( (ep = readdir(dp)))  {
        switch (ep->d_type) {
            case DT_DIR: { // Directory
                printf("%s%s%s\n", ANSI_COLOR_BLUE, ep->d_name, ANSI_COLOR_RESET);
                break;
            }
            case DT_BLK: { // Block
                printf("%s%s%s\n", ANSI_COLOR_GREEN, ep->d_name, ANSI_COLOR_RESET);
                break;
            }
            case DT_CHR: { // Char device
                printf("%s%s%s\n", ANSI_COLOR_RED, ep->d_name, ANSI_COLOR_RESET);
                break;
            }
            case DT_FIFO: { // Named pipe
                printf("%s%s%s\n", ANSI_COLOR_YELLOW, ep->d_name, ANSI_COLOR_RESET);
                break;
            }
            case DT_LNK: { // Link
                printf("%s%s%s\n", ANSI_COLOR_CYAN, ep->d_name, ANSI_COLOR_RESET);
                break;
            }
            case DT_REG: { // Reg file
                printf("%s\n", ep->d_name);
                break;
            }
            case DT_SOCK: { // Socket
                printf("%s%s%s\n", ANSI_COLOR_MAGENTA, ep->d_name, ANSI_COLOR_RESET);
                break;
            }
            case DT_UNKNOWN: { // Uknown file
                printf("%s\n", ep->d_name);
                break;
            }
        }
    }
    (void)closedir(dp);

    return 0;
}