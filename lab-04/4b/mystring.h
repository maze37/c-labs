#ifndef MYSTRING_H
#define MYSTRING_H

#include <stddef.h>

char *process(const char *);
int isvowel(char a);

char *get_str();
char *myreadline(const char *prompt);
size_t mystrlen(const char *s);
char *mystrdup(const char *s);
char *mymemcpy(char *destination, const char *source, size_t n);
char *mystrtok(char *str, const char *delim);
char *mystrchr(const char *str, char c);

#endif