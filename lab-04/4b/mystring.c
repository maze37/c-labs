#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

char *get_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;

    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = mystrlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            if (!res) {
                return NULL;
            }
            mymemcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

char *myreadline(const char *prompt) {
    printf("%s", prompt);
    return get_str();
}

size_t mystrlen(const char *s) {
    size_t res = 0;
    while (*s) {
        s++;
        res++;
    }
    return res;
}

char *mystrdup(const char *s) {
    size_t len = mystrlen(s) + 1;
    char *temp = malloc(len);
    if (temp == NULL) {
        return NULL;
    }
    mymemcpy(temp, s, len);
    return temp;
}

char *mymemcpy(char *destination, const char *source, size_t n){
        for (size_t i = 0; i < n; i++){
                destination[i] = source[i];
        }
        return destination;
}

char *mystrtok(char *str, const char *delim) {
    static char *token = NULL;
    if (str != NULL) {
        token = str;
    }

    if (token == NULL) {
        return NULL;
    }

    char *first = token;
    while (*first && mystrchr(delim, *first)) {
        first++;
    }

    if (*first == '\0') {
        token = NULL;
        return NULL;
    }

    char *last = first;
    while (*last && !mystrchr(delim, *last)) {
        last++;
    }

    if (*last == '\0') {
        token = NULL;
    }
    else {
        *last = '\0';
        token = last + 1;
    }

    return first;
}

char *mystrchr(const char *s, char c) {
    while (*s) {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }
    return NULL;
}