#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//== To run ==
//(a) compile: gcc bsearch.c -lm -o run
//(b) run:     ./run

// =========================================[ ALGORITHM ]==============================================

/**
 * Recursive binary search algorithm 
 * @param arr    Sorted array to search
 * @param low    Low limit index of array to search from
 * @param high   High limit index of array to search to
 * @param target Element to find
 * @return Found state
 */
bool binarySearch_( const int * arr, size_t low, size_t high, int target ) {        
    size_t mid = ( low + ceil( ( high - low ) / 2. ) );
    
    printf( "  [binarySearch( arr, l:%lu, h:%lu, %d )] mid=%d\n", low, high, target, mid );
    
    if( low == high ) //i.e. just 1 element left
        return ( target == arr[mid] );
    else if( target < arr[mid] )
        return binarySearch_( arr, low, mid - 1, target );
    else //target >= arr[mid]
        return binarySearch_( arr, mid, high, target );
}

/**
 * Binary search algorithm 
 * @param arr    Sorted array to search
 * @param size   Size of array
 * @param low    Low limit index of array to search from
 * @param high   High limit index of array to search to
 * @param target Element to find
 * @return Found state
 */
bool binarySearch( const int * arr, size_t size, size_t low, size_t high, int target ) {       
    if( size == 0 )
        return false;
    
    return binarySearch_( arr, low, high, target );
}

// ===========================================[ TESTING ]================================================

static size_t test_count   = 0;
static size_t test_success = 0;

void printResult( const char * desc, bool res, int expected, int search_var ) {
    ++test_count;
    
    if( res == expected )
        ++test_success;
    
    printf( "Test \"%s\" (val=%d): %s\n", desc, search_var, ( res == expected ? "\x1b[32mPASSED\033[0m" : "\x1b[31mFAILED\033[0m" ) );    
}

bool test_one_el() {
    static int   arr[] = { 1 };
    const size_t size  = ( sizeof( arr ) / sizeof( int ) );
    const size_t high  = size - 1;
    
    printResult( "one element", binarySearch( arr, size, 0, high, 0 ), false, 0 );
    printResult( "one element", binarySearch( arr, size, 0, high, 1 ), true,  1 );
}

bool test_two_el() {
    static int   arr[] = { 1, 3 };
    const size_t size  = ( sizeof( arr ) / sizeof( int ) );
    const size_t high  = size - 1;
    
    printResult( "two element", binarySearch( arr, size, 0, high, 0 ), false, 0 );
    printResult( "two element", binarySearch( arr, size, 0, high, 1 ), true,  1 );
    printResult( "two element", binarySearch( arr, size, 0, high, 2 ), false, 2 );
    printResult( "two element", binarySearch( arr, size, 0, high, 3 ), true,  3 );
    printResult( "two element", binarySearch( arr, size, 0, high, 4 ), false, 4 );
}

bool test_even_el() {
    static int   arr[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22 };
    const size_t size  = ( sizeof( arr ) / sizeof( int ) );
    const size_t high  = size - 1;
    
    for( int i = 0, val = 0; i < high; ++i, val += 2 )
        printResult( "even", binarySearch( arr, size, 0, high, val ), true, val );
    
    for( int i = 0, val = 1; i < high; ++i, val += 2 )
        printResult( "even", binarySearch( arr, size, 0, high, val ), false, val );
}

bool test_odd_el() {
    static int   arr[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25 };
    const size_t size  = ( sizeof( arr ) / sizeof( int ) );
    const size_t high  = size - 1;
    
    for( int i = 0, val = 1; i < high; ++i, val += 2 )
        printResult( "odd", binarySearch( arr, size, 0, high, val ), true, val );
    
    for( int i = 0, val = 0; i < high; ++i, val += 2 )
        printResult( "odd", binarySearch( arr, size, 0, high, val ), false, val );
}

bool test_multiple() {
    static int   arr[] = { 1, 2, 3, 5, 5, 11, 13, 14 };
    const size_t size  = ( sizeof( arr ) / sizeof( int ) );
    const size_t high  = size - 1;
    
    printResult( "multiple", binarySearch( arr, size, 0, high, 0 ), false,  0 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 1 ), true,   1 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 2 ), true,   2 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 3 ), true,   3 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 4 ), false,  4 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 5 ), true,   5 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 6 ), false,  6 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 11 ), true,  11 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 13 ), true,  13 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 14 ), true,  14 );
    printResult( "multiple", binarySearch( arr, size, 0, high, 15 ), false, 15 );
}

int main() {
    test_one_el();
    test_two_el();
    test_even_el();
    test_odd_el();
    test_multiple();
        
    printf( "%lu/%lu successful tests\n", test_success, test_count );
    return 0;
}
