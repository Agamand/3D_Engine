


/*
 * bmp.c -- bmp texture loader
 * last modification: dec. 15, 2005
 *
 * Copyright (c) 2005 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * gcc -Wall -ansi -L/usr/X11R6/lib -lGL -lGLU -lglut bmp.c -o bmp
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glut.h>

#ifndef BMPLOADER_H
#define BMPLOADER_H

/* OpenGL texture info */
typedef struct
{
  GLsizei width;
  GLsizei height;

  GLenum format;
  GLint	internalFormat;
  GLuint id;

  GLubyte *texels;

} gl_texture_t;


#pragma pack(push, 2)
/* bitmap file header */
typedef struct
{
  unsigned char bfType[2];      /* magic number "BM" */
  unsigned int bfSize;          /* file size */
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned int bfOffBits;       /* offset to image data */

} bmp_file_header_t;
#pragma pack(pop)


/* bitmap info header */
typedef struct
{
  unsigned int biSize;          /* size of bitmap info header */
  int biWidth;                  /* image with */
  int biHeight;                 /* image height */
  unsigned short biPlanes;      /* must be equal to 1 */
  unsigned short biBitCount;    /* bits per pixels */
  unsigned int biCompression;   /* compression type */
  unsigned int biSizeImage;     /* size of pixel data */
  int biXPelsPerMeter;          /* pixels per meter on x-axis */
  int biYPelsPerMeter;          /* pixels per meter on y-axis */
  unsigned int biClrUsed;       /* number of used colors */
  unsigned int biClrImportant;  /* number of important colors */

} bmp_info_header_t;

/* bitmap core header */
typedef struct
{
  unsigned int bcSize;           /* size of bitmap core header */
  unsigned short bcWidth;        /* image with */
  unsigned short bcHeight;       /* image height */
  unsigned short bcPlanes;       /* must be equal to 1 */
  unsigned short bcBitCount;     /* bits per pixel */

} bmp_core_header_t;


/* bitmap core info */
typedef struct
{
  bmp_core_header_t bmciHeader;
  unsigned char bmciColors[3];

} bmp_core_info_t;


/* OS-style type */
typedef enum
{
  BMP_WIN,
  BMP_OS2,

} os_type_e;


enum
  {
    /* BMP compression type constants */
    BI_RGB          = 0,
    BI_RLE8         = 1,
    BI_RLE4         = 2,
    BI_BITFIELDS    = 3,

    /* RLE byte type constants */
    RLE_COMMAND     = 0,
    RLE_ENDOFLINE   = 0,
    RLE_ENDOFBITMAP = 1,
    RLE_DELTA       = 2,
  };

void ReadBMP1bit (FILE *fp, GLubyte *colormap, os_type_e os_type, gl_texture_t *texinfo);

void ReadBMP4bits (FILE *fp, GLubyte *colormap, os_type_e os_type, gl_texture_t *texinfo);

void ReadBMP8bits (FILE *fp, GLubyte *colormap, os_type_e os_type, gl_texture_t *texinfo);

void ReadBMP24bits (FILE *fp, gl_texture_t *texinfo);

void ReadBMP32bits (FILE *fp, gl_texture_t *texinfo);

void ReadBMP8bitsRLE (FILE *fp, GLubyte *colormap, gl_texture_t *texinfo);

void ReadBMP4bitsRLE (FILE *fp, GLubyte *colormap, gl_texture_t *texinfo);

gl_texture_t * ReadBMPFile (const char *filename);

GLuint loadBMPTexture (const char *filename);

#endif