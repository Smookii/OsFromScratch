#include "mem.h"
#include "string.h"

typedef struct kfile_struct kfile_struct;

struct kfile_struct{
  int id;
  char* name;
  char* addr_st;
  char* content;
  unsigned long len;
  kfile_struct* next_file;
};

void init_kfs();
kfile_struct* c_file(char* kfilename);
kfile_struct* o_file(char* kfilename);
int list_files();
void w_file(kfile_struct* kf, char* len);
void r_file(kfile_struct* kf, char* len);
kfile_struct* get_last_file();
kfile_struct* find_by_id(int id);
