#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//== To run ==
//(a) compile: gcc quicksort.c -o run
//(b) run:     ./run

void printArr( const char * prefix, const int * arr, size_t ln ) {
    printf( "%s{ ", prefix );
        
    for( size_t i = 0; i < ln; ++i ) {
        if( i < (ln - 1) )
            printf( "%d, ", arr[i] );
        else
            printf( "%d ", arr[i] );
    }
    
    printf( "}\n" );
}


// =========================================[ ALGORITHM ]==============================================
/**
 * (helper) Integer comparator
 * @param lhs Pointer to element A
 * @param rhs Pointer to element B
 * @return 0: same, +1: larger than, -1: smaller than
 */
int comparator( const void * lhs, const void * rhs ) {
    const int * a = (int *) lhs;
    const int * b = (int *) rhs;
        
    if( *a > *b )
        return +1;
    else if( *a < *b )
        return -1;
    else
        return 0;
}

/**
 * (helper) Swaps elements
 * @param lhs Pointer to element A
 * @param rhs Pointer to element B
 */
void swap( int * lhs, int * rhs ) {
    if( lhs != rhs ) {
        *lhs ^= *rhs;
        *rhs ^= *lhs;
        *lhs ^= *rhs;
    }
}

/**
 * Quicksort partition method
 * @param arr  Pointer to array
 * @param ln   Length of arrayfunction
 * @param low  Left side index
 * @param high Right side index
 * @return New pivot index
 */
size_t partition( int * arr, size_t ln, size_t low, size_t high ) {
    const int pivot       = arr[high];
    size_t    pivot_index = low;
    
    printf( "  [partition( %p, ln:%lu, l:%lu, h:%lu )] pivot: [%lu]='%d'\n", &arr, ln, low, high, pivot_index, pivot );
        
    for( size_t i = low; i < high; ++i ) {
        if( arr[i] <= pivot ) {
            swap( &arr[i], &arr[pivot_index] );
            ++pivot_index;
        }
    }
    
    swap( &arr[high], &arr[pivot_index] );

    return pivot_index;
}

/**
 * Quicksort
 * @param arr  Pointer to array
 * @param ln   Length of array
 * @param low  Left side index
 * @param hi   Right side index
 */
void quicksort( int * arr, size_t ln, size_t low, size_t high ) {
    if( low < high ) {
        printf( "  [quicksort( %p, ln:%lu, l:%lu, h:%lu )]\n", arr, ln, low, high );
        size_t p = partition( arr, ln, low, high );
        quicksort( arr, ln, low, ( p > 0 ? (p - 1) : p ) ); //note: avoids underflow on 'high'
        quicksort( arr, ln, (p + 1), high );
    }
}

/**
 * Sort array using comparator
 * @param arr Pointer to array
 * @param ln  Length of array
 * @return Success
 */
bool sort( int * arr, size_t ln ) {
    
    if( ln == 0 )
        return false; //EARLY RETURN

    quicksort( arr, ln, 0, ln - 1 );
    
    return true;
}

// ===========================================[ TESTING ]================================================

static size_t test_count   = 0;
static size_t test_success = 0;

void printResult( const char * desc, const int * arr, const int * expected, size_t ln ) {
    bool success = true;
    
    for( size_t i = 0; i < ln; ++i ) {
        if( arr[i] != expected[i] ) {
            success = false;
            break;
        }
    }
    
        
    if( success )
        ++test_success;
    ++test_count;
    
    printf( "Test #%lu (\"%s\"): %s\n", test_count, desc, ( success ? "\x1b[32mPASSED\033[0m" : "\x1b[31mFAILED\033[0m" ) );
}

bool test_one_el() {
    int       arr[]      = { 1 };
    const int expected[] = { 1 };
    
    sort( arr, 1 );    
    printResult( "one element", arr, expected, 1 );

}

bool test_two_el() {
    int       arr[]      = { 2, 1 };
    const int expected[] = { 1, 2 };
    
    sort( arr, 2 );    
    printResult( "two elements", arr, expected, 2 );

}

bool test_first_last() {
    int       arr[]      = { 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    const int expected[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    sort( arr, 11 );    
    printResult( "first/last", arr, expected, 11 );
}

bool test_middle() {
    int       arr[]      = { 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10 };
    const int expected[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    sort( arr, 11 );    
    printResult( "middle", arr, expected, 11 );
}

bool test_inverse() {
    int       arr[]      = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0  };
    const int expected[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    sort( arr, 11 );    
    printResult( "inverse", arr, expected, 11 );
}

bool test_half_and_half() {
    int       arr[]      = { 10, 9, 8, 7, 6, 0, 1, 2, 3, 4, 5  };
    const int expected[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    sort( arr, 11 );    
    printResult( "half & half", arr, expected, 11 );
}

bool test_down_up() {
    int       arr[]      = { 10, 0, 9, 1, 8, 2, 7, 3, 6, 4, 5  };
    const int expected[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    sort( arr, 11 );    
    printResult( "down/up", arr, expected, 11 );
}

int main() {
    test_one_el();
    test_two_el();
    test_first_last();
    test_middle();
    test_inverse();
    test_half_and_half();
    test_down_up();
        
    printf( "%lu/%lu successful tests\n", test_success, test_count );
    return 0;
}
