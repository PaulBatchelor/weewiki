#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "miniz/miniz.h"
#include "btprnt.h"

static unsigned long crc_table[256];

static int crc_table_computed = 0;

static
char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length);

typedef struct {
    unsigned char *buf;
    size_t sz;
    size_t pos;
} bufwrite;

static size_t bufwrite_write(bufwrite *buf,
                             const void *ptr,
                             size_t sz,
                             size_t nmemb)
{
    size_t wsz;
    const unsigned char *bytes;
    size_t i;

    wsz = sz*nmemb;

    if (buf->pos + wsz >= buf->sz) return 0;

    bytes = ptr;

    for (i = 0; i < wsz; i++) {
        buf->buf[buf->pos] = bytes[i];
        buf->pos++;
    }

    return wsz;
}

static void make_crc_table(void)
{
    unsigned long c;
    int n, k;

    for (n = 0; n < 256; n++) {
        c = (unsigned long) n;
        for (k = 0; k < 8; k++) {
            if (c & 1) {
                c = 0xedb88320L ^ (c >> 1);
            } else {
                c = c >> 1;
            }
        }
        crc_table[n] = c;
    }

    crc_table_computed = 1;
}

static unsigned long update_crc(unsigned long crc,
                                unsigned char *buf,
                                int len)
{
    unsigned long c;
    int n;

    c = crc;

    if (!crc_table_computed) {
        make_crc_table();
    }

    for (n = 0; n < len; n++) {
        c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }

    return c;
}

unsigned long crc(unsigned char *buf, int len)
{
    return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;
}

void draw(btprnt_region *r)
{
    int x, y;
    for (y = 0; y < 10; y++) {
        for (x = 0; x < 10; x++) {
            btprnt_draw_rect_filled(r,
                                    x*18, y*18,
                                    14, 14,
                                    1);
        }
    }
}

void write_long(bufwrite *buf, unsigned long x)
{
    uint8_t b[4];
    int i;

    for (i = 3; i >= 0; i--) {
        b[i] = x & 0xff;
        x >>= 8;
    }

    bufwrite_write(buf, b, 1, 4);
}

static void write_chunk(bufwrite *buf,
                        unsigned long len,
                        const char *type,
                        unsigned char *data)
{
    unsigned long x;

    /* part 1: length */
    write_long(buf, len);
    /* part 2: type */
    bufwrite_write(buf, type, 1, 4);
    /* part 3: data */
    bufwrite_write(buf, data, 1, len);
    /* part 4: CRC */

    x = 0xffffffffL;
    x = update_crc(x, (unsigned char *)type, 4);
    x = update_crc(x, data, len);
    x ^= 0xffffffffL;

    write_long(buf, x);
}

static void write_header(bufwrite *buf, uint32_t w, uint32_t h)
{
    uint8_t data[13];
    uint8_t b[4];
    uint32_t x;
    int pos, i;

    pos = 0;

    /* width (4 bytes) */

    x = w;
    for (i = 3; i >= 0; i--) {
        b[i] = x & 0xff;
        x >>= 8;
    }
    for (i = 0; i < 4; i++) {
        data[pos] = b[i];
        pos++;
    }

    /* height (4 bytes) */

    x = h;
    for (i = 3; i >= 0; i--) {
        b[i] = x & 0xff;
        x >>= 8;
    }

    for (i = 0; i < 4; i++) {
        data[pos] = b[i];
        pos++;
    }

    /* bit depth 1 bytes, set to be 1 bit */
    b[0] = 1;
    data[pos] = b[0];
    pos++;

    /* color type: grayscale (0) */
    b[0] = 0;
    data[pos] = b[0];
    pos++;

    /* compression method: default DEFLATE (0) */
    b[0] = 0;
    data[pos] = b[0];
    pos++;

    /* filter method: 0 (default) */
    b[0] = 0;
    data[pos] = b[0];
    pos++;

    /* interlace: no interlace (0) */
    b[0] = 0;
    data[pos] = b[0];
    pos++;

    write_chunk(buf, 13, "IHDR", data);
}

static void write_data(bufwrite *writer, btprnt_buf *buf)
{
    uint8_t *data;
    uint8_t *zdata;
    uint32_t sz;
    long unsigned int zsz;
    int x, y;
    int w, h;
    int stride;
    uint32_t pos;
    int bpos;
    z_stream defstream;

    h = btprnt_buf_height(buf);
    w = btprnt_buf_width(buf);

    stride = w / 8;

    if ((stride * 8) < w) stride++;

    sz = (stride + 1) * h;

    zdata = calloc(1, sz);
    data = calloc(1, sz);
    zsz = sz;

    pos = 0;

    for (y = 0; y < h; y++) {
        uint8_t byte;
        uint8_t bit;

        bpos = -1;
        byte = 0;
        bit = 0;

        data[pos] = 0x00;
        pos++;

        for (x = 0; x < w; x++) {
            bit = btprnt_buf_read(buf, x, y);
            bpos++;

            if (!bit) {
                byte |= 1 << (7 - bpos);
            }

            if (bpos == 7) {
                data[pos] = byte;
                pos++;
                byte = 0;
                bpos = -1;
            }
        }

        if (bpos >= 0) {
            data[pos] = byte;
            pos++;
            byte = 0;
            bpos = -1;
        }
    }

    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    defstream.avail_in = sz;
    defstream.next_in = data;
    defstream.avail_out = sz;
    defstream.next_out = zdata;

    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);

    zsz = sz - defstream.avail_out;

    write_chunk(writer, zsz, "IDAT", zdata);

    deflateEnd(&defstream);
    free(zdata);
    free(data);
}

static void write_end(bufwrite *buf)
{
    write_chunk(buf, 0, "IEND", NULL);
}

void btprnt_write_png(btprnt *bp, char **out, size_t *sz)
{
    bufwrite writer;
    char *b64;
    size_t b64_sz;

    unsigned char signature[] = {
        137, 80, 78, 71, 13, 10, 26, 10
    };

    btprnt_buf *buf;
    int w, h;
    int stride;
    int maxsz;

    buf = btprnt_buf_get(bp);
    w = btprnt_buf_width(buf);
    h = btprnt_buf_height(buf);

    /* max possible size is signature plus WxH bits */
    stride = w/8;
    if ((stride * 8) < w) stride++;
    maxsz = (stride * h) + 8;

    writer.sz = maxsz;
    writer.pos = 0;
    writer.buf = malloc(maxsz);

    /* write PNG signature */
    bufwrite_write(&writer, signature, 1, 8);

    write_header(&writer, w, h);

    /* write IDAT chunk (image data) */

    write_data(&writer, buf);

    /* write IEND chunk */

    write_end(&writer);

    b64_sz = 0;
    b64 = base64_encode(writer.buf, writer.pos, &b64_sz);
    *out = b64;
    *sz = b64_sz;

    free(writer.buf);
}

static char encoding_table[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

static int mod_table[] = {0, 2, 1};

static
char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length)
{

    char *encoded_data;
    int i, j;

    *output_length = 4 * ((input_length + 2) / 3);

    encoded_data = malloc(*output_length);
    if (encoded_data == NULL) return NULL;

    for (i = 0, j = 0; i < input_length;) {
        uint32_t octet_a =
            i < input_length ?  (unsigned char)data[i++] : 0;
        uint32_t octet_b =
            i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c =
            i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple =
            (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] =
            encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] =
            encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] =
            encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] =
            encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}
