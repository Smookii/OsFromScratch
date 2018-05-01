#include "mem.h"

typedef struct kfile_struct kfile_struct;
struct kfile_struct{
  char* name;
  char* data_start;
  unsigned long len;
  kfile_struct* next_file;
};

void write_str(char* str, char* address, unsigned long len);
char* read_str(char* address, unsigned long len);
