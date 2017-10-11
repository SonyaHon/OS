#ifndef _PRINT_C_
#define _PRINT_C_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

// helper functions
    
static void reverse(char * str, int len) {
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
static int intToStr(long x, char str[], int d) {
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}
static void ftoa(double n, char *res, int afterpoint) {
    int ipart = (int)n;
    
       // Extract floating part
       float fpart = n - (float)ipart;
    
       // convert integer part to string
       int i = intToStr(ipart, res, 0);
    
       // check for display option after point
       if (afterpoint != 0)
       {
           res[i] = '.';  // add dot
    
           // Get the value of fraction part upto given no.
           // of points after dot. The third parameter is needed
           // to handle cases like 233.007
           fpart = fpart * pow(10, afterpoint);
    
           intToStr((int)fpart, res + i + 1, afterpoint);
       }
}

int print_myf(int file, char * format, ...) {
    va_list args;
    va_start(args, format);
    bool wasLastArg = false;
    bool wasLastSlash = false;
    char* res = (char *) malloc(0);
    int length = 0;
    for(int i = 0; i < strlen(format); i++) {       
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
                case 'f': { // its float
                    double mrd = va_arg(args, double);
                    char mr[100];
                    ftoa(mrd, mr, 6);
                    length += strlen(mr);
                    res = (char *) realloc(res, length);
                    strcat(res, mr);
                    break;
                }
                case 'd': { // its decimal
                    long mri = va_arg(args, int);
                    char mr[100];
                    intToStr(mri, mr, 0);
                    length += strlen(mr);
                    res = (char *) realloc(res, length);
                    strcat(res, mr);
                    break;
                }
                default: {
                    write(2, "No such format style", strlen("No such format style") * sizeof(char));
                    exit(1);
                }
            }
        }
        else {
                res = (char *) realloc(res, ++length);
                strncat(res, &format[i], 1);
            }
    }
    write(file, res, strlen(res) * sizeof(char));
    free(res);
    return 0;
}

int print_my(const char* format, ...) {
    va_list args;
    va_start(args, format);
    bool wasLastArg = false;
    bool wasLastSlash = false;
    char* res = (char *) malloc(1);
    strcpy(res, "\0");
    int length = 1;
    for(int i = 0; i < strlen(format); i++) {       
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
                case 'f': { // its float
                    double mrd = va_arg(args, double);
                    char mr[100];
                    ftoa(mrd, mr, 6);
                    length += strlen(mr);
                    res = (char *) realloc(res, length);
                    strcat(res, mr);
                    break;
                }
                case 'd': { // its decimal
                    long mri = va_arg(args, int);
                    char mr[100];
                    intToStr(mri, mr, 0);
                    length += strlen(mr);
                    res = (char *) realloc(res, length);
                    strcat(res, mr);
                    break;
                }
                default: {
                    write(2, "No such format style", strlen("No such format style") * sizeof(char));
                    exit(1);
                }
            }
        }
        else {
                res = (char *) realloc(res, ++length);
                strncat(res, &format[i], 1);
            }
    }
    write(1, res, strlen(res) * sizeof(char));
    free(res);
    return 0;
}



#endif