#include "kfs.h"
#include "../drivers/screen.h"

kfile_struct* root_file;
int current_id = 0;

//cimer paul

void init_kfs(){
  kmalloc(sizeof(kfile_struct), 1, &root_file);
  root_file->id = current_id;
  root_file->name = "LE KEBAB";
  current_id++;
  kprint("glorious kfs init\n");
}

kfile_struct* c_file(char* kfilename){
  int s = sizeof(kfile_struct);
  char* s_ascii;

  kfile_struct* last_file = get_last_file();
  kmalloc(sizeof(kfile_struct), 1, last_file->next_file);
  kmalloc(sizeof(char)*(strlen(kfilename)), 1, &(last_file->next_file->name));
  last_file = last_file->next_file;
  last_file->id = current_id;
  current_id++;

  //strcopy(last_file->next_file->name, kfilename);
  //w_file(last_file->next_file, "");

  int_to_ascii(s, s_ascii);
  kprint("last file : ");
  kprint(last_file->name);
  kprint("file ");
  kprint(last_file->name);
  kprint(" created, ");
  kprint(s_ascii);
  kprint(" bytes allocated\n");
  return last_file->next_file;
}

int list_files(){
  kfile_struct* current_kf = root_file;
  char* id_str[10];


  int_to_ascii(current_kf->id, id_str);
  kprint("#");
  kprint(id_str);
  kprint("   ");
  kprint(current_kf->name);
  kprint("\n");


  while (current_kf->next_file != 0){
    int_to_ascii(current_kf->id, id_str);
    kprint("#");
    kprint(id_str);
    kprint("   ");
    kprint(current_kf->name);
    kprint("\n");
    current_kf = current_kf->next_file;
  }
}

kfile_struct* find_by_id(int id){
  kfile_struct* current = root_file;
  while(current->next_file != 0){
    if (current->id == id){
      return current;
    }
  }
}

kfile_struct* get_last_file(){
  kfile_struct* current = root_file;
  while(current->next_file != 0){
    current = current->next_file;
  }
  return current;
}

void w_file(kfile_struct* kf, char* len){
  kmalloc(sizeof(char)*strlen(len), 1, &(kf->addr_st));
  strcopy(kf->addr_st, len);
}

void r_file(kfile_struct* kf, char* len){
  str_clear(len, strlen(len));
  kmalloc(sizeof(char)*strlen(kf->addr_st), 1, len);
  strcopy(len, kf->addr_st);
}
