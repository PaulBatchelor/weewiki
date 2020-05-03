/* runs internal jpm utility */
#include "janet.h"

extern const unsigned char *janet_gen_jpm;
extern int32_t janet_gen_jpm_size;

int weewiki_jpm(int argc, char *argv[])
{
    int i;
    JanetArray *args;
    JanetTable *env;
    janet_init();

    env = janet_core_env(0);

    args = janet_array(argc);
    for (i = 0; i < argc; i++)
        janet_array_push(args, janet_cstringv(argv[i]));

    janet_table_put(env,
                    janet_ckeywordv("args"),
                    janet_wrap_array(args));

    janet_dobytes(env,
                  janet_gen_jpm,
                  janet_gen_jpm_size,
                  "jpm.janet", NULL);

    janet_deinit();
    return 0;
}
