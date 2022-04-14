#include <stdio.h>
#include "RLEList.h"

int main() {
    char* str = "WWWWWBBBBCCCDDDWWWW";
    RLEList list = RLEListCreate();
    printf("here\n");
    while(*str)
    {
        RLEListAppend(list, *str);
        printf("Added\n");
        str++;
    }
    printf("here\n");
    RLEListResult status=RLE_LIST_SUCCESS;
    char* result = RLEListExportToString(list,&status);
    if(status == RLE_LIST_SUCCESS)
        printf("%s", result);
    return 0;
}
