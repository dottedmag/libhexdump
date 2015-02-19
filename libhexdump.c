//
// Copyright (c) 2015 Mikhail Gusarov <dottedmag@dottedmag.net>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.
//

#include <hexdump.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

static void print_chunk(FILE *fp, uint64_t offset, const uint8_t *mem, int size)
{
    fprintf(fp, "%08" PRIx64 " ", offset);
    for (int i = 0; i < size; ++i)
        fprintf(fp, "%*s %02x", i == 8, "", mem[i]);
    fprintf(fp, "%*s|", 51 - 3*size - (size>=9), "");
    for (int i = 0; i < size; ++i)
        putc(mem[i] >= ' ' && mem[i] <= '~' ? mem[i] : '.', fp);
    fputs("|\n", fp);
}

static bool empty_chunk(const uint8_t *mem, int size)
{
    return size == 16 && !memcmp(mem, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

void hexdump(FILE *fp, const uint8_t *mem, uint64_t size)
{
    int num_empty = 0;

    for (uint64_t off = 0; off < size; off += 16)
    {
        const uint8_t *chunk_mem = mem + off;
        int chunk_size = (size - off > 16) ? 16 : size - off;

        if (empty_chunk(chunk_mem, chunk_size))
            num_empty++;
        else
            num_empty = 0;

        if (num_empty < 2)
            print_chunk(fp, off, chunk_mem, chunk_size);
        if (num_empty == 2)
            fputs("*\n", fp);
    }
    fprintf(fp, "%08" PRIx64 "\n", size);
}
