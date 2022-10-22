#include <string.h>
#include "btprnt.h"
#include "janet/janet.h"
#include "macfont.h"

typedef struct {
    uint8_t *buf;
    macfont_info info;
} janet_macfont_d;

static int load_macfont(janet_macfont_d *mf,
                        const char *filename)
{
    uint8_t *buf;
    FILE *fp;
    size_t sz;

    fp = fopen(filename, "r");

    if (fp == NULL) return 0;

    fseek(fp, 0L, SEEK_END);
    sz = ftell(fp);
    buf = malloc(sz + 1);
    fseek(fp, 0L, SEEK_SET);
    fread(buf, 1, sz, fp);
    fclose(fp);

    mf->buf = buf;
    macfont_info_init(&mf->info, buf);
    return 1;
}

static void free_macfont(janet_macfont_d *mf)
{
    free(mf->buf);
}

static int gcmacfont(void *p, size_t s)
{
    janet_macfont_d *mj;
    (void) s;
    mj = p;
    free_macfont(mj);
    return 0;
}

static const JanetAbstractType macfont_type = {
    "macfont",
    gcmacfont,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static janet_macfont_d * get_macfont(Janet *argv, int argc)
{
    janet_macfont_d *mj;
    mj = janet_getabstract(argv, argc, &macfont_type);
    return mj;
}

btprnt * janet2btprnt(Janet *argv, int argc);
void janet2reg(btprnt *bp,
               JanetArray *ja,
               btprnt_region *r);

static Janet j_macfont_load(int32_t argc, Janet *argv)
{
    janet_macfont_d *mf;
    const char *filename;

    janet_fixarity(argc, 1);

    filename = (const char *)janet_getstring(argv, 0);

    mf = (janet_macfont_d *)
        janet_abstract(&macfont_type,
                       sizeof(janet_macfont_d));

    if(load_macfont(mf, filename)) {
        return janet_wrap_abstract(mf);
    } else {
        janet_panicf("Could not find font %s", filename);
    }
    return janet_wrap_nil();
}

static Janet j_macfont_height(int32_t argc, Janet *argv)
{
    janet_macfont_d *mf;
    int h;

    janet_fixarity(argc, 1);

    mf = get_macfont(argv, 0);

    h = macfont_info_fontheight(&mf->info);

    return janet_wrap_integer(h);
}

static Janet j_macfont_rectheight(int32_t argc, Janet *argv)
{
    janet_macfont_d *mf;
    int h;

    janet_fixarity(argc, 1);

    mf = get_macfont(argv, 0);

    h = macfont_info_rectheight(&mf->info);

    return janet_wrap_integer(h);
}

static Janet j_macfont_descent(int32_t argc, Janet *argv)
{
    janet_macfont_d *mf;
    int d;

    janet_fixarity(argc, 1);

    mf = get_macfont(argv, 0);

    d = macfont_info_descent(&mf->info);

    return janet_wrap_integer(d);
}

static Janet j_macfont_textbox(int32_t argc, Janet *argv)
{
    janet_macfont_d *mf;
    int offx, offy;
    int nx, ny;
    int color;
    const char *str;
    btprnt_region reg;
    JanetArray *jreg;
    btprnt *bp;
    JanetArray *out;

    janet_fixarity(argc, 7);

    bp = janet2btprnt(argv, 0);
    mf = get_macfont(argv, 1);
    jreg = janet_getarray(argv, 2);

    offx = janet_getinteger(argv, 3);
    offy = janet_getinteger(argv, 4);

    str = (const char *)janet_getstring(argv, 5);
    color = janet_getinteger(argv, 6);

    janet2reg(bp, jreg, &reg);


    nx = ny = 0;
    macfont_textbox(&reg, &mf->info,
                    offx, offy, str, color,
                    &nx, &ny);
    /* mf = (janet_macfont_d *) */
    /*     janet_abstract(&macfont_type, */
    /*                    sizeof(janet_macfont_d)); */

    /* if(load_macfont(mf, filename)) { */
    /*     return janet_wrap_abstract(mf); */
    /* } else { */
    /*     return janet_wrap_nil(); */
    /* } */

    out = janet_array(2);

    janet_array_push(out, janet_wrap_integer(nx));
    janet_array_push(out, janet_wrap_integer(ny));

    return janet_wrap_array(out);
}

static Janet j_macfont_linewidth(int32_t argc, Janet *argv)
{
    janet_macfont_d *mf;
    const char *str;
    int w;

    janet_fixarity(argc, 2);

    mf = get_macfont(argv, 0);
    str = (const char *)janet_getstring(argv, 1);

    w = macfont_line_width(&mf->info, str, strlen(str));

    return janet_wrap_integer(w);
}

#define F(n) "btprnt/"n
static const JanetReg cfuns[] =
{
    {F("macfont-load"), j_macfont_load, NULL},
    {F("macfont-height"), j_macfont_height, NULL},
    {F("macfont-rectheight"), j_macfont_rectheight, NULL},
    {F("macfont-descent"), j_macfont_descent, NULL},
    {F("macfont-textbox"), j_macfont_textbox, NULL},
    {F("macfont-linewidth"), j_macfont_linewidth, NULL},
    {NULL, NULL, NULL}
};
#undef F

JANET_API void janet_cfuns_prefix(JanetTable *env,
                                  const char *regprefix,
                                  const JanetReg *cfuns);

void janet_macfont(JanetTable *env, const char *name)
{
#ifdef MONOLITH
    janet_cfuns_prefix(env, "monolith", cfuns);
#else
    janet_cfuns(env, "btprnt", cfuns);
#endif
}
