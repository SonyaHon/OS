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
    va_start(args, format);
    bool wasLastArg = false;
    wasLastSlash = false;

    char* res = (char *) malloc(0);
    int length = 0;
    for(int i = 0; i < strlen(format); i++) {   
        if(format[i] == '\\') {
            wasLastSlash = true;
            res = (char *) realloc(res, ++length);
            strncat(res, &format[i], 1);
        }
        else if(wasLastSlash) {
            wasLastSlash = false;
            res = (char *) realloc(res, ++length);
            strncat(res, &format[i], 1);
        }
        else {
            if(format[i] == '%') {
                wasLastArg = true;
            }
            else if(wasLastArg){
                wasLastArg = false;
                switch(format[i]) {
                    case 's': { // its char*
                        char * mr = va_arg(args, char*);
                        length += strlen(mr);
                        res = (char *) realloc(res, length);
                        strcat(res, mr);
                        break;
                    }
                    case 'd': { // its double
                        double mrd = va_arg(args, double);
                        break;
                    }
                    case 'i': {
                        long mri = va_arg(args, int);
                        break;
                    }
                    case 'l': {
                        long mrl = va_arg(args, long);
                        break;
                    }
                    default: {

                    }
                }
            }
            else {
                    res = (char *) realloc(res, ++length);
                    strncat(res, &format[i], 1);
                }
            }
        }
    printf("%s", res);
    free(res);
    return 0;
}

#endif