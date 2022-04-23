#include <stdio.h>
#include <string.h>
#include "AsciiArtTool.h"

RLEList test_function_input()
{
    FILE *in_stream = fopen("C:\\Users\\David\\Desktop\\MatamEx01\\matamEx1\\test.txt", "r");
    if(!in_stream) return NULL;
    RLEList list = asciiArtRead(in_stream);
    fclose(in_stream);
    return list;
}

void test_function_output1()
{
    FILE *out_stream = fopen("C:\\Users\\David\\Desktop\\MatamEx01\\matamEx1\\out.txt", "w");
    RLEList list = test_function_input();
    asciiArtPrint(list,out_stream);
    fclose(out_stream);
}

void test_function_output2()
{
    FILE *out_stream = fopen("C:\\Users\\David\\Desktop\\MatamEx01\\matamEx1\\out.txt", "w");
    RLEList list = test_function_input();
    asciiArtPrintEncoded(list,out_stream);
    fclose(out_stream);
}

char invertedMapping(char c)
{
    if(c == ' ') return '@';
    else if(c == '@') return ' ';
    return c;

}
void printInvertedArt(char *inputPath, char *outputPath)
{
    FILE *inStream = fopen(inputPath, "r");
    if(!inStream) return;
    RLEList list = asciiArtRead(inStream);
    fclose(inStream);

    RLEListResult status = RLE_LIST_SUCCESS;
    status = RLEListMap(list, invertedMapping);
    if(status != RLE_LIST_SUCCESS) return;

    char *result = RLEListExportToString(list, &status);
//    printf("%s",result);

    FILE *outStream = fopen(outputPath, "w");
    if(!outStream) return;
    asciiArtPrint(list,outStream);
    fclose(outStream);
}

void printEncodedArt(char *inputPath, char *outputPath)
{
    FILE *inStream = fopen(inputPath, "r");
    if(!inStream) return;
    RLEList list = asciiArtRead(inStream);
    fclose(inStream);
    FILE *outStream = fopen(outputPath, "w");
    if(!outStream) return;
    asciiArtPrintEncoded(list,outStream);
    fclose(outStream);
}
int main(int argc, char** argv) {

    if(argc != 4) return 0;
    if(strlen(argv[1]) !=2)  return 0;
    bool isInverted = argv[1][1] == 'i';
    if(isInverted)
        printInvertedArt(argv[2], argv[3]);
    else
        printEncodedArt(argv[2], argv[3]);


    return 0;
}

