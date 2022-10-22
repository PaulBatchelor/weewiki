#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "btprnt.h"
#include "janet/janet.h"
#include "cherry.xbm"

void btprnt_write_png(btprnt *bp, char **out, size_t *sz);

typedef struct btprnt_janet {
    btprnt *b;
} btprnt_janet;

static void free_btprnt(btprnt_janet *bj)
{
    if (bj->b != NULL) {
        btprnt_del(&bj->b);
    }
}

static int gcbtprnt(void *p, size_t s)
{
    btprnt_janet *bj;
    (void) s;
    bj = p;
    free_btprnt(bj);
    return 0;
}

static const JanetAbstractType btprnt_type = {
    "btprnt",
    gcbtprnt,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

btprnt * btprnt_janet_btprnt(btprnt_janet *bj)
{
    return bj->b;
}

btprnt * janet2btprnt(Janet *argv, int argc)
{
    btprnt_janet *bj;
    bj = janet_getabstract(argv, argc, &btprnt_type);
    if (bj != NULL) return bj->b;
    else return NULL;
}

static Janet j_new(int32_t argc, Janet *argv)
{
    int w, h;
    btprnt_janet *bj;

    janet_fixarity(argc, 2);

    w = janet_getinteger(argv, 0);
    h = janet_getinteger(argv, 1);

    bj = (btprnt_janet *) janet_abstract(&btprnt_type,
                                         sizeof(btprnt_janet));
    bj->b = btprnt_new(w, h);

    return janet_wrap_abstract(bj);
}

static Janet j_del(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;

    janet_fixarity(argc, 1);
    bj = janet_getabstract(argv, 0, &btprnt_type);
    free_btprnt(bj);

    return janet_wrap_nil();
}

typedef struct {
    btprnt_buf *buf;
    int w, h;
    int free;
} btprnt_janet_font;

static int gcbuf(void *p, size_t s)
{
    btprnt_janet_font *bb;
    (void) s;
    bb = p;
    if (bb->free) btprnt_buf_free(&bb->buf);
    return 0;
}

static const JanetAbstractType btprnt_buf_type = {
    "btprnt font",
    gcbuf,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Janet font_cherry(int32_t argc, Janet *argv)
{
    btprnt_janet_font *bb;
    janet_fixarity(argc, 0);

    bb = janet_abstract(&btprnt_buf_type,
                        sizeof(btprnt_janet_font));

    bb->buf = btprnt_buf_extmem(cherry_width,
                                cherry_height,
                                cherry_bits);
    bb->w = 7;
    bb->h = 13;
    bb->free = 1;
    return janet_wrap_abstract(bb);
}

void janet2reg(btprnt *bp,
               JanetArray *ja,
               btprnt_region *r)
{
    int x, y;
    int w, h;

    x = janet_getinteger(ja->data, 0);
    y = janet_getinteger(ja->data, 1);
    w = janet_getinteger(ja->data, 2);
    h = janet_getinteger(ja->data, 3);

    btprnt_region_init(btprnt_canvas_get(bp), r,
                       x, y,
                       w, h);
}

JanetArray * reg2janet(btprnt_region *r) {
    JanetArray *a;

    a = janet_array(4);
    janet_array_push(a, janet_wrap_integer(r->x));
    janet_array_push(a, janet_wrap_integer(r->y));
    janet_array_push(a, janet_wrap_integer(r->w));
    janet_array_push(a, janet_wrap_integer(r->h));

    return a;
}

static Janet textbox(int32_t argc, Janet *argv)
{

    btprnt_janet *bj;
    btprnt_janet_font *bf;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    const char *str;
    int scale;
    int clr;

    janet_fixarity(argc, 8);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    bf = janet_getabstract(argv, 1, &btprnt_buf_type);
    jreg = janet_getarray(argv, 2);
    x = janet_getinteger(argv, 3);
    y = janet_getinteger(argv, 4);
    str = (const char *)janet_getstring(argv, 5);
    scale = janet_getinteger(argv, 6);
    clr = janet_getinteger(argv, 7);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_textbox(&reg, bf->buf,
                        x, y,
                        bf->w, bf->h,
                        str, scale, clr);


    return janet_wrap_nil();
}

static Janet write_pbm(int32_t argc, Janet *argv)
{
    const char *filename;
    btprnt_janet *bj;
    janet_fixarity(argc, 2);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    filename = (const char *)janet_getstring(argv, 1);

    btprnt_buf_pbm(btprnt_buf_get(bj->b), filename);

    return janet_wrap_nil();
}

static Janet j_rect(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    int w, h;
    int clr;

    janet_fixarity(argc, 7);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x = janet_getinteger(argv, 2);
    y = janet_getinteger(argv, 3);
    w = janet_getinteger(argv, 4);
    h = janet_getinteger(argv, 5);
    clr = janet_getinteger(argv, 6);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_rect(&reg, x, y, w, h, clr);

    return janet_wrap_nil();
}

static Janet j_rect_filled(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    int w, h;
    int clr;

    janet_fixarity(argc, 7);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x = janet_getinteger(argv, 2);
    y = janet_getinteger(argv, 3);
    w = janet_getinteger(argv, 4);
    h = janet_getinteger(argv, 5);
    clr = janet_getinteger(argv, 6);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_rect_filled(&reg, x, y, w, h, clr);

    return janet_wrap_nil();

}

static Janet j_circ(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    int rad;
    int clr;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x = janet_getinteger(argv, 2);
    y = janet_getinteger(argv, 3);
    rad = janet_getinteger(argv, 4);
    clr = janet_getinteger(argv, 5);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_circ(&reg, x, y, rad, clr);

    return janet_wrap_nil();
}

static Janet j_circ_filled(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    int rad;
    int clr;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x = janet_getinteger(argv, 2);
    y = janet_getinteger(argv, 3);
    rad = janet_getinteger(argv, 4);
    clr = janet_getinteger(argv, 5);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_circ_filled(&reg, x, y, rad, clr);

    return janet_wrap_nil();
}

static Janet j_hline(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    int sz;
    int clr;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x = janet_getinteger(argv, 2);
    y = janet_getinteger(argv, 3);
    sz = janet_getinteger(argv, 4);
    clr = janet_getinteger(argv, 5);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_hline(&reg, x, y, sz, clr);

    return janet_wrap_nil();
}

static Janet j_vline(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    int sz;
    int clr;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x = janet_getinteger(argv, 2);
    y = janet_getinteger(argv, 3);
    sz = janet_getinteger(argv, 4);
    clr = janet_getinteger(argv, 5);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_vline(&reg, x, y, sz, clr);

    return janet_wrap_nil();
}

static Janet j_line(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x0, y0;
    int x1, y1;
    int clr;

    janet_fixarity(argc, 7);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x0 = janet_getinteger(argv, 2);
    y0 = janet_getinteger(argv, 3);
    x1 = janet_getinteger(argv, 4);
    y1 = janet_getinteger(argv, 5);
    clr = janet_getinteger(argv, 6);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_line(&reg, x0, y0, x1, y1, clr);

    return janet_wrap_nil();
}

static Janet j_drawbits(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int xpos, ypos;
    int w, h;
    JanetBuffer *buf;
    int x, y;
    int xoff, yoff;

    janet_fixarity(argc, 9);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    buf = janet_getbuffer(argv, 1);
    jreg = janet_getarray(argv, 2);
    xpos = janet_getinteger(argv, 3);
    ypos = janet_getinteger(argv, 4);
    w = janet_getinteger(argv, 5);
    h = janet_getinteger(argv, 6);
    xoff = janet_getinteger(argv, 7);
    yoff = janet_getinteger(argv, 8);

    janet2reg(bj->b, jreg, &reg);

    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y++) {
            int p;
            int pos;
            int byte;
            unsigned char bitoff;

            /* calculate position, in bits */
            pos = (y+yoff)*w + (x+xoff);
            /* get nearest byte (truncate-divide by 8) */
            byte = pos >> 3;
            /* bit offset is the difference between the two */
            bitoff = pos - (byte << 3);

            /* bounds check */
            if (byte >= buf->count) continue;

            /* get the state */
            p = buf->data[byte] & 1 << bitoff;

            btprnt_region_draw(&reg, xpos + x, ypos + y, p);
        }
    }

    return janet_wrap_nil();
}

static Janet j_tinytile(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int xpos, ypos;
    int b[3];

    janet_fixarity(argc, 7);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    xpos = janet_getinteger(argv, 2);
    ypos = janet_getinteger(argv, 3);
    b[0] = janet_getinteger(argv, 4);
    b[1] = janet_getinteger(argv, 5);
    b[2] = janet_getinteger(argv, 6);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_tinytile(&reg, xpos, ypos, b[0], b[1], b[2]);


    return janet_wrap_nil();
}

static Janet j_width(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    btprnt_buf *buf;

    janet_fixarity(argc, 1);

    bj = janet_getabstract(argv, 0, &btprnt_type);

    buf = btprnt_buf_get(bj->b);

    return janet_wrap_integer(btprnt_buf_width(buf));
}

static Janet j_height(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    btprnt_buf *buf;

    janet_fixarity(argc, 1);

    bj = janet_getabstract(argv, 0, &btprnt_type);

    buf = btprnt_buf_get(bj->b);

    return janet_wrap_integer(btprnt_buf_height(buf));
}

static Janet j_centerbox(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    btprnt_region subreg;
    JanetArray *jsubreg;
    int w;
    int h;
    int rc;

    janet_fixarity(argc, 4);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    w = janet_getinteger(argv, 2);
    h = janet_getinteger(argv, 3);

    janet2reg(bj->b, jreg, &reg);

    rc = btprnt_layout_centerbox(&reg, w, h, &subreg);

    if (rc != BTPRNT_OK) {
        janet_panic("region out of bounds\n");
        return janet_wrap_nil();
    }

    jsubreg = reg2janet(&subreg);

    return janet_wrap_array(jsubreg);
}

static Janet j_border(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    btprnt_region subreg;
    JanetArray *jsubreg;
    int size;
    int rc;

    janet_fixarity(argc, 3);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    size = janet_getinteger(argv, 2);

    janet2reg(bj->b, jreg, &reg);

    rc = btprnt_layout_border(&reg, size, &subreg);

    if (rc != BTPRNT_OK) {
        janet_panic("region out of bounds\n");
        return janet_wrap_nil();
    }

    jsubreg = reg2janet(&subreg);

    return janet_wrap_array(jsubreg);
}

static Janet j_invert(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    int w, h;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x = janet_getinteger(argv, 2);
    y = janet_getinteger(argv, 3);
    w = janet_getinteger(argv, 4);
    h = janet_getinteger(argv, 5);

    janet2reg(bj->b, jreg, &reg);

    btprnt_invert(&reg, x, y, w, h);

    return janet_wrap_nil();
}

static Janet j_bitrow(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    int nbits;
    unsigned short pat;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x = janet_getinteger(argv, 2);
    y = janet_getinteger(argv, 3);
    nbits = janet_getinteger(argv, 4);
    pat = janet_getinteger(argv, 5);

    janet2reg(bj->b, jreg, &reg);

    btprnt_bitrow(&reg, x, y, nbits, pat);

    return janet_wrap_nil();

}

static Janet j_bp2font(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    btprnt_janet_font *fnt;
    int w, h;

    janet_fixarity(argc, 3);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    fnt = janet_abstract(&btprnt_buf_type,
                         sizeof(btprnt_janet_font));
    w = janet_getinteger(argv, 1);
    h = janet_getinteger(argv, 2);

    fnt->buf = btprnt_buf_get(bj->b);
    fnt->w = w;
    fnt->h = h;
    fnt->free = 0;

    return janet_wrap_abstract(fnt);
}

static Janet j_wraptext(int32_t argc, Janet *argv)
{

    btprnt_janet *bj;
    btprnt_janet_font *bf;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    const char *str;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    bf = janet_getabstract(argv, 1, &btprnt_buf_type);
    jreg = janet_getarray(argv, 2);
    x = janet_getinteger(argv, 3);
    y = janet_getinteger(argv, 4);
    str = (const char *)janet_getstring(argv, 5);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_wraptext(&reg, bf->buf,
                        x, y,
                        bf->w, bf->h,
                        str);


    return janet_wrap_nil();
}

static Janet j_scrolltext(int32_t argc, Janet *argv)
{

    btprnt_janet *bj;
    btprnt_janet_font *bf;
    JanetArray *jreg;
    btprnt_region reg;
    int x, y;
    const char *str;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    bf = janet_getabstract(argv, 1, &btprnt_buf_type);
    jreg = janet_getarray(argv, 2);
    x = janet_getinteger(argv, 3);
    y = janet_getinteger(argv, 4);
    str = (const char *)janet_getstring(argv, 5);

    janet2reg(bj->b, jreg, &reg);
    btprnt_draw_scrolling_text(&reg, bf->buf,
                               x, y,
                               bf->w, bf->h,
                               str);


    return janet_wrap_nil();
}

static Janet j_grid(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    btprnt_region subreg;
    JanetArray *jsubreg;
    int nrows;
    int ncols;
    int row;
    int col;
    int rc;

    janet_fixarity(argc, 6);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    nrows = janet_getinteger(argv, 2);
    ncols = janet_getinteger(argv, 3);
    row = janet_getinteger(argv, 4);
    col = janet_getinteger(argv, 5);

    janet2reg(bj->b, jreg, &reg);

    rc = btprnt_layout_grid(&reg,
                            nrows, ncols,
                            row, col,
                            &subreg);

    if (rc != BTPRNT_OK) {
        janet_panic("region out of bounds\n");
        return janet_wrap_nil();
    }

    jsubreg = reg2janet(&subreg);

    return janet_wrap_array(jsubreg);
}

static Janet j_outline(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int clr;

    janet_fixarity(argc, 3);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    clr = janet_getinteger(argv, 2);

    janet2reg(bj->b, jreg, &reg);

    btprnt_layout_outline(&reg, clr);

    return janet_wrap_nil();
}

static Janet j_bezier(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    JanetArray *jreg;
    btprnt_region reg;
    int x[3], y[3];
    int clr;

    janet_fixarity(argc, 9);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    jreg = janet_getarray(argv, 1);
    x[0] = janet_getinteger(argv, 2);
    y[0] = janet_getinteger(argv, 3);
    x[1] = janet_getinteger(argv, 4);
    y[1] = janet_getinteger(argv, 5);
    x[2] = janet_getinteger(argv, 6);
    y[2] = janet_getinteger(argv, 7);
    clr = janet_getinteger(argv, 8);

    janet2reg(bj->b, jreg, &reg);

    btprnt_draw_bezier(&reg,
                       x[0], y[0],
                       x[1], y[1],
                       x[2], y[2],
                       clr);

    return janet_wrap_nil();
}

static Janet write_png(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    char *b64;
    JanetString jstr;
    size_t sz;
    janet_fixarity(argc, 1);

    bj = janet_getabstract(argv, 0, &btprnt_type);

    sz = 0;
    btprnt_write_png(bj->b, &b64, &sz);

    jstr = janet_string((unsigned char *)b64, sz);

    free(b64);
    return janet_wrap_string(jstr);
}

static Janet tile(int32_t argc, Janet *argv)
{
    btprnt_janet *bj;
    btprnt_janet *mapj;
    JanetArray *jreg;
    btprnt_region reg;
    int xpos, ypos;
    int mapx, mapy;
    int tilew, tileh;
    int scale;
    int color;

    janet_fixarity(argc, 11);

    bj = janet_getabstract(argv, 0, &btprnt_type);
    mapj = janet_getabstract(argv, 1, &btprnt_type);
    jreg = janet_getarray(argv, 2);
    janet2reg(bj->b, jreg, &reg);

    xpos = janet_getinteger(argv, 3);
    ypos = janet_getinteger(argv, 4);

    mapx = janet_getinteger(argv, 5);
    mapy = janet_getinteger(argv, 6);

    tilew = janet_getinteger(argv, 7);
    tileh = janet_getinteger(argv, 8);

    scale = janet_getinteger(argv, 9);

    color = janet_getinteger(argv, 10);

    btprnt_draw_tile(&reg,
                     btprnt_buf_get(mapj->b),
                     xpos, ypos,
                     mapx, mapy,
                     tilew, tileh,
                     scale,
                     color);

    return janet_wrap_nil();
}

#define F(n) "btprnt/"n

static const JanetReg cfuns[] =
{
    {F("new"), j_new, "creates a new btprnt instance"},
    {F("del"), j_del, "deletes btprnt instance"},
    {F("font-cherry"), font_cherry, "Gets cherry font."},
    {F("textbox"), textbox, "Makes a textbox."},
    {F("write-pbm"), write_pbm, "writes pbm file from buffer."},
    {F("rect"), j_rect, "Draws a rectangle."},
    {F("rect-filled"), j_rect_filled, "Draws a filled rectangle."},
    {F("circ"), j_circ, "Draws a circle."},
    {F("circ-filled"), j_circ_filled, "Draws a filled circle."},
    {F("hline"), j_hline, "Draws a horizontal line."},
    {F("vline"), j_vline, "draws a vertical line."},
    {F("line"), j_line, "draws a line."},
    {F("drawbits"), j_drawbits, "Draws bits from a Janet buffer."},
    {F("tinytile"), j_tinytile, "Draws a 3-byte tiny tile."},
    {F("width"), j_width, "Get buffer width."},
    {F("height"), j_height, "Get buffer height."},
    {F("centerbox"),
     j_centerbox,
     "creates a centered region from a region"},
    {F("border"),
     j_border,
     "creates a centered subregion inside of a region with a "
     "specified border size"},
    {F("invert"),
     j_invert,
     "inverts a rectangular space inside a region"},
    {F("bitrow"),
     j_bitrow,
     "write a binary pattern of integer to a row"},
    {F("bp->font"),
     j_bp2font,
     "Converts canvas in btprnt instance to font."},
    {F("wraptext"),
     j_wraptext,
     "Draws text from a bitmap font with basic wrapping."},
    {F("scrolltext"),
     j_scrolltext,
     "produces text with bounds that wraparound."},
    {F("grid"),
     j_grid,
     "returns a region that belongs to a grid of arbitrary "
     "rows and columns."},
    {F("outline"),
     j_outline,
     "outlines a region"
    },
    {F("bezier"),
     j_bezier,
     "draws a bezier line."
    },
    {F("write-png"), write_png, "writes a monochrome png."},
    {F("tile"), tile, "Draws a tile from a tilemap."},
    {NULL, NULL, NULL}
};
#undef F

void janet_macfont(JanetTable *env, const char *name);
void weewiki_janet_btprnt(JanetTable *env) {
    janet_cfuns(env, NULL, cfuns);
    janet_macfont(env, "btprnt");
}
