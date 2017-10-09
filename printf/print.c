#ifndef _PRINT_C_
#define _PRINT_C_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

// To std_out
// int print_my(const char* data) {
//     int length = strlen(data);
//     if(write(1, data, length * sizeof(char)) != length) {
//         write(2, "Error\n", 6* sizeof(char));
//         return -1;
//     } 
//     return 0;
// }

//parse string and get %s, %d, %i from it
// %s - char*
// %d - double
// %i - int
// %f - float
// %l - long 
// \% - does not count

int print_my(const char* format, ...) {
    va_list args;
    int numOfArgs = 0;
    bool wasLastSlash = false;
    // parsse count
    for(int i = 0; i < strlen(format); i++) {
        if(format[i] == '\\') {
            wasLastSlash = true;
        }
        else if(wasLastSlash) {
            wasLastSlash = false;
        }
        else {
            if(format[i] == '%') {
                numOfArgs++;
            }
        }
    }
    va_start(args, numOfArgs);
    bool wasLastArg = false;
    wasLastSlash = false;
    
    for(int i = 0; i < strlen(format); i++) {
        
    }
    return 0;
}

#endif