#pragma once
#include <stdio.h>

//------------------------------------------------------------------------------

static inline
void
_APP_PRINT_MACRO(const char* s) {
    int indent = 0;
    bool newline = false;
    for (;*s;++s) {
        char c = *s;
        switch (c) {
            case '}':
                indent -= 1;
                break;
        }
        if (newline) {
            newline = false;
            fputc('\n', stdout);
            for (int i = 0; i < indent; ++i)
                fputs("    ", stdout);
        }
        fputc(c, stdout);
        switch (c) {
            case '}':
                newline = true;
                while (s[1] == ' ') ++s;
                break;
            case '{':
                indent += 1;
                newline = true;
                while (s[1] == ' ') ++s;
                break;
            case ';':
                newline = true;
                while (s[1] == ' ') ++s;
                break;
        }
    }
    fputc('\n', stdout);
    fputc('\n', stdout);
}

#define APP_PRINT_MACRO(...) _APP_PRINT_MACRO(__VA_ARGS__)
#define _APP_PRINT_MACRO(...) _APP_PRINT_MACRO(#__VA_ARGS__)

//------------------------------------------------------------------------------
