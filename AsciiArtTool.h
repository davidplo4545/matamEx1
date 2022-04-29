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
* 	An RLEList compressed with all the characters in the image,
*   returns NULL if the list couldn't be created.
*/
RLEList asciiArtRead(FILE *in_stream);

/**
*   asciiArtPrint: Decompresses an RLE list
 *   and writes it back into an output file.
*
* @param list - The compressed RLE list.
* @param out_stream - A FILE object that includes the output file stream.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS if the output file was generated successfully.
*/
RLEListResult asciiArtPrint(RLEList list,FILE *out_stream);

/**
*   asciiArtPrintEncoded: Decompressed an RLE list and write it back
 *   into an output file in the 'encoded' way.
*
* @param list - The compressed RLE list.
* @param out_stream - A FILE object that includes the output file stream.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS if the output file was generated successfully.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif