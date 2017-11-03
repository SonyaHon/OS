#include "./ffs.c"

int main(int argc, char ** argv) {
  ffs_open_file_system("ffs_file");
  ffs_read_file_from_file_system("appendFile.txt");
  return 0;
}
