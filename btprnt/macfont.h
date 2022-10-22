#line 11 "macfont.org"
#ifndef MACFONT_H
#define MACFONT_H
#line 181 "macfont.org"
typedef struct {
#line 206 "macfont.org"
uint8_t *bitmaps;
#line 211 "macfont.org"
uint16_t off;
#line 226 "macfont.org"
uint16_t *loctable;
#line 239 "macfont.org"
uint16_t *owtable;
#line 250 "macfont.org"
uint16_t nchars;
#line 260 "macfont.org"
uint16_t stride;
#line 270 "macfont.org"
uint16_t rectheight;
#line 280 "macfont.org"
int16_t kernmax;
#line 290 "macfont.org"
uint16_t firstchar;
#line 300 "macfont.org"
uint16_t fontheight;
#line 310 "macfont.org"
uint16_t descent;
uint16_t ascent;
#line 183 "macfont.org"
} macfont_info;
#line 11 "macfont.org"
#line 169 "macfont.org"
#define MF_CHAR_COMMAND 0x11
#define MF_CHAR_DOT 0x12
#define MF_CHAR_CHECK 0x13
#define MF_CHAR_APPLE 0x14
#line 11 "macfont.org"
#line 91 "macfont.org"
int macfont_glyph_lowlevel(btprnt_region *r,
                           uint8_t *font,
                           int xpos,
                           int ypos,
                           char c);
#line 192 "macfont.org"
void macfont_info_init(macfont_info *info, uint8_t *font);
#line 324 "macfont.org"
int macfont_info_fontheight(macfont_info *info);
#line 339 "macfont.org"
int macfont_info_rectheight(macfont_info *info);
#line 355 "macfont.org"
int macfont_info_descent(macfont_info *info);
#line 370 "macfont.org"
int macfont_glyph(btprnt_region *r,
                  macfont_info *info,
                  int xpos,
                  int ypos,
                  char c,
                  int color);
#line 436 "macfont.org"
void macfont_textbox(btprnt_region *reg,
                     macfont_info *fnt,
                     int offx, int offy,
                     const char *str,
                     int color,
                     int *nx, int *ny);
#line 582 "macfont.org"
int macfont_line_width(macfont_info *fnt,
                       const char *str,
                       int nchars);
#line 16 "macfont.org"
#endif
