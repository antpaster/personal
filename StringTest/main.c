#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* strstr analog */
uint8_t hasSubstr( const char* inputStr, const char* substr) {
    size_t i, occurenceCounter = 0;
    char *currPos;

    for( i = 0; i < strlen( inputStr); ++i) {
        currPos = substr + i;

        if( *currPos == *( inputStr + i)) {
            occurenceCounter++;

            if( occurenceCounter == strlen( substr)) {
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    printf( "%u\n", hasSubstr( "You must read the entire document before you start to answer.",
        "en"));
    return 0;
}

