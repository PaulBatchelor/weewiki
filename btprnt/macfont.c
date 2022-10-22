#line 21 "macfont.org"
#include <stdint.h>
#include <string.h>
#include "btprnt/btprnt.h"
#include "macfont.h"
#line 56 "macfont.org"
#line 40 "macfont.org"
#define BIGINT(n) (((n & 0xFF) << 8) | n >> 8)
#line 48 "macfont.org"
#define MKINT(d, pos) ((d[pos] << 8) + d[pos + 1])
#line 56 "macfont.org"
#line 56 "macfont.org"
#define FONTTYPE(d) (MKINT(d, 0))
#define FIRSTCHAR(d) (MKINT(d, 2))
#define LASTCHAR(d) (MKINT(d, 4))
#define WIDTHMAX(d) ((int16_t)MKINT(d, 6))
#define KERNMAX(d) ((int16_t)MKINT(d, 8))
#define NDESCENT(d) ((int16_t)MKINT(d, 10))
#define RECTWIDTH(d) ((int16_t)MKINT(d, 12))
#define RECTHEIGHT(d) ((int16_t)MKINT(d, 14))
#define OWTLOC(d) ((int16_t)MKINT(d, 16))
#define ASCENT(d) ((int16_t)MKINT(d, 18))
#define DESCENT(d) ((int16_t)MKINT(d, 20))
#define LEADING(d) ((int16_t)MKINT(d, 22))
#define ROWWORDS(d) ((int16_t)MKINT(d, 24))
#define BITMAPS(d) (&d[26])
#line 56 "macfont.org"
#line 21 "macfont.org"
#line 103 "macfont.org"
int macfont_glyph_lowlevel(btprnt_region *r,
                           uint8_t *font,
                           int xpos,
                           int ypos,
                           char c)
{
    uint8_t *bitmaps;
    uint16_t *loctable;
    uint16_t *owtable;
    uint16_t off;
    uint16_t nchars;
    uint16_t ow;
    uint16_t width;
    uint16_t offset;
    uint16_t pos;
    uint16_t nextloc;
    uint16_t loc;
    uint16_t stride;
    uint16_t x, y;
    uint16_t w, h;
    uint16_t kern;

    bitmaps = BITMAPS(font);
    off = ROWWORDS(font) * RECTHEIGHT(font);

    loctable = (uint16_t *) (bitmaps + (2 * off));

    nchars = LASTCHAR(font) - FIRSTCHAR(font) + 1;

    owtable = loctable + (nchars + 2);

    pos = c - FIRSTCHAR(font);
    ow = owtable[pos];
    ow = ((ow & 0xFF) << 8) | ow >> 8;

    if (ow == 0xFFFF) return 0;

    offset = (ow >> 8) & 0x00FF;
    width = ow & 0x00FF;

    loc = BIGINT(loctable[pos]);
    nextloc = BIGINT(loctable[pos + 1]);

    stride = ROWWORDS(font) * 2;

    w = nextloc - loc;
    h = RECTHEIGHT(font);
    kern = offset + KERNMAX(font);

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            int pos = loc + x;
            uint8_t byte = bitmaps[(stride * y) + (pos / 8)];
            uint8_t val = (byte >> (7 - (pos % 8))) & 1;
            btprnt_region_draw(r, xpos + x + kern, ypos + y, val);
        }
    }

    return width;
}
#line 197 "macfont.org"
void macfont_info_init(macfont_info *info, uint8_t *font)
{
#line 226 "macfont.org"
#line 216 "macfont.org"
info->off = ROWWORDS(font) * RECTHEIGHT(font);
#line 221 "macfont.org"
info->bitmaps = BITMAPS(font);
#line 232 "macfont.org"
info->loctable =
    (uint16_t *) (info->bitmaps + (2 * info->off));
#line 239 "macfont.org"
#line 255 "macfont.org"
info->nchars = LASTCHAR(font) - FIRSTCHAR(font) + 1;
#line 245 "macfont.org"
info->owtable = info->loctable + (info->nchars + 2);
#line 232 "macfont.org"
#line 265 "macfont.org"
info->stride = ROWWORDS(font) * 2;
#line 275 "macfont.org"
info->rectheight = RECTHEIGHT(font);
#line 285 "macfont.org"
info->kernmax = KERNMAX(font);
#line 295 "macfont.org"
info->firstchar = FIRSTCHAR(font);
#line 305 "macfont.org"
info->fontheight = ASCENT(font) - DESCENT(font);
#line 316 "macfont.org"
info->ascent = ASCENT(font);
info->descent = DESCENT(font);
#line 200 "macfont.org"
}
#line 328 "macfont.org"
int macfont_info_fontheight(macfont_info *info)
{
    return info->fontheight;
}
#line 343 "macfont.org"
int macfont_info_rectheight(macfont_info *info)
{
    return info->rectheight;
}
#line 359 "macfont.org"
int macfont_info_descent(macfont_info *info)
{
    return info->descent;
}
#line 380 "macfont.org"
int macfont_glyph(btprnt_region *r,
                  macfont_info *info,
                  int xpos,
                  int ypos,
                  char c,
                  int color)
{
    uint16_t ow;
    uint16_t width;
    uint16_t offset;
    uint16_t pos;
    uint16_t nextloc;
    uint16_t loc;
    uint16_t x, y;
    uint16_t w, h;
    uint16_t kern;

    pos = c - info->firstchar;
    ow = info->owtable[pos];
    ow = ((ow & 0xFF) << 8) | ow >> 8;

    if (ow == 0xFFFF) return 0;

    offset = (ow >> 8) & 0x00FF;
    width = ow & 0x00FF;

    loc = BIGINT(info->loctable[pos]);
    nextloc = BIGINT(info->loctable[pos + 1]);

    w = nextloc - loc;
    h = info->rectheight;
    kern = offset + info->kernmax;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            int pos = loc + x;
            uint8_t byte =
                info->bitmaps[(info->stride * y) + (pos / 8)];
            uint8_t val = (byte >> (7 - (pos % 8))) & 1;
            if (val) {
                btprnt_region_draw(r,
                                   xpos + x + kern,
                                   ypos + y,
                                   color);
            }
        }
    }

    return width;
}
#line 436 "macfont.org"
#line 498 "macfont.org"
static int get_charwidth(macfont_info *fnt, char c)
{
    uint16_t pos;
    uint16_t width;
    uint16_t ow;

    pos = c - fnt->firstchar;
    ow = fnt->owtable[pos];
    ow = ((ow & 0xFF) << 8) | ow >> 8;
    width = ow & 0x00FF;

    return (int)width;
}

static int get_wordlen(macfont_info *fnt, const char *str, int sz)
{
    int wordlen;
    int n;

    wordlen = 0;

    for (n = 0; n < sz; n++) {
        wordlen += get_charwidth(fnt, str[n]);
    }

    return wordlen;
}

static void write_word(btprnt_region *reg,
                       macfont_info *fnt,
                       const char *str,
                       int nchars,
                       int *xp,
                       int *yp,
                       int color)
{
    int wordlen;
    int i;
    int xpos, ypos;

    xpos = *xp;
    ypos = *yp;

    wordlen = get_wordlen(fnt, str, nchars);

    if ((xpos + wordlen) > reg->w) {
        if (wordlen < reg->w) {
            xpos = 0;
            ypos += fnt->fontheight * 1.5;
        }
    }

    for (i = 0; i < nchars; i++) {
        char c;
        int cw;

        c = str[i];
        cw = get_charwidth(fnt, c);

        if ((xpos + cw) > reg->w || c == '\n') {
            xpos = 0;
            ypos += fnt->fontheight * 1.5;
        }

        if (c != '\n') {
            xpos +=
                macfont_glyph(reg, fnt,
                            xpos,
                            ypos,
                            c,
                            color);
        }
    }

    *xp = xpos;
    *yp = ypos;
}
#line 447 "macfont.org"
void macfont_textbox(btprnt_region *reg,
                     macfont_info *fnt,
                     int offx, int offy,
                     const char *str,
                     int color,
                     int *nx, int *ny)
{
    int len;
    int n;
    int start;
    int nchars;
    int xpos;
    int ypos;

    len = strlen(str);
    start = 0;
    nchars = 0;
    xpos = offx;
    ypos = offy;
    for (n = 0; n < len; n++) {
        nchars++;
        if (str[n] == ' ' || str[n] == '\n') {
            write_word(reg, fnt,
                       &str[start], nchars,
                       &xpos, &ypos,
                       color);
            start = n + 1;
            nchars = 0;
        }
    }

    if (nchars >= 0) {
        write_word(reg, fnt,
                    &str[start], nchars,
                    &xpos, &ypos,
                    color);
    }

    if (nx != NULL) *nx = xpos;
    if (ny != NULL) *ny = ypos;
}
#line 588 "macfont.org"
int macfont_line_width(macfont_info *fnt,
                       const char *str,
                       int nchars)
{
    int lw;
    int n;

    lw = 0;

    for (n = 0; n < nchars; n++) {
        lw += get_charwidth(fnt, str[n]);
    }

    return lw;
}
#line 21 "macfont.org"
