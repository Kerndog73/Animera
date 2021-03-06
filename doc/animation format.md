# Animation Format

* [Introduction](#introduction)
* [File Layout](#file-layout)
* [Data Representation](#data-representation)
* [Chunk Layout](#chunk-layout)
* [Standard Chunks](#standard-chunks)
  * [AHDR (Animation Header)](#ahdr-animation-header)
  * [PLTE (Palette)](#plte-palette)
  * [GRPS (Groups)](#grps-groups)
  * [LHDR (Layer Header)](#lhdr-layer-header)
  * [CHDR (Cel Header)](#chdr-cel-header)
  * [CDAT (Cel Data)](#cdat-cel-data)
  * [AEND (Animation End)](#aend-animation-end)

## Introduction

The animation format (`.animera`) is heavily inspired by the PNG format. This is
because the PNG format is very resistant to error (as it was originally designed
to be sent over a network). If the file is corrupted somehow, the signature
might not match up, or the chunk names might be invalid, or the CRC check won't
pass. If a new chunk is added in the future, old decoders will warn about it. It
is extremely unlikely that a corrupted file will be read without emitting an 
error.

## File Layout

The file starts with an 8 byte signature.

| Byte | ASCII |
|------|-------|
| 65   | A     |
| 110  | n     |
| 105  | i     |
| 109  | m     |
| 101  | e     |
| 114  | r     |
| 97   | a     |
| 0    | \0    |

Following the signature are some number of chunks. The order of the chunks is
defined by the following pseudo-code.

```
AHDR
PLTE
GRPS
for each layer:
  LHDR
  for each cel in layer:
    CHDR
    if cel is not null:
      CDAT
AEND
```

## Data Representation

To avoid repetition, I will define some standard data types that are used in the
definitions of standard chunks.

| Type   | Description                                      |
|--------|--------------------------------------------------|
| Byte   | 1 byte, unsigned                                 |
| Int    | 4 bytes, little-endian, signed (2s-complement)   |
| Uint   | 4 bytes, little-endian, unsigned                 |
| String | Sequence of printable ASCII characters [32, 126] |

## Chunk Layout

| Part   | Type               | Description                                                                                                      |
|--------|--------------------|------------------------------------------------------------------------------------------------------------------|
| Length | Uint               | The size of the "Data" part in bytes. This is not limited to 2^31 (as it is by PNG).                             |
| Name   | 4 ASCII characters | All standard chunk names are upper case. There is no meaning in the case of the characters (as there is in PNG). |
| Data   | "Length" bytes     | The contents of the chunk is defined by the particular chunk.                                                    |
| CRC    | Uint               | A CRC (Cyclic Redundancy Check) of the "Name" and "Data" parts as defined by zlib's `crc32` function.            |

See also: [PNG chunk layout](http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html#Chunk-layout)

## Standard Chunks

### AHDR (Animation Header)

| Type | Description                               |
|------|-------------------------------------------|
| Int  | Width of the canvas in pixels [1, 32768]  |
| Int  | Height of the canvas in pixels [1, 32768] |
| Int  | Number of layers [1, 2147483647]          |
| Int  | Number of groups [1, 2147483647]          |
| Int  | Number of frames [1, 2147483647]          |
| Int  | Animation delay in milliseconds [1, 999]  |
| Byte | Pixel format (explained below)            |

The number of layers corresponds to the number of LHDR chunks. The number of
groups corresponds to the number of groups in the GRPS chunk. There are three
valid values for the pixel format byte. These values happen to be the byte depth
of the pixel format.

| Value | Description |
|-------|-------------|
| 1     | Indexed     |
| 2     | Gray-alpha  |
| 4     | RGBA        |

### PLTE (Palette)

For indexed and RGBA animations, the palette consists of RGBA entries. Each
entry is four bytes. Each of the four bytes correspond to the red, green, blue
and alpha channels respectively.

For gray-alpha animations, the palette consists of gray-alpha entries. Each
entry is two bytes. Each of the two bytes correspond to the gray and alpha
channels respectively.

There can be no more than 256 palette entries. Trailing all-zero entries are
assumed if they're not present. In other words, if the last few entries are
all-zeros, they don't need to be written to the file. This is similar to the way
PNG optimizes its PLTE and tRNS chunks.

### GRPS (Groups)

| Type   | Description                                    |
|--------|------------------------------------------------|
| Int    | Number of frames in this group [1, 2147483647] |
| Uint   | Length of the name [0, 256]                    |
| String | Name of this group [0, 256]                    |

This chunk contains an array of groups. Each group has a length and a name. The
total length of all groups must be equal to the number of frames in the AHDR
chunk.

### LHDR (Layer Header)

| Type   | Description                                               |
|--------|-----------------------------------------------------------|
| Uint   | Number of cels in this layer [1, 4294967295]              |
| Byte   | Visibility of this layer (0 for invisible, 1 for visible) |
| String | Name of this layer [0, 256]                               |

Each layer contains a number of cels. The number of cels corresponds to the
number of CHDR chunks that follow this chunk.

### CHDR (Cel Header)

The format of the CHDR chunk depends on whether the cel is null or not.

If the cel is non-null, the cel rectangle is stored. This is a rectangle on the
canvas where the cel is placed. All pixels outside of the rectangle are
considered zero.

| Type | Description                                  |
|------|----------------------------------------------|
| Int  | Number of frames in this cel [1, 2147483647] |
| Int  | Cel X coordinate [-2147483648, 2147483647]   |
| Int  | Cel Y coordinate [-2147483648, 2147483647]   |
| Int  | Cel width [1, 1073741823]                    |
| Int  | Cel height [1, 1073741823]                   |

If the cel is null, the cel rectangle is not stored (because there is no cel to
have a rectangle).

| Type | Description                                  |
|------|----------------------------------------------|
| Int  | Number of frames in this cel [1, 2147483647] |

If the cel is non-null, the following chunk will be a CDAT chunk.

### CDAT (Cel Data)

Cel data is compressed using zlib's `deflate` function at the default
compression level. Before being compressed, the pixels are written in the order
you would expect. That is, pixels are written from left to right into scanlines,
and scanlines are written from top to bottom. Scanlines are not filtered as they
are in PNG so scanlines do not begin with a filter-type byte.

The pixel format of the cel data is defined by the pixel format in the AHDR
chunk.

* Indexed

   Each pixel is a single byte that is an index into the palette.

* Gray-alpha

   Each pixel is two bytes that correspond to the gray and alpha channels
   respectively.

* RGBA

   Each pixel is four bytes that correspond to the red, green, blue and alpha
   channels respectively.

See also: [PNG IDAT chunk](http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IDAT)

### AEND (Animation End)

This chunk contains no data. It corresponds to the IEND chunk of PNG. It marks
the end of the file to ensure that the file hasn't been truncated.

See also: [PNG IEND chunk](http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IEND)
