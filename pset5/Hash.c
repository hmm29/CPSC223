/******************************************************************************
 * Hash.c
 * Main routine for sorting two queues
 *
 * HWK #5
 * Pancake Sort
 *
 * Harrison Miller
 ******************************************************************************/

// Return hash of string S into [0,SIZE)
static long hash (char *s, long size)
{
    unsigned long sum;
    int shift;
    const unsigned long prime = 3141592653589793239L;

    for (sum = 0, shift = 0; *s; s++) {
    sum ^= *s<<shift;
    shift += 7;
    if (shift >= 57)
        shift -= 57;
    }

    return ((prime * sum) % size);
}
