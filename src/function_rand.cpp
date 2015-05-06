// "Returning rand() % N does not uniformly give a number in the range [0, N)
// unless N divides the length of the interval into which rand() returns
// (i.e. is a power of 2)."
// Source: http://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range
//return (l_bound + rand()%(u_bound - l_bound));


#include "function_rand.h"

int function_rand(const int &l_bound, const int &u_bound) {
	
    // Generate number
	unsigned int r;
    const unsigned int range = 1 + u_bound - l_bound;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do {
		r = rand();
    } while (r >= limit);

    return l_bound + (r / buckets);	
}
