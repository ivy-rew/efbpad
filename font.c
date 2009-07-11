#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include "util.h"

#define FONTFACE	"/usr/lib/X11/fonts/TTF/DejaVuSansMono.ttf"
#define FONTSIZE	10
#define DPI		192
#define MAXDOTS		(1 << 10)
#define WIDTHDIFF	1

static FT_Library library;
static FT_Face face;
static int rows, cols;

void font_init(void)
{
	FT_Init_FreeType(&library);
	FT_New_Face(library, FONTFACE, 0, &face);
	FT_Set_Char_Size(face, 0, FONTSIZE << 6, DPI, DPI);
	rows = face->size->metrics.height >> 6;
	cols = (face->size->metrics.max_advance >> 6) + WIDTHDIFF;
}

unsigned char *font_bitmap(int c, int bold)
{
	static unsigned char bits[MAXDOTS];
	int sr, sc, er, ec;
	int i;
	if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		return NULL;
	sr = rows + (face->size->metrics.descender >> 6) -
		(face->glyph->metrics.horiBearingY >> 6);
	sc = face->glyph->metrics.horiBearingX >> 6;
	er = MIN(rows, sr + face->glyph->bitmap.rows);
	ec = MIN(cols, sc + face->glyph->bitmap.width);
	memset(bits, 0, sr * cols);
	for (i = sr; i < er; i++) {
		unsigned char *rowaddr = face->glyph->bitmap.buffer +
					(i - sr) * face->glyph->bitmap.pitch;
		memset(&bits[i * cols], 0, sc);
		memcpy(&bits[i * cols + sc], rowaddr, ec - sc);
		memset(&bits[i * cols + ec], 0, cols - ec);
	}
	memset(&bits[er * cols], 0, (rows - er) * cols);
	return bits;
}

void font_free(void)
{
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

int font_rows(void)
{
	return rows;
}

int font_cols(void)
{
	return cols;
}