#line 10 "btprnt.org"
#ifndef BTPRNT_H
#define BTPRNT_H
#line 33 "btprnt.org"
typedef struct btprnt btprnt;
#line 158 "btprnt.org"
typedef struct btprnt_buf btprnt_buf;
#line 470 "btprnt.org"
typedef struct btprnt_region btprnt_region;
#line 715 "btprnt.org"
typedef struct btprnt_canvas btprnt_canvas;
#line 10 "btprnt.org"
#line 2569 "btprnt.org"
enum {
    BTPRNT_OK,
    BTPRNT_NOT_OK
};
#line 10 "btprnt.org"
#line 486 "btprnt.org"
struct btprnt_region {
    btprnt_canvas *c;
    int w, h;
    int x, y;
};
#line 10 "btprnt.org"
#line 51 "btprnt.org"
btprnt_canvas *btprnt_canvas_get(btprnt *b);
#line 65 "btprnt.org"
btprnt_buf * btprnt_buf_get(btprnt *b);
#line 82 "btprnt.org"
btprnt * btprnt_new(int w, int h);
#line 118 "btprnt.org"
void btprnt_del(btprnt **b);
#line 149 "btprnt.org"
void btprnt_del(btprnt **b);
#line 180 "btprnt.org"
btprnt_buf * btprnt_buf_init(int w, int h);
#line 231 "btprnt.org"
btprnt_buf * btprnt_buf_extmem(int w, int h,
                               unsigned char *data);
#line 268 "btprnt.org"
void btprnt_buf_free(btprnt_buf **buf);
#line 288 "btprnt.org"
unsigned char btprnt_buf_read(btprnt_buf *b, int x, int y);
void btprnt_buf_write(btprnt_buf *b, int x, int y, int c);
#line 346 "btprnt.org"
int btprnt_buf_width(btprnt_buf *buf);
int btprnt_buf_height(btprnt_buf *buf);
#line 368 "btprnt.org"
void btprnt_buf_pbm(btprnt_buf *buf, const char *filename);
#line 408 "btprnt.org"
void btprnt_pbm(btprnt *bp, const char *filename);
#line 425 "btprnt.org"
void btprnt_buf_xbm(btprnt_buf *buf,
                    const char *name,
                    const char *filename);
#line 497 "btprnt.org"
btprnt_region * btprnt_region_new(btprnt_canvas *c,
                                  int x, int y,
                                  int w, int h);
#line 524 "btprnt.org"
void btprnt_region_del(btprnt_region **r);
#line 543 "btprnt.org"
void btprnt_region_init(btprnt_canvas *c,
                        btprnt_region *r,
                        int x, int y,
                        int w, int h);
#line 568 "btprnt.org"
void btprnt_region_xpos_set(btprnt_region *r, int x);
void btprnt_region_ypos_set(btprnt_region *r, int y);
void btprnt_region_width_set(btprnt_region *r, int w);
void btprnt_region_height_set(btprnt_region *r, int h);
#line 604 "btprnt.org"
void btprnt_region_draw(btprnt_region *r,
                        int x, int y,
                        int c);
#line 641 "btprnt.org"
void btprnt_region_draw_wrap(btprnt_region *r,
                             int x, int y,
                             int c);
#line 686 "btprnt.org"
int btprnt_region_read(btprnt_region *r, int x, int y);
#line 723 "btprnt.org"
btprnt_canvas * btprnt_canvas_new(btprnt_buf *buf);
#line 745 "btprnt.org"
void btprnt_canvas_offx_set(btprnt_canvas *c, int x);
void btprnt_canvas_offy_set(btprnt_canvas *c, int y);
#line 764 "btprnt.org"
void btprnt_canvas_del(btprnt_canvas **c);
#line 891 "btprnt.org"
void btprnt_draw_tile(btprnt_region *reg,
                      btprnt_buf *map,
                      int xpos, int ypos,
                      int mx, int my,
                      int w, int h,
                      int scale, int color);
#line 921 "btprnt.org"
void btprnt_draw_tile_wrap(btprnt_region *reg,
                           btprnt_buf *map,
                           int xpos, int ypos,
                           int mx, int my,
                           int w, int h,
                           int scale, int color);
#line 958 "btprnt.org"
void btprnt_draw_char(btprnt_region *reg,
                      btprnt_buf *map,
                      int xpos, int ypos,
                      int w, int h,
                      char c, int scale, int color);
#line 997 "btprnt.org"
void btprnt_draw_char_wrap(btprnt_region *reg,
                           btprnt_buf *map,
                           int xpos, int ypos,
                           int w, int h,
                           char c, int scale, int color);
#line 1036 "btprnt.org"
void btprnt_draw_text(btprnt_region *reg,
                      btprnt_buf *map,
                      int xpos, int ypos,
                      int w, int h,
                      const char *str);
#line 1069 "btprnt.org"
void btprnt_draw_scrolling_text(btprnt_region *reg,
                                btprnt_buf *map,
                                int xpos, int ypos,
                                int w, int h,
                                const char *str);
#line 1102 "btprnt.org"
void btprnt_draw_wraptext(btprnt_region *reg,
                          btprnt_buf *map,
                          int xpos, int ypos,
                          int w, int h,
                          const char *str);
#line 1154 "btprnt.org"
void btprnt_draw_textbox(btprnt_region *reg,
                         btprnt_buf *map,
                         int xpos, int ypos,
                         int w, int h,
                         const char *str,
                         int scale,
                         int color);
#line 1298 "btprnt.org"
void btprnt_fill(btprnt_region *reg, int clr);
#line 1317 "btprnt.org"
void btprnt_draw_hline(btprnt_region *r,
                       int x, int y,
                       int sz, int clr);
#line 1338 "btprnt.org"
void btprnt_draw_vline(btprnt_region *r,
                       int x, int y,
                       int sz, int clr);
#line 1360 "btprnt.org"
void btprnt_draw_line(btprnt_region *reg,
                      int x0, int y0,
                      int x1, int y1,
                      int clr);
#line 1425 "btprnt.org"
void btprnt_draw_thickline(btprnt_region *reg,
                           int x0, int y0,
                           int x1, int y1,
                           int thick,
                           int clr);
#line 1487 "btprnt.org"
void btprnt_draw_slopeline(btprnt_region *r,
                           int xstart,
                           int ystart,
                           int xslp,
                           int yslp,
                           int nsteps,
                           int clr,
                           int *xlast,
                           int *ylast);
#line 1559 "btprnt.org"
void btprnt_draw_rect(btprnt_region *r,
                      int x, int y,
                      int w, int h,
                      int clr);
#line 1580 "btprnt.org"
void btprnt_draw_rect_filled(btprnt_region *r,
                             int xpos, int ypos,
                             int w, int h,
                             int clr);
#line 1621 "btprnt.org"
void btprnt_draw_circ(btprnt_region *r,
                      int cx, int cy,
                      int rad,
                      int clr);
#line 1679 "btprnt.org"
void btprnt_draw_circ_filled(btprnt_region *r,
                      int cx, int cy,
                      int rad,
                      int clr);
#line 1750 "btprnt.org"
void btprnt_draw_thickcirc(btprnt_region *r,
                           int cx, int cy,
                           int rad, int thick,
                           int clr);
#line 1808 "btprnt.org"
void btprnt_draw_roundrect(btprnt_region *reg,
                           int x, int y,
                           int w, int h,
                           int r,
                           int clr);
#line 1888 "btprnt.org"
void btprnt_draw_roundrect_filled(btprnt_region *r,
                                  int x, int y,
                                  int w, int h,
                                  int rad,
                                  int clr);
#line 1994 "btprnt.org"
void btprnt_draw_triangle(btprnt_region *r,
                          int v1x, int v1y,
                          int v2x, int v2y,
                          int v3x, int v3y,
                          int c);
#line 2225 "btprnt.org"
void btprnt_draw_arrow(btprnt_region *r,
                       int start_x, int start_y,
                       int end_x, int end_y,
                       int arrow_start,
                       int arrow_end,
                       int draw_line,
                       int c);
#line 2320 "btprnt.org"
void btprnt_draw_bezier(btprnt_region *reg,
                        int x0, int y0,
                        int x1, int y1,
                        int x2, int y2,
                        int c);
#line 2459 "btprnt.org"
void btprnt_draw_bezier_arrow(btprnt_region *r,
                              int start_x, int start_y,
                              int end_x, int end_y,
                              int ctrl_x, int ctrl_y,
                              int arrow_start,
                              int arrow_end,
                              int c);
#line 2509 "btprnt.org"
void btprnt_draw_tinytile(btprnt_region *r,
                          int xpos,
                          int ypos,
                          int b0,
                          int b1,
                          int b2);
#line 2590 "btprnt.org"
void btprnt_layout_outline(btprnt_region *r, int c);
#line 2614 "btprnt.org"
int btprnt_layout_centerbox(btprnt_region *r,
                            int w, int h,
                            btprnt_region *s);
#line 2656 "btprnt.org"
int btprnt_layout_border(btprnt_region *r,
                         int border,
                         btprnt_region *s);
#line 2686 "btprnt.org"
int btprnt_layout_grid(btprnt_region *r,
                       int nrows,
                       int ncols,
                       int row,
                       int col,
                       btprnt_region *s);
#line 2743 "btprnt.org"
void btprnt_invert(btprnt_region *r,
                   int xoff, int yoff,
                   int w, int h);
#line 2784 "btprnt.org"
void btprnt_bitrow(btprnt_region *reg,
                   int x, int y,
                   int nbits,
                   unsigned short pat);
#line 16 "btprnt.org"
#ifdef BTPRNT_IMPL
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#line 40 "btprnt.org"
struct btprnt {
    btprnt_buf *buf;
    btprnt_canvas *canvas;
};
#line 166 "btprnt.org"
struct btprnt_buf {
    int w;
    int h;
    int stride;
    unsigned char free;
    unsigned char *data;
};
#line 785 "btprnt.org"
struct btprnt_canvas {
    btprnt_buf *buf;
    int offx, offy;
};
#line 16 "btprnt.org"
#line 828 "btprnt.org"
static void draw_tile(btprnt_region *reg,
                      btprnt_buf *map,
                      int xpos, int ypos,
                      int mx, int my,
                      int w, int h,
                      int scale, int color,
                      void (*draw)(btprnt_region*,int,int,int));
#line 16 "btprnt.org"
#line 55 "btprnt.org"
btprnt_canvas *btprnt_canvas_get(btprnt *b)
{
    return b->canvas;
}
#line 69 "btprnt.org"
btprnt_buf * btprnt_buf_get(btprnt *b)
{
    return b->buf;
}
#line 87 "btprnt.org"
btprnt * btprnt_new(int w, int h)
{
    btprnt *b;

    b = calloc(1, sizeof(btprnt));

    if (b == NULL) return NULL;

    b->buf = btprnt_buf_init(w, h);

    if (b->buf == NULL) {
        free(b);
        return NULL;
    }

    b->canvas = btprnt_canvas_new(b->buf);

    if (b->canvas == NULL) {
        btprnt_buf_free(&b->buf);
        free(b);
        return NULL;
    }
    return b;
}
#line 137 "btprnt.org"
void btprnt_del(btprnt **b)
{
    if (*b == NULL) return;
    btprnt_canvas_del(&(*b)->canvas);
    btprnt_buf_free(&(*b)->buf);
    free(*b);
    *b = NULL;
}
#line 195 "btprnt.org"
btprnt_buf * btprnt_buf_init(int w, int h)
{
    btprnt_buf *b;
    int stride;

    b = calloc(1, sizeof(btprnt_buf));

    if (b == NULL) return NULL;

    b->free = 1;
    b->w = w;
    b->h = h;

    if (w % 8) {
        stride = ((w / 8) + 1);
    } else {
        stride = w / 8;
    }

    b->stride = stride;
    b->data = calloc(1, stride * h);

    if (b->data == NULL) {
        free(b);
        return NULL;
    }

    return b;
}
#line 237 "btprnt.org"
btprnt_buf * btprnt_buf_extmem(int w, int h,
                               unsigned char *data)
{
    btprnt_buf *b;
    int stride;

    b = calloc(1, sizeof(btprnt_buf));

    if (b == NULL) return NULL;

    b->free = 0;
    b->w = w;
    b->h = h;

    if (w % 8) {
        stride = ((w / 8) + 1) * 8;
    } else {
        stride = w / 8;
    }

    b->stride = stride;
    b->data = data;

    return b;
}
#line 274 "btprnt.org"
void btprnt_buf_free(btprnt_buf **buf)
{
    if (*buf == NULL) return;
    if ((*buf)->free) free((*buf)->data);
    free(*buf);
    *buf = NULL;
}
#line 304 "btprnt.org"
unsigned char btprnt_buf_read(btprnt_buf *b, int x, int y)
{
    unsigned char bitpos;
    int pos;
    int off;

    off = x >> 3;
    pos = (y * b->stride) + off;
    bitpos = x - (off * 8);

    return (b->data[pos] & (1 << bitpos)) > 0;
}
#line 323 "btprnt.org"
void btprnt_buf_write(btprnt_buf *b, int x, int y, int c)
{
    unsigned char bitpos;
    int pos;
    int off;

    off = x >> 3;
    pos = (y * b->stride) + off;
    bitpos = x - (off * 8);

    if (c) {
        b->data[pos] |= (1 << bitpos);
    } else {
        b->data[pos] &= ~(1 << bitpos);
    }
}
#line 352 "btprnt.org"
int btprnt_buf_width(btprnt_buf *buf)
{
    return buf->w;
}

int btprnt_buf_height(btprnt_buf *buf)
{
    return buf->h;
}
#line 372 "btprnt.org"
void btprnt_buf_pbm(btprnt_buf *buf, const char *filename)
{
    FILE *fp;
    int x, y;
    int count;
    fp = fopen(filename, "w");

    if (buf == NULL || fp == NULL) return;

    fprintf(fp, "P1\n");
    fprintf(fp, "# Generated with btprnt\n");
    fprintf(fp, "%d %d\n", buf->w, buf->h);

    count = 0;
    for(y = 0; y < buf->h; y++) {
        for(x = 0; x < buf->w; x++) {
            fprintf(fp, "%d", btprnt_buf_read(buf, x, y));
            count++;
            if (count == 16) {
                count = 0;
                fprintf(fp, "\n");
            } else if (count != 0) {
                fprintf(fp, " ");
            }
        }
    }

    fclose(fp);
}
#line 413 "btprnt.org"
void btprnt_pbm(btprnt *bp, const char *filename)
{
    btprnt_buf_pbm(bp->buf, filename);
}
#line 431 "btprnt.org"
void btprnt_buf_xbm(btprnt_buf *buf,
                    const char *name,
                    const char *filename)
{
    FILE *fp;
    int n;
    unsigned int count;

    fp = fopen(filename, "w");

    if (buf == NULL || fp == NULL) return;

    fprintf(fp, "#define %s_width %d\n", name, buf->w);
    fprintf(fp, "#define %s_height %d\n", name, buf->h);
    fprintf(fp, "static unsigned char %s_bits[] = {\n", name);

    count = buf->h * buf->stride;

    for (n = 0; n < count; n++) {
        fprintf(fp, "0x%x,", buf->data[n]);
        if ((n + 1) % 8 == 0) {
            fprintf(fp, "\n");
        } else {
            fprintf(fp, " ");
        }
    }

    fprintf(fp, "};");


    fclose(fp);
}
#line 504 "btprnt.org"
btprnt_region * btprnt_region_new(btprnt_canvas *c,
                                  int x, int y,
                                  int w, int h)
{
    btprnt_region *r;

    r = calloc(1, sizeof(btprnt_region));

    if (r == NULL) return NULL;

    btprnt_region_init(c, r, x, y, w, h);

    return r;
}
#line 529 "btprnt.org"
void btprnt_region_del(btprnt_region **r)
{
    if (*r == NULL) return;
    free(*r);
    *r = NULL;
}
#line 550 "btprnt.org"
void btprnt_region_init(btprnt_canvas *c,
                        btprnt_region *r,
                        int x, int y,
                        int w, int h)
{
    btprnt_region_xpos_set(r, x);
    btprnt_region_ypos_set(r, y);
    btprnt_region_width_set(r, w);
    btprnt_region_height_set(r, h);
    r->c = c;
}
#line 576 "btprnt.org"
void btprnt_region_xpos_set(btprnt_region *r, int x)
{
    r->x = x;
}

void btprnt_region_ypos_set(btprnt_region *r, int y)
{
    r->y = y;
}

void btprnt_region_width_set(btprnt_region *r, int w)
{
    r->w = w;
}

void btprnt_region_height_set(btprnt_region *r, int h)
{
    r->h = h;
}
#line 615 "btprnt.org"
void btprnt_region_draw(btprnt_region *r,
                        int x, int y,
                        int c)
{
    btprnt_canvas *cv;
    int gx, gy;

    cv = r->c;

    if (x < 0 || x >= r->w) return;
    if (y < 0 || y >= r->h) return;

    gx = cv->offx + r->x + x;
    if (gx < 0 || gx >= cv->buf->w) return;
    gy = cv->offy + r->y + y;
    if (gy < 0 || gy >= cv->buf->h) return;

    btprnt_buf_write(cv->buf, gx, gy, c);
}
#line 657 "btprnt.org"
void btprnt_region_draw_wrap(btprnt_region *r,
                             int x, int y,
                             int c)
{
    btprnt_canvas *cv;
    int gx, gy;

    cv = r->c;

    while (x < 0) x += r->w;
    while (x >= r->w) x -= r->w;

    while (y < 0) y += r->h;
    while (y >= r->h) y -= r->h;

    gx = cv->offx + r->x + x;
    if (gx < 0 || gx >= cv->buf->w) return;
    gy = cv->offy + r->y + y;
    if (gy < 0 || gy >= cv->buf->h) return;

    btprnt_buf_write(cv->buf, gx, gy, c);
}
#line 691 "btprnt.org"
int btprnt_region_read(btprnt_region *r, int x, int y)
{
    btprnt_canvas *cv;
    int gx, gy;

    cv = r->c;

    if (x < 0 || x >= r->w) return 0;
    if (y < 0 || y >= r->h) return 0;

    gx = cv->offx + r->x + x;
    if (gx < 0 || gx >= cv->buf->w) return 0;
    gy = cv->offy + r->y + y;
    if (gy < 0 || gy >= cv->buf->h) return 0;

    return btprnt_buf_read(cv->buf, gx, gy);
}
#line 728 "btprnt.org"
btprnt_canvas * btprnt_canvas_new(btprnt_buf *buf)
{
    btprnt_canvas *c;

    c = calloc(1, sizeof(btprnt_canvas));

    if (c == NULL) return NULL;

    c->buf = buf;
    btprnt_canvas_offx_set(c, 0);
    btprnt_canvas_offy_set(c, 0);
    return c;
}
#line 751 "btprnt.org"
void btprnt_canvas_offx_set(btprnt_canvas *c, int x)
{
    c->offx = x;
}

void btprnt_canvas_offy_set(btprnt_canvas *c, int y)
{
    c->offy = y;
}
#line 769 "btprnt.org"
void btprnt_canvas_del(btprnt_canvas **c)
{
    if (*c == NULL) return;
    free(*c);
    *c = NULL;
}
#line 847 "btprnt.org"
static void draw_tile(btprnt_region *reg,
                      btprnt_buf *map,
                      int xpos, int ypos,
                      int mx, int my,
                      int w, int h,
                      int scale, int color,
                      void (*draw)(btprnt_region*,int,int,int))
{
    int startx;
    int starty;
    int x;
    int y;
    int c;

    startx = mx * w;
    starty = my * h;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            c = btprnt_buf_read(map,
                                startx + x,
                                starty + y);
            if (c) {
                if (scale == 1) {
                    draw(reg, xpos + x, ypos + y, color);
                } else {
                    int sx, sy;
                    for (sy = 0; sy < scale; sy++) {
                        for (sx = 0; sx < scale; sx++) {
                            draw(reg,
                                 xpos + x*scale + sx,
                                 ypos + y*scale + sy,
                                 color);
                        }
                    }
                }
            }
        }
    }
}
#line 901 "btprnt.org"
void btprnt_draw_tile(btprnt_region *reg,
                      btprnt_buf *map,
                      int xpos, int ypos,
                      int mx, int my,
                      int w, int h,
                      int scale, int color)
{
    draw_tile(reg, map,
              xpos, ypos,
              mx, my,
              w, h,
              scale, color,
              btprnt_region_draw);
}
#line 931 "btprnt.org"
void btprnt_draw_tile_wrap(btprnt_region *reg,
                           btprnt_buf *map,
                           int xpos, int ypos,
                           int mx, int my,
                           int w, int h,
                           int scale, int color)
{
    draw_tile(reg, map,
              xpos, ypos,
              mx, my,
              w, h,
              scale, color,
              btprnt_region_draw_wrap);
}
#line 967 "btprnt.org"
void btprnt_draw_char(btprnt_region *reg,
                      btprnt_buf *map,
                      int xpos, int ypos,
                      int w, int h,
                      char c, int scale, int color)
{
    int gx, gy;
    char o;
    int ncols;

    o = c - ' '; /* start at 0 */

    ncols = map->w / w;

    gx = o % ncols;
    gy = o / ncols;

    btprnt_draw_tile(reg, map,
                     xpos, ypos,
                     gx, gy,
                     w, h,
                     scale, color);
}
#line 1006 "btprnt.org"
void btprnt_draw_char_wrap(btprnt_region *reg,
                           btprnt_buf *map,
                           int xpos, int ypos,
                           int w, int h,
                           char c, int scale, int color)
{
    int gx, gy;
    char o;
    int ncols;

    o = c - ' '; /* start at 0 */

    ncols = map->w / w;

    gx = o % ncols;
    gy = o / ncols;

    btprnt_draw_tile_wrap(reg, map,
                          xpos, ypos,
                          gx, gy,
                          w, h,
                          scale, color);
}
#line 1045 "btprnt.org"
void btprnt_draw_text(btprnt_region *reg,
                      btprnt_buf *map,
                      int xpos, int ypos,
                      int w, int h,
                      const char *str)
{
    int len;
    int n;
    len = strlen(str);

    for (n = 0; n < len; n++) {
        btprnt_draw_char(reg, map,
                         xpos + w*n, ypos,
                         w, h,
                         str[n], 1, 1);
    }
}
#line 1078 "btprnt.org"
void btprnt_draw_scrolling_text(btprnt_region *reg,
                                btprnt_buf *map,
                                int xpos, int ypos,
                                int w, int h,
                                const char *str)
{
    int len;
    int n;
    len = strlen(str);

    for (n = 0; n < len; n++) {
        btprnt_draw_char_wrap(reg, map,
                              xpos + w*n, ypos,
                              w, h,
                              str[n], 1, 1);
    }
}
#line 1111 "btprnt.org"
void btprnt_draw_wraptext(btprnt_region *reg,
                          btprnt_buf *map,
                          int xpos, int ypos,
                          int w, int h,
                          const char *str)
{
    int len;
    int n;
    int curpos;
    int line;
    int c;
    len = strlen(str);
    line = 0;
    curpos = 0;
    c = 0;

    for (n = 0; n < len; n++) {
        curpos = xpos + w*c;

        if (curpos >= reg->w) {
            curpos = xpos;
            line++;
            c = 0;
        }

        btprnt_draw_char(reg, map,
                         curpos, ypos + line*h,
                         w, h,
                         str[n], 1, 1);
        c++;
    }
}
#line 1192 "btprnt.org"
void btprnt_draw_textbox(btprnt_region *reg,
                         btprnt_buf *map,
                         int xpos, int ypos,
                         int w, int h,
                         const char *str,
                         int scale,
                         int color)
{
    int len;
    int n;
    int start;
    int nchars;
    int c;
    int line;
    len = strlen(str);

    start = 0;
    nchars = 0;
    c = 0;
    line = 0;
    for (n = 0; n < len; n++) {
        nchars++;
        if (str[n] == ' ' || str[n] == '\n') {
            int wordlen;
            int off;
            int i;
            int curpos;
            char x;

            wordlen = nchars*w*scale;
            off = xpos + c*w*scale;

            if ((off + wordlen) > reg->w) {
                /* nested if is a clumsy, but it works */
                if (wordlen < reg->w) {
                    line++;
                    c = 0;
                }
            }

            for (i = 0; i < nchars; i++) {
                curpos = xpos + c*w*scale;

                x = str[start + i];

                if ((curpos + w*scale) > reg->w || x == '\n') {
                    curpos = xpos;
                    line++;
                    c = 0;
                }


                if (x != '\n') {
                    btprnt_draw_char(reg, map,
                                     curpos,
                                     ypos + line*h*scale,
                                     w, h, x, scale, color);
                    c++;
                }
            }

            start = n + 1;
            nchars = 0;
        }
    }

    if (nchars > 0) {
        /* duplicate code alert ring ring ring */
        int wordlen;
        int off;
        int i;
        int curpos;

        wordlen = nchars * w * scale;
        off = xpos + c*w*scale;

        if ((off + wordlen) > reg->w) {
            line++;
            c = 0;
        }

        for (i = 0; i < nchars; i++) {
            curpos = xpos + c*w*scale;

            if ((curpos + w*scale) > reg->w) {
                curpos = xpos;
                line++;
                c = 0;
            }

            btprnt_draw_char(reg, map,
                             curpos, ypos + line*h*scale,
                             w, h,
                             str[start + i], scale, color);
            c++;
        }

        start = n + 1;
        nchars = 0;
    }
}
#line 1302 "btprnt.org"
void btprnt_fill(btprnt_region *reg, int clr)
{
    int x, y;
    for (y = 0; y < reg->h; y++) {
        for (x = 0; x < reg->w; x++) {
            btprnt_region_draw(reg, x, y, clr);
        }
    }
}
#line 1323 "btprnt.org"
void btprnt_draw_hline(btprnt_region *r,
                       int x, int y,
                       int sz, int clr)
{
    int n;

    for (n = 0; n < sz; n++) {
        btprnt_region_draw(r, x + n, y, clr);
    }
}
#line 1344 "btprnt.org"
void btprnt_draw_vline(btprnt_region *r,
                       int x, int y,
                       int sz, int clr)
{
    int n;

    for (n = 0; n < sz; n++) {
        btprnt_region_draw(r, x, y + n, clr);
    }
}
#line 1368 "btprnt.org"
static void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void btprnt_draw_line(btprnt_region *reg,
                      int x0, int y0,
                      int x1, int y1,
                      int clr)
{
    int x, y;
    int dx, dy;
    int derror2;
    int error2;
    char steep = 0;

    if (abs(x0 - x1) < abs(y0 - y1)) {
        swap(&x0, &y0);
        swap(&x1, &y1);
        steep = 1;
    }

    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    dx = x1 - x0;
    dy = y1 - y0;
    derror2 = abs(dy) * 2;
    error2 = 0;
    y = y0;

    for (x = x0; x < x1; x++) {
        if (steep) {
            btprnt_region_draw(reg, y, x, clr);
        } else {
            btprnt_region_draw(reg, x, y, clr);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}
#line 1434 "btprnt.org"
void btprnt_draw_thickline(btprnt_region *reg,
                           int x0, int y0,
                           int x1, int y1,
                           int thick,
                           int clr)
{
    int x, y;
    int dx, dy;
    int derror2;
    int error2;
    char steep = 0;

    if (abs(x0 - x1) < abs(y0 - y1)) {
        swap(&x0, &y0);
        swap(&x1, &y1);
        steep = 1;
    }

    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    dx = x1 - x0;
    dy = y1 - y0;
    derror2 = abs(dy) * 2;
    error2 = 0;
    y = y0;

    for (x = x0; x < x1; x++) {
        if (steep) {
            btprnt_draw_circ_filled(reg, y, x, thick, clr);
        } else {
            btprnt_draw_circ_filled(reg, x, y, thick, clr);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}
#line 1500 "btprnt.org"
void btprnt_draw_slopeline(btprnt_region *r,
                           int xstart,
                           int ystart,
                           int xslp,
                           int yslp,
                           int nsteps,
                           int clr,
                           int *xlast,
                           int *ylast)
{
    int c;
    int xp, yp;
    int ydir, xdir;

    c = nsteps;

    xp = xstart;
    yp = ystart;

    xdir = (xslp < 0) ? -1 : 1;
    ydir = (yslp < 0) ? -1 : 1;

    xslp = abs(xslp);
    yslp = abs(yslp);

    while (c > 0) {
        int x, y;
        for (x = 0; x < xslp; x++) {
            btprnt_region_draw(r, xp, yp, clr);
            c--;
            if (c <= 0) break;
            xp += xdir;
        }

        if (c <= 0) break;

        for (y = 0; y < yslp; y++) {
            if (y > 0) {
                btprnt_region_draw(r, xp - xdir, yp, clr);
                c--;
                if (c <= 0) break;
            }
            yp += ydir;
        }

    }

    if (xlast != NULL) *xlast = xp;
    if (ylast != NULL) *ylast = yp;
}
#line 1566 "btprnt.org"
void btprnt_draw_rect(btprnt_region *r,
                      int x, int y,
                      int w, int h,
                      int clr)
{
    btprnt_draw_hline(r, x, y, w, clr);
    btprnt_draw_hline(r, x, y + (h - 1), w, clr);
    btprnt_draw_vline(r, x, y, h, clr);
    btprnt_draw_vline(r, x + (w - 1), y, h, clr);
}
#line 1587 "btprnt.org"
void btprnt_draw_rect_filled(btprnt_region *r,
                             int xpos, int ypos,
                             int w, int h,
                             int clr)
{
    int x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            btprnt_region_draw(r,
                               xpos + x,
                               ypos + y,
                               clr);
        }
    }
}
#line 1628 "btprnt.org"
static void circ_pixel(btprnt_region *r,
                       int cx, int cy,
                       int x, int y,
                       int clr)
{
    btprnt_region_draw(r, cx - x, cy + y, clr);
    btprnt_region_draw(r, cx + x, cy + y, clr);
    btprnt_region_draw(r, cx - y, cy + x, clr);
    btprnt_region_draw(r, cx + y, cy + x, clr);
    btprnt_region_draw(r, cx + x, cy - y, clr);
    btprnt_region_draw(r, cx - x, cy - y, clr);
    btprnt_region_draw(r, cx + y, cy - x, clr);
    btprnt_region_draw(r, cx - y, cy - x, clr);
}

void btprnt_draw_circ(btprnt_region *r,
                      int cx, int cy,
                      int rad,
                      int clr)
{
    int x;
    int y;
    int err;

    x = 0;
    y = rad;
    err = 1 - rad;

    circ_pixel(r, cx, cy, x, y, clr);

    while (x < y) {
        x++;

        if (err < 0) {
            err += 2 * x + 1;
        } else {
            y--;
            err += 2 * (x - y) + 1;
        }

        circ_pixel(r, cx, cy, x, y, clr);
    }
}
#line 1688 "btprnt.org"
static void circ_line(btprnt_region *r,
                       int cx, int cy,
                       int x, int y,
                       int clr)
{
    btprnt_draw_line(r,
                     cx - x, cy + y,
                     cx + x, cy + y,
                     clr);
    btprnt_draw_line(r,
                     cx - y, cy + x,
                     cx + y, cy + x,
                     clr);
    btprnt_draw_line(r,
                     cx + x, cy - y,
                     cx - x, cy - y,
                     clr);
    btprnt_draw_line(r,
                     cx + y, cy - x,
                     cx - y, cy - x,
                     clr);

}

void btprnt_draw_circ_filled(btprnt_region *r,
                      int cx, int cy,
                      int rad,
                      int clr)
{
    int x;
    int y;
    int err;

    x = 0;
    y = rad;
    err = 1 - rad;

    circ_line(r, cx, cy, x, y, clr);

    while (x < y) {
        x++;

        if (err < 0) {
            err += 2 * x + 1;
        } else {
            y--;
            err += 2 * (x - y) + 1;
        }

        circ_line(r, cx, cy, x, y, clr);
    }
}
#line 1758 "btprnt.org"
static void circ_dots(btprnt_region *r,
                       int cx, int cy,
                       int x, int y,
                       int clr, int thick)
{
    btprnt_draw_circ_filled(r, cx - x, cy + y, thick, clr);
    btprnt_draw_circ_filled(r, cx + x, cy + y, thick, clr);
    btprnt_draw_circ_filled(r, cx - y, cy + x, thick, clr);
    btprnt_draw_circ_filled(r, cx + y, cy + x, thick, clr);
    btprnt_draw_circ_filled(r, cx + x, cy - y, thick, clr);
    btprnt_draw_circ_filled(r, cx - x, cy - y, thick, clr);
    btprnt_draw_circ_filled(r, cx + y, cy - x, thick, clr);
    btprnt_draw_circ_filled(r, cx - y, cy - x, thick, clr);
}

void btprnt_draw_thickcirc(btprnt_region *r,
                           int cx, int cy,
                           int rad, int thick,
                           int clr)
{
    int x;
    int y;
    int err;

    x = 0;
    y = rad;
    err = 1 - rad;

    circ_dots(r, cx, cy, x, y, clr, thick);

    while (x < y) {
        x++;

        if (err < 0) {
            err += 2 * x + 1;
        } else {
            y--;
            err += 2 * (x - y) + 1;
        }

        circ_dots(r, cx, cy, x, y, clr, thick);
    }
}
#line 1817 "btprnt.org"
static void quadcirc(btprnt_region *reg,
                     int x0, int y0,
                     int r,
                     int corner,
                     int clr)
{
    int f;
    int ddf_x;
    int ddf_y;
    int x;
    int y;

    f = 1 - r;
    ddf_x = 1;
    ddf_y = -2 * r;
    x = 0;
    y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddf_y += 2;
            f += ddf_y;
        }

        x++;
        ddf_x += 2;
        f += ddf_x;

        if (corner & 0x4) {
            btprnt_region_draw(reg, x0 + x, y0 + y, clr);
            btprnt_region_draw(reg, x0 + y, y0 + x, clr);
        }

        if (corner & 0x2) {
            btprnt_region_draw(reg, x0 + x, y0 - y, clr);
            btprnt_region_draw(reg, x0 + y, y0 - x, clr);
        }

        if (corner & 0x8) {
            btprnt_region_draw(reg, x0 - y, y0 + x, clr);
            btprnt_region_draw(reg, x0 - x, y0 + y, clr);
        }

        if (corner & 0x1) {
            btprnt_region_draw(reg, x0 - y, y0 - x, clr);
            btprnt_region_draw(reg, x0 - x, y0 - y, clr);
        }
    }
}

void btprnt_draw_roundrect(btprnt_region *reg,
                           int x, int y,
                           int w, int h,
                           int r,
                           int clr)
{
    btprnt_draw_hline(reg, x + r, y, w - 2 * r, clr);
    btprnt_draw_hline(reg, x + r, y + h - 1, w - 2 * r, clr);
    btprnt_draw_vline(reg, x, y + r, h - 2 * r, clr);
    btprnt_draw_vline(reg, x + w - 1, y + r, h - 2 * r, clr);

    quadcirc(reg, x + r, y + r, r, 1, clr);
    quadcirc(reg, x + w - r - 1, y + r, r, 2, clr);
    quadcirc(reg, x + w - r - 1, y + h - r - 1, r, 4, clr);
    quadcirc(reg, x + r, y + h - r - 1, r, 8, clr);
}
#line 1897 "btprnt.org"
static void quadcirc_filled(btprnt_region *reg,
                            int x0, int y0, int r,
                            int corner, int delta,
                            int clr)
{
    int f;
    int ddf_x;
    int ddf_y;
    int x;
    int y;
    int px;
    int py;

    f = 1 - r;
    ddf_x = 1;
    ddf_y = -2 * r;
    x = 0;
    y = r;
    px = x;
    py = y;

    delta++;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddf_y += 2;
            f += ddf_y;
        }

        x++;
        ddf_x += 2;
        f += ddf_x;

        if (x < (y + 1)) {
            if (corner & 1) {
                btprnt_draw_vline(reg,
                                  x0 + x, y0 - y,
                                  2 * y + delta, clr);
            }

            if (corner & 2) {
                btprnt_draw_vline(reg,
                                  x0 - x, y0 - y,
                                  2 * y + delta, clr);
            }
        }
        if (y != py) {
            if (corner & 1) {
                btprnt_draw_vline(reg,
                                  x0 + py, y0 - px,
                                  2 * px + delta, clr);
            }

            if (corner & 2) {
                btprnt_draw_vline(reg,
                                  x0 - py, y0 - px,
                                  2 * px + delta, clr);
            }

            py = y;
        }
        px = x;
    }
}

void btprnt_draw_roundrect_filled(btprnt_region *reg,
                                  int x, int y,
                                  int w, int h,
                                  int r,
                                  int clr)
{
  int max_radius = ((w < h) ? w : h) / 2;
  if (r > max_radius)
    r = max_radius;
  btprnt_draw_rect_filled(reg, x + r, y, w - 2 * r, h, clr);
  quadcirc_filled(reg,
                  x + w - r - 1, y + r,
                  r, 1, h - 2 * r - 1, clr);
  quadcirc_filled(reg,
                  x + r, y + r,
                  r, 2, h - 2 * r - 1, clr);
}
#line 2170 "btprnt.org"
#line 2053 "btprnt.org"
static int signum(int x)
{
    if (x < 0) return -1;
    if (x > 0) return 1;
    else return 0;
}


static void bresenham_fill(btprnt_region *r,
                           int v1x, int v1y,
                           int v2x, int v2y,
                           int v3x, int v3y,
                           int c)
{
    int vtmp1x;
    int vtmp1y;
    int vtmp2x;
    int vtmp2y;

    int changed1;
    int changed2;

    int dx1;
    int dy1;
    int dx2;
    int dy2;

    int signx1;
    int signx2;

    int signy1;
    int signy2;

    int e1;
    int e2;

    int i;

    vtmp1x = v1x;
    vtmp1y = v1y;

    vtmp2x = v1x;
    vtmp2y = v1y;

    changed1 = 0;
    changed2 = 0;

    dx1 = abs(v2x - v1x);
    dy1 = abs(v2y - v1y);

    dx2 = abs(v3x - v1x);
    dy2 = abs(v3y - v1y);

    signx1 = signum(v2x - v1x);
    signx2 = signum(v3x - v1x);

    signy1 = signum(v2y - v1y);
    signy2 = signum(v3y - v1y);

    if (dy1 > dx1) {
        int tmp;
        tmp = dx1;
        dx1 = dy1;
        dy1 = tmp;
        changed1 = 1;
    }

    if (dy2 > dx2) {
        int tmp;
        tmp = dx2;
        dx2 = dy2;
        dy2 = tmp;
        changed2 = 1;
    }

    e1 = 2 * dy1 - dx1;
    e2 = 2 * dy2 - dx2;

    for(i = 0; i <= dx1; i++) {
        btprnt_draw_line(r, vtmp1x, vtmp1y, vtmp2x, vtmp2y, c);

        while (e1 >= 0) {
            if (changed1) vtmp1x += signx1;
            else vtmp1y += signy1;

            e1 = e1 - 2 * dx1;
        }

        if (changed1) vtmp1y += signy1;
        else vtmp1x += signx1;

        e1 = e1 + 2 * dy1;

        while (vtmp2y != vtmp1y) {
            while (e2 >= 0) {
                if (changed2) vtmp2x += signx2;
                else vtmp2y += signy2;

                e2 = e2 - 2 * dx2;
            }

            if (changed2) vtmp2y += signy2;
            else vtmp2x += signx2;

            e2 = e2 + 2 * dy2;
        }
    }

}
#line 2193 "btprnt.org"

void btprnt_draw_triangle(btprnt_region *r,
                          int v1x, int v1y,
                          int v2x, int v2y,
                          int v3x, int v3y,
                          int c)
{
#line 2006 "btprnt.org"
{
    int tmpx;
    int tmpy;

    if (v1y > v2y) {
        tmpy = v1y;
        tmpx = v1x;

        v1y = v2y;
        v1x = v2x;

        v2y = tmpy;
        v2x = tmpx;
    }

    if (v1y > v3y) {
        tmpy = v1y;
        tmpx = v1x;

        v1y = v3y;
        v1x = v3x;

        v3y = tmpy;
        v3x = tmpx;
    }

    if (v2y > v3y) {
        tmpy = v2y;
        tmpx = v2x;

        v2y = v3y;
        v2x = v3x;

        v3y = tmpy;
        v3x = tmpx;
    }
}
#line 2201 "btprnt.org"
    if (v2y == v3y) {
        bresenham_fill(r,
                       v1x, v1y,
                       v2x, v2y,
                       v3x, v3y,
                       c);
    } if (v1y == v2y) {
        bresenham_fill(r,
                       v3x, v3y,
                       v1x, v1y,
                       v2x, v2y,
                       c);
    } else {
#line 2170 "btprnt.org"
int v4x, v4y;

v4x = (v1x +
    ((float)(v2y - v1y)/(v3y - v1y)) *
    (v3x - v1x));
v4y = v2y;

bresenham_fill(r,
               v1x, v1y,
               v2x, v2y,
               v4x, v4y,
               c);

bresenham_fill(r,
               v3x, v3y,
               v2x, v2y,
               v4x, v4y,
               c);
#line 2215 "btprnt.org"
    }

}
#line 2239 "btprnt.org"
void btprnt_draw_arrow(btprnt_region *r,
                       int start_x, int start_y,
                       int end_x, int end_y,
                       int arrow_start,
                       int arrow_end,
                       int draw_line,
                       int c)
{
    int sz;
    float angle;
    float off;
    int ptx[2];
    int pty[2];
    int dx;
    int dy;
    int dir;

    if (start_x > end_x) {
        dir = -1;
    } else {
        dir = 1;
    }

    sz = 9;

    dx = end_x - start_x;
    dy = end_y - start_y;

    off = asin(dx / sqrt(dx*dx + dy*dy));

    if (off < 0) {
        dir *= -1;
    }

    angle = 30;
    /* convert to radians */
    angle *= M_PI / 180.0;

    if (draw_line) {
        btprnt_draw_line(r,
                        start_x, start_y,
                        end_x, end_y, c);
    }

    if (arrow_start) {
        ptx[0] = start_x + dir * sz * sin(angle + off);
        pty[0] = start_y + dir * sz * cos(angle + off);

        ptx[1] = start_x + dir * sz * sin(off - angle);
        pty[1] = start_y + dir * sz * cos(off - angle);

        btprnt_draw_triangle(r,
                            start_x, start_y,
                            ptx[0], pty[0],
                            ptx[1], pty[1],
                            c);
    }

    if (arrow_end) {
        ptx[0] = end_x + -dir * sz * sin(angle + off);
        pty[0] = end_y + -dir * sz * cos(angle + off);

        ptx[1] = end_x + -dir * sz * sin(off - angle);
        pty[1] = end_y + -dir * sz * cos(off - angle);

        btprnt_draw_triangle(r,
                            end_x, end_y,
                            ptx[0], pty[0],
                            ptx[1], pty[1],
                            c);

    }
}
#line 2320 "btprnt.org"
#line 2375 "btprnt.org"
static void bezierseg(btprnt_region *r,
                      int x0, int y0,
                      int x1, int y1,
                      int x2, int y2,
                      int c)
{
    int sx, sy;
    long xx, yy, xy;
    double dx, dy, err, cur;
    int rc;

    sx = x2-x1;
    sy = y2-y1;
    xx = x0-x1;
    yy = y0-y1;

    cur = xx*sy-yy*sx;

    rc = xx*sx <= 0 && yy*sy <= 0;

    if (!rc) return;

    if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy) {
        x2 = x0;
        x0 = sx+x1;
        y2 = y0;
        y0 = sy+y1;
        cur = -cur;
    }

    if (cur != 0) {
        xx += sx;
        xx *= sx = x0 < x2 ? 1 : -1;

        yy += sy;
        yy *= sy = y0 < y2 ? 1 : -1;

        xy = 2*xx*yy;
        xx *= xx;
        yy *= yy;

        if (cur*sx*sy < 0) {
            xx = -xx;
            yy = -yy;
            xy = -xy;
            cur = -cur;
        }

        dx = 4.0*sy*cur*(x1-x0)+xx-xy;
        dy = 4.0*sx*cur*(y0-y1)+yy-xy;

        xx += xx;
        yy += yy;
        err = dx+dy+xy;

        do {
            btprnt_region_draw(r, x0, y0, c);

            if (x0 == x2 && y0 == y2) return;

            y1 = 2*err < dx;

            if (2*err > dy) {
                x0 += sx;
                dx -= xy;
                err += dy += yy;
            }

            if (y1) {
                y0 += sy;
                dy -= xy;
                err += dx += xx;
            }
        } while (dy < dx );
    }

    btprnt_draw_line(r, x0, y0, x2, y2, c);
}
#line 2330 "btprnt.org"
void btprnt_draw_bezier(btprnt_region *reg,
                        int x0, int y0,
                        int x1, int y1,
                        int x2, int y2,
                        int c)
{
    int x, y;
    double t, r;

    x = x0-x1;
    y = y0-y1;
    t = x0-2*x1+x2;

    if ((long)x*(x2-x1) > 0) {
        if ((long)y*(y2-y1) > 0)
            if (fabs((y0-2*y1+y2)/t*x) > abs(y)) {
                x0 = x2; x2 = x+x1; y0 = y2; y2 = y+y1;
            }
        t = (x0-x1)/t;
        r = (1-t)*((1-t)*y0+2.0*t*y1)+t*t*y2;
        t = (x0*x2-x1*x1)*t/(x0-x1);
        x = floor(t+0.5); y = floor(r+0.5);
        r = (y1-y0)*(t-x0)/(x1-x0)+y0;
        bezierseg(reg, x0, y0, x, floor(r+0.5), x, y, c);
        r = (y1-y2)*(t-x2)/(x1-x2)+y2;
        x0 = x1 = x; y0 = y; y1 = floor(r+0.5);
    }

    if ((long)(y0-y1)*(y2-y1) > 0) {
        t = y0-2*y1+y2; t = (y0-y1)/t;
        r = (1-t)*((1-t)*x0+2.0*t*x1)+t*t*x2;
        t = (y0*y2-y1*y1)*t/(y0-y1);
        x = floor(r+0.5); y = floor(t+0.5);
        r = (x1-x0)*(t-y0)/(y1-y0)+x0;
        bezierseg(reg, x0, y0, floor(r+0.5), y, x, y, c);
        r = (x1-x2)*(t-y2)/(y1-y2)+x2;
        x0 = x; x1 = floor(r+0.5); y0 = y1 = y;
    }

    bezierseg(reg, x0, y0, x1, y1, x2, y2, c);
}
#line 2474 "btprnt.org"
void btprnt_draw_bezier_arrow(btprnt_region *r,
                              int start_x, int start_y,
                              int end_x, int end_y,
                              int ctrl_x, int ctrl_y,
                              int arrow_start,
                              int arrow_end,
                              int c)
{
    btprnt_draw_arrow(r,
                      start_x, start_y,
                      ctrl_x, ctrl_y,
                      1, 0, 0, c);

    btprnt_draw_arrow(r,
                      end_x, end_y,
                      ctrl_x, ctrl_y,
                      1, 0, 0, c);

    btprnt_draw_bezier(r,
                       start_x, start_y,
                       ctrl_x, ctrl_y,
                       end_x, end_y,
                       c);
}
#line 2519 "btprnt.org"
void btprnt_draw_tinytile(btprnt_region *r,
                          int xpos,
                          int ypos,
                          int b0,
                          int b1,
                          int b2)
{
    int x, y;
    b0 &= 0xff;
    b1 &= 0xff;
    b2 &= 0xff;

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            unsigned char pat;
            int xoff, yoff;

            if (y < 2) {
                pat = (b1 >> (4 * y)) & (1 << x);
            } else {
                pat = (b2 >> (4 * (y - 2))) & (1 << x);
            }

            pat = (pat ? (b0>>4) : b0) & 0xf;

            xoff = (x<<1) + xpos;
            yoff = (y<<1) + ypos;

            btprnt_region_draw(r,
                               xoff, yoff,
                               pat & 1);
            btprnt_region_draw(r,
                               xoff + 1, yoff,
                               (pat & 2) >> 1);
            btprnt_region_draw(r,
                               xoff, yoff + 1,
                               (pat & 4) >> 2);
            btprnt_region_draw(r,
                               xoff + 1, yoff + 1,
                               (pat & 8) >> 3);
        }
    }
}
#line 2595 "btprnt.org"
void btprnt_layout_outline(btprnt_region *r, int c)
{
    btprnt_region o;
    o = *r;
    o.x--;
    o.y--;
    o.w += 2;
    o.h += 2;
    btprnt_draw_rect(&o, 0, 0, o.w, o.h, c);
}
#line 2621 "btprnt.org"
int btprnt_layout_centerbox(btprnt_region *r,
                            int w, int h,
                            btprnt_region *s)
{
    int vmargin;
    int hmargin;

    hmargin = (r->w - w) / 2;
    vmargin = (r->h - h) / 2;


    if (hmargin < 0 || vmargin < 0) {
        s->c = r->c;
        s->x = 0;
        s->y = 0;
        s->w = 0;
        s->h = 0;
        return BTPRNT_NOT_OK;
    }

    s->c = r->c;
    s->x = r->x + hmargin;
    s->y = r->y + vmargin;
    s->w = w;
    s->h = h;

    return BTPRNT_OK;
}
#line 2663 "btprnt.org"
int btprnt_layout_border(btprnt_region *r,
                         int border,
                         btprnt_region *s)
{
    if (r->w < (2 * border) || r->h < (2 * border)) {
        return BTPRNT_NOT_OK;
    }

    s->c = r->c;
    s->x = r->x + border;
    s->y = r->y + border;
    s->w = r->w - 2*border;
    s->h = r->h - 2*border;

    return BTPRNT_OK;
}
#line 2696 "btprnt.org"
int btprnt_layout_grid(btprnt_region *r,
                       int nrows,
                       int ncols,
                       int row,
                       int col,
                       btprnt_region *s)
{
    int hspace;
    int vspace;
    int err;

    hspace = r->w / nrows;
    vspace = r->h / ncols;

    err = hspace <= 0 || vspace <= 0;
    err = err || row >= nrows || col >= ncols;

    if (err) {
        s->c = r->c;
        s->x = 0;
        s->y = 0;
        s->w = 0;
        s->h = 0;
        return BTPRNT_NOT_OK;
    }

    s->c = r->c;
    s->x = r->x + hspace * row;
    s->y = r->y + vspace * col;
    s->w = hspace;
    s->h = vspace;

    if (row == (nrows - 1)) s->w = r->w - (hspace * row);
    if (col == (ncols - 1)) s->h = r->h - (vspace * col);

    return BTPRNT_OK;
}
#line 2752 "btprnt.org"
void btprnt_invert(btprnt_region *r,
                   int xoff, int yoff,
                   int w, int h)
{
    int x, y;
    /* TODO: add bounds checking */
    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y ++) {
            int s;
            int xp, yp;
            xp = x + xoff;
            yp = y + yoff;
            s = btprnt_region_read(r, xp, yp);

            if (s) {
                btprnt_region_draw(r, xp, yp, 0);
            } else {
                btprnt_region_draw(r, xp, yp, 1);
            }
        }
    }

}
#line 2792 "btprnt.org"
void btprnt_bitrow(btprnt_region *reg,
                   int x, int y,
                   int nbits,
                   unsigned short pat)
{
    int i;
    if (nbits < 0) return;
    if (nbits > 16) nbits = 16;

    for (i = 0; i < nbits; i++) {
        btprnt_region_draw(reg,
                           x + i, y,
                           (pat & (1 << i)) >> i);
    }
}
#line 24 "btprnt.org"
#endif
#endif
