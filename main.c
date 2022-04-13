#include <stdio.h>
#include "RLEList.h"

int main() {
    char* str = "WWWWWBBBBCCCDDDWWWW";
    RLEList list = RLEListCreate();
    while(*str)
    {
        RLEListAppend(list, *str);
        str++;
    }
    RLEListResult status=RLE_LIST_SUCCESS;
    char* result = RLEListExportToString(list,&status);
    if(status == RLE_LIST_SUCCESS)
        printf("%s", result);
    return 0;
}
