/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x) | (~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x && !y) {
        return 1;
    } else if ((x >> 31) ^ (y >> 31)) {
        return 0;
    } else {
        if (!x && y) {
            return 0;
        }
        if ((!y && x)) {
            return 0;
        }
        return 1;
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int s;
    s = ((v >> 16) > 0) << 4;
    r |= s;
    v >>= s;
    s = ((v >> 8) > 0) << 3;
    r |= s;
    v >>= s;
    s = ((v >> 4) > 0) << 2;
    r |= s;
    v >>= s;
    s = ((v >> 2) > 0) << 1;
    r |= s;
    v >>= s;
    s = (v >> 1) > 0;
    r |= s;
    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int ns = n << 3, ms = m << 3;
    int nb = (x >> ns) & 0xFF;
    int mb = (x >> ms) & 0xFF;
    int mask = ~((0xFF << ns) | (0xFF << ms));
    return (x & mask) | (nb << ms) | (mb << ns);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned r = 0;
    unsigned maks = 0x1;
    for (int i = 0; i != 32; i++) {
        r = r << 1;
        r = r | (v & maks);
        v = v >> 1;
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    x >>= n;
    int mask = 1 << 31;
    mask = ~(mask >> n << 1);
    return x & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int cnt = 0;
    int mask16 = !~(x >> 16);
    cnt += mask16 << 4;
    x = x << (mask16 << 4);

    int mask8 = !~(x >> 24);
    cnt += mask8 << 3;
    x = x << (mask8 << 3);

    int mask4 = !~(x >> 28);
    cnt += mask4 << 2;
    x = x << (mask4 << 2);

    int mask2 = !~(x >> 30);
    cnt += mask2 << 1;
    x = x << (mask2 << 1);

    int mask1 = !~(x >> 31);
    cnt += mask1;
    x = x << (mask1);

    int mask0 = x & 0x80000000;
    cnt += !!mask0;
    return cnt;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (!x)
        return 0;
    unsigned S = 0;
    unsigned abs_x;
    int e;
    if (x == 0x80000000) {
        S = 1;
        e = 31;
        abs_x = 0x80000000U;
    } else if (x < 0) {
        S = 1;
        abs_x = -x;
    } else {
        S = 0;
        abs_x = x;
    }
    unsigned temp = abs_x;
    e = 0;
    if (temp >> 16) { e += 16; temp >>= 16; }
    if (temp >> 8)  { e += 8;  temp >>= 8;  }
    if (temp >> 4)  { e += 4;  temp >>= 4;  }
    if (temp >> 2)  { e += 2;  temp >>= 2;  }
    if (temp >> 1)  { e += 1;  temp >>= 1;  }

    unsigned m;
    if (e > 23) {
        int shift = e - 23;
        m = (abs_x >> shift) & 0x7FFFFF;
        unsigned G = 0;
        if (shift >= 1) {
            G = (abs_x >> (shift - 1)) & 1U;
        }
        if (G != 0) {
            unsigned R = 0;
            unsigned sticky = 0;
            if (shift >= 2) {
                R = (abs_x >> (shift - 2)) & 1U;
                sticky = abs_x & ((1U << (shift - 1)) - 1U);
            }
            if ((R | sticky) != 0) {
                m = m + 1;
            } else {
                if ((m & 1U) != 0) {
                    m = m + 1;
                }
            }
            if (m == 0x800000) {
                m = 0;
                e = e + 1;
            }
        }
    } else {
        m = (abs_x << (23 - e)) & 0x7FFFFF;
    }
    int E = e + 127;
    unsigned res = (S << 31) | (E << 23) | m;
    return res;
}


/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    return 2;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    return 2;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
