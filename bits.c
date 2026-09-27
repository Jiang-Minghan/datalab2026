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
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
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
    if(!x&&!y) return 1;
    if(!x) return 0;
    if(!y) return 0;
    x>>=31;
    y>>=31;
    return !(x^y);
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
    int result=((v>>16)>0)<<4;
    result|=((v>>(result|8))>0)<<3;
    result|=((v>>(result|4))>0)<<2;
    result|=((v>>(result|2))>0)<<1;
    result|=((v>>(result|1))>0);
    return result;
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
    int s1=n<<3;
    int s2=m<<3;
    int mask1=0xFF<<s1;
    int mask2=0xFF<<s2;
    int byte_n=x>>s1&0xFF;
    int byte_m=x>>s2&0xFF;
    x=(byte_n<<s2)|(byte_m<<s1)|((x&~(mask1|mask2)));
    return x;
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
    unsigned i = 0;
    unsigned u = 0;
    while(i!=32)
    {
        u<<=1;
        u+=v&1;
        v>>=1;
        i++;
    }
    return u;
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
    x=x>>n;
    int mask=~(1<<31>>n<<1);
    x&=mask;
    return x;
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
    x=~x;
    x|=x>>1;
    x|=x>>2;
    x|=x>>4;
    x|=x>>8;
    x|=x>>16;
    x=~x;
    int mask = 0x11111111;
    int s=x&mask;
    s+=(x>>1)&mask;
    s+=(x>>2)&mask;
    s+=(x>>3)&mask;
    s+=(s>>16);
    return (s&0xF)+(s>>4&0xF)+(s>>8&0xF)+(s>>12&0xF);
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
    if (x == 0) return 0;
    unsigned sign, ux, frac;
    int exp = 158;
    sign = x & 0x80000000u;
    ux = x;
    if (sign) ux = ~ux + 1;
    while (!(ux & 0x80000000u))
    {
        ux <<= 1;
        exp -= 1;
    }
    frac = (ux >> 8) & 0x7FFFFFu;
    if ((ux & 0xFFu) > 0x80u) frac += 1;
    if ((ux & 0x1FFu) == 0x180u) frac += 1;
    return sign|(exp << 23)|frac;
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
    unsigned sign=(uf>>31)&1;
    unsigned exp=(uf>>23)&0xFF;
    unsigned frac=uf&0x7FFFFF;
    if(exp==0xFF) return uf;
    if(exp==0)
    {
        frac<<=1;
        return (sign<<31)+frac;
    }
    else
    {
        exp+=1;
        return (sign<<31)|(exp<<23)|frac;
    }
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
    if(!(uf1|uf2)) return 0;
    unsigned sign=(uf2>>31)&1;
    int exp=(uf2>>20)&0x7FF;
    unsigned frac;
    if(!(exp!=0x7FF)) return 0x80000000;
    if(exp!=0)
    {
        exp-=1023;
        if(exp<0) return 0;
        if(exp>30) return 0x80000000;
        if(exp>20) frac=(((uf2<<12)|(uf1>>20))>>1|0x80000000)>>(31-exp);
        else frac=(uf2<<11|0x80000000)>>(31-exp);
        unsigned result=frac;
        if(sign) result=~result+1;
        return result;
    }
    else return 0;
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
    if(x>127) return 0x7F800000;
    if(x<-149) return 0;
    if(x>-127) return (x+127)<<23;
    else return 1<<(x+149);
}
