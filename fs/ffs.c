#ifndef FFS_C_
#define FFS_C_

#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// Strcts n defines
// FS Header
typedef struct {
    char fs_check_code[7]; // ffs_322
    long amount_of_files; // initial - 0
    long size_all;
    off_t last_file_offset; 
} ffs_header;


// File header
typedef struct {
    char* file_name;
    int file_size;
    off_t next_file_offset;
} ffs_file_header;


#define BASE_FILE_NAME "ffs_file"

char * current_file_system;

// Create file system
void ffs_create_file_system() {
    int f = open(BASE_FILE_NAME, O_CREAT | O_RDWR, 0666);
    ffs_header header;
    header.fs_check_code[0] = 'f';
    header.fs_check_code[1] = 'f';
    header.fs_check_code[2] = 's';
    header.fs_check_code[3] = '_';
    header.fs_check_code[4] = '3';
    header.fs_check_code[5] = '2';
    header.fs_check_code[6] = '2';
    header.amount_of_files = 0;
    header.size_all = sizeof(ffs_header);
    header.last_file_offset = sizeof(ffs_header);
    write(f, &header, sizeof(header));
    close(f);
}
// Create file system in specified (created) file
void ffs_create_file_system_from_file(int file) {  
    ffs_header header;
    header.fs_check_code[0] = 'f';
    header.fs_check_code[1] = 'f';
    header.fs_check_code[2] = 's';
    header.fs_check_code[3] = '_';
    header.fs_check_code[4] = '3';
    header.fs_check_code[5] = '2';
    header.fs_check_code[6] = '2';
    header.amount_of_files = 0;
    header.size_all = sizeof(ffs_header);
    header.last_file_offset = sizeof(ffs_header);
    write(file, &header, sizeof(header));
}
// Check ffs header
void ffs_check_fs_header() {
    int f = open(current_file_system, O_RDWR);
    ffs_header header;
    lseek(f, 0, SEEK_SET);
    read(f, &header, sizeof(ffs_header));
    printf("code: %s\nfile count: %ld\nall file size: %ld\nlast file offset: %ld\n", header.fs_check_code, header.amount_of_files, header.size_all, header.last_file_offset);
    close(f);
}
// Open ffs
void ffs_open_file_system(char* path) {
    current_file_system = path;
    printf("Opened: %s\n", current_file_system);
}
// Read ffs header from file
ffs_header ffs_read_fs_header(int fs) {
    ffs_header hd;
    lseek(fs, 0, SEEK_SET);
    read(fs, &hd, sizeof(ffs_header));
    return hd;
}
// Append file to file system
void ffs_append_file_to_file_system(char* file) {
    ffs_file_header f_header;
    int fsd = open(current_file_system, O_RDWR);
    ffs_header header = ffs_read_fs_header(fsd);
    int fd = open(file, O_RDWR);
    struct stat file_stats;
    stat(file, &file_stats);
    f_header.file_name = file;
    f_header.file_size = file_stats.st_size;
    f_header.next_file_offset = header.last_file_offset + sizeof(ffs_file_header) + file_stats.st_size;
    lseek(fsd, 0, SEEK_END);
    write(fsd, &f_header, sizeof(f_header));
    char buf[f_header.file_size];
    //lseek(fd, 0, SEEK_SET);
    read(fd, buf, file_stats.st_size);
    printf("File content: %s\n", buf);
    lseek(fsd, 0, SEEK_END);
    write(fsd, buf, file_stats.st_size);
    header.amount_of_files = header.amount_of_files + 1;
    header.last_file_offset = f_header.next_file_offset;
    header.size_all = header.size_all + file_stats.st_size;
    lseek(fsd, 0, SEEK_SET);
    write(fsd, &header, sizeof(ffs_header));
    close(fsd);
    close(fd);
}
// Read file from file system
void ffs_read_file_from_file_system(char* filename) {
    int fsd = open(current_file_system, O_RDWR);
    ffs_header header = ffs_read_fs_header(fsd);
    off_t current_offset = sizeof(header);
    lseek(fsd, current_offset, SEEK_SET);
    ffs_file_header f_header;
    read(fsd, &f_header, sizeof(ffs_file_header));
    printf("Name: %s\nSize: %d\nOffset: %ld\n", f_header.file_name, f_header.file_size, f_header.next_file_offset);
    lseek(fsd, sizeof(ffs_file_header), SEEK_CUR);
    char buf[f_header.file_size];
    read(fsd, buf, f_header.file_size);
    printf("File: %s\n", buf);

    close(fsd);
}
// Delete file from file system

// Delete all files from file system

// List amount of files

// List total files size

// List all files

#endif
