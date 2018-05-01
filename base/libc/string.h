#ifndef STRINGS_H
#define STRINGS_H

void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
//
char single_int_to_ascii(int n);
int contains_arg(char* c);
void get_args(int index, char* input, char* dest);

void str_clear(char s[], int length);
void strcopy(char* s1, char* s2);

//void delete_str(char* in);
#endif
