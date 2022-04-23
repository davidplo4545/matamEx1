#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"

/**
*   asciiArtRead: Reads a file and compresses it using the RLE method.
*
* @param in_stream - A FILE object that includes the image we want to compress.
* @return
* 	An RLEList compressed with all the characters in the image.
*/
RLEList asciiArtRead(FILE *in_stream);


RLEListResult asciiArtPrint(RLEList list,FILE *out_stream);

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif