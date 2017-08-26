#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define STR_MAX_SIZE 10

typedef struct StrStruct
{
    char str[ STR_MAX_SIZE];
} StrStruct;

StrStruct wrappedStr[10];

/*! Быстрая сортировка строк */
void strQsort(
    StrStruct *strArr, /*!< массив строк */
    uint32_t arrSize  /*!< размер массива строк */
) {
    /* Первоначальная выставка индексов на начало и конец массива */
    uint32_t i = 0, j = arrSize - 1;
    char tempStr[ STR_MAX_SIZE];
    char p[ STR_MAX_SIZE];

    /* Центральный элемент */
    strncpy( p, strArr[ arrSize >> 1].str, STR_MAX_SIZE);

    /* Процедура разделения */
    do
    {
        while( strncmp( p, strArr[i].str, STR_MAX_SIZE) > 0)
        {
            i++;
        }

        while( strncmp( p, strArr[j].str, STR_MAX_SIZE) < 0)
        {
            j--;
        }

        if( i < j)
        {
            strncpy( tempStr, strArr[i].str, STR_MAX_SIZE);
            strncpy( strArr[i].str, strArr[j].str, STR_MAX_SIZE);
            strncpy( strArr[j].str, tempStr, STR_MAX_SIZE);
            i++;
            j--;
        }
    } while( i < j);


    /* Рекурсивные вызовы, если есть что сортировать */
    if( j > 0)
    {
        strQsort( strArr, j);
    }

    if( arrSize > i)
    {
        strQsort( strArr + i, arrSize - i);
    }
}

void strInsertionAlphabetSort(
    StrStruct *strArr,
    uint32_t arrSize,
    uint32_t iLetter
) {
    int i, j;
    char x[ STR_MAX_SIZE];

    /* Цикл проходов, i - индекс прохода */
    for( i = 0; i < arrSize; ++i)
    {
        strncpy( x, strArr[ i].str, STR_MAX_SIZE);

        /* Поиск места элемента в готовой последовательности */
        for( j = i - 1; j >= 0 && strncmp( strArr[ j].str, x, STR_MAX_SIZE) > 0
             /*(strArr[ j].str[iLetter] > x[iLetter])
             && ((iLetter < (strchr( strArr[ j].str, '\0') ? strlen( strArr[ j].str)
             : STR_MAX_SIZE)) || (iLetter < (strchr( x, '\0') ? strlen( x) : STR_MAX_SIZE)))*/; j--)
        {
            /* Сдвигаем элемент направо, пока не дошли */
            strncpy( strArr[ j + 1].str, strArr[ j].str, STR_MAX_SIZE);
        }

        /* Место найдено, вставить элемент */
        strncpy( strArr[ j + 1].str, x, STR_MAX_SIZE);
    }
}

int main( void)
{
//    StrStruct wrappedStr[10];

    memset( &wrappedStr, 0, 10 * sizeof( wrappedStr[0]));

    strncpy( wrappedStr[0].str, "Russia", STR_MAX_SIZE);
    strncpy( wrappedStr[1].str, "Rhanda", STR_MAX_SIZE);
    strncpy( wrappedStr[2].str, "Australia", STR_MAX_SIZE);
    strncpy( wrappedStr[3].str, "Canada", STR_MAX_SIZE);
    strncpy( wrappedStr[4].str, "Austria", STR_MAX_SIZE);
    strncpy( wrappedStr[5].str, "Columbia", STR_MAX_SIZE);
    strncpy( wrappedStr[6].str, "Somalia", STR_MAX_SIZE);
    strncpy( wrappedStr[7].str, "Armenia", STR_MAX_SIZE);
    strncpy( wrappedStr[8].str, "Sweden", STR_MAX_SIZE);
    strncpy( wrappedStr[9].str, "Italy", STR_MAX_SIZE);

    uint32_t i;
    for( i = 0; i < 10; ++i)
    {
        printf( "wrappedStr[%d].str = %s\n", i, wrappedStr[i].str);
    }

    //    strQsort( wrappedStr, 10);

    /* Сортировка вставками */
    uint32_t subArrSize = 10, iLetter = 0;
//    size_t str1len, str2len;
    i = 0;
//    do
//    {
//        strInsertionAlphabetSort( wrappedStr + i, subArrSize, iLetter);

//        while( wrappedStr[ i].str[ iLetter] != wrappedStr[ i + 1].str[ iLetter])
//        {
//            i++;
//        }

//        subArrSize = 0;
//        while( wrappedStr[ i + subArrSize].str[ iLetter]
//            == wrappedStr[ i + subArrSize + 1].str[ iLetter])
//        {
//            subArrSize++;
//        }

//        subArrSize++;
//        iLetter++;
//    } while( subArrSize > 1);

    strInsertionAlphabetSort( wrappedStr, 10, 0);

    for( i = 0; i < 10; ++i)
    {
        printf( "wrappedStr[%d].str = %s\n", i, wrappedStr[i].str);
    }

    return 0;
}

