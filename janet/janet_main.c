/*
* Copyright (c) 2019 Calvin Rose
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "janet.h"
#include "line.h"

#include "orgparse.h"
#include "weewiki.h"
#include "jan.h"

#ifdef _WIN32
#include <windows.h>
#include <shlwapi.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

extern const unsigned char *janet_gen_init;
extern int32_t janet_gen_init_size;

int janet_main(int argc, char **argv) {
    int i, status;
    JanetArray *args;
    JanetTable *env;

#ifdef _WIN32
    /* Enable color console on windows 10 console and utf8 output. */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    SetConsoleOutputCP(65001);

    /* Add directory containing janet.exe as DLL search path for
    dynamic modules on windows. This is needed because dynamic modules reference
    janet.exe for symbols. Otherwise, janet.exe would have to be in the current directory
    to load natives correctly. */
#ifndef JANET_NO_DYNAMIC_MODULES
    {
        SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_USER_DIRS);
        HMODULE hModule = GetModuleHandleW(NULL);
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(hModule, path, MAX_PATH);
        size_t i = wcsnlen(path, MAX_PATH);
        while (i > 0 && path[i] != '\\')
            path[i--] = '\0';
        if (i) AddDllDirectory(path);
        GetCurrentDirectoryW(MAX_PATH, path);
        AddDllDirectory(path);
    }
#endif
#endif

    /* Set up VM */
    janet_init();

    /* set up weewiki global data */
    weewiki_init(weewiki_get());

    /* Replace original getline with new line getter */
    JanetTable *replacements = janet_table(0);
    janet_table_put(replacements, janet_csymbolv("getline"), janet_wrap_cfunction(janet_line_getter));
    janet_line_init();

    /* Get core env */
    env = janet_core_env(replacements);

    /* Load weewiki c functions */
    weewiki_janet_cfuns(env);

    /* Create args tuple */
    args = janet_array(argc);
    for (i = 1; i < argc; i++)
        janet_array_push(args, janet_cstringv(argv[i]));
    janet_table_put(env, janet_ckeywordv("args"), janet_wrap_array(args));

    /* Save current executable path to (dyn :executable) */
    janet_table_put(env, janet_ckeywordv("executable"), janet_cstringv(argv[0]));

    /* Run startup script */
    status = janet_dobytes(env, janet_gen_init, janet_gen_init_size, "init.janet", NULL);

    /* Deinitialize vm */
    janet_deinit();
    janet_line_deinit();

    return status;
}
