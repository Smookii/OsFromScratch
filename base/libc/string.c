#include "string.h"
#include <stdint.h>
#include "../drivers/screen.h"

const char d[] = "0123456789";

char single_int_to_ascii(int n){
  int base = 10;
  return d[n % base];
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int contains_arg(char* c){
  int i = 0;
  for (i; i < strlen(c) - 2; i++){
    if (c[i] == ' ' && c[i+1] == '=' && c[i+2] == ' '){
      return i+3;
    }
  }
  return 0;
}

void get_args(int index, char* input, char* dest){
  int i = index;
  for (i; i < strlen(input); i++){
    append(dest, input[i]);
  }
}

void strcopy(char* s1, char s2[]){
  int len = strlen(s2);
  kmalloc(len*sizeof(char), 1, s1);
  int i;
  for (i=0;i<len;i++){
    s1[i] = s2[i];
  }
}

void str_clear(char s[], int length){
  int i;
  for(i=0;i<length;i++){
    s[i] = '\0';
  }
}
/*
void delete_str(char* in){
  int i = 0;
  for (i < strlen(in); i++){
    in[i] = '';
  }
}*/
