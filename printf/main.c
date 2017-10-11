#include "./print.c"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char ** argv) {
    
    int f = open("res_file", O_CREAT | O_RDWR, 0666);
    print_myf(f, "%s", "Hello world\n");
    close(f);

    print_my("This is string - %s, this is decimal %d, this is float %f\n", "Hello World", 12, 120.001);

    return 0;
}