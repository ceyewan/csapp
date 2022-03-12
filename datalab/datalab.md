位运算还能这样玩，我是万万没想到的。

![image-20220306235036268](https://gitee.com/ceyewan/pic/raw/master/images/image-20220306235036268.png)

### bitXor

```c
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
```

意思就是说我们用 ~ 和 & 实现 ^ 。

```c
// x ^ y = x & (~y) | (~x) & y
// ~ (x | y) = ~x & ~y
// 数字逻辑经常用到
int bitXor(int x, int y)
{
  x = ~(~x & y) & ~(x & ~y);
  return ~x;
}
```

### tmin

```c
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
```

最小值就是 01111111 + 1 = 10000000 。

```c
int tmin(void)
{
  return 1 << 31;
}
```

### isTmax

```c
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
```

判断给定的数是不是最大数，我们发现 x + 1 = 1000000 == ~ x。相等可以用异或是否等于 0 来判断。

```c
int isTmax(int x)
{
  // INT_MAX 和 -1 都满足
  int a = !((x + 1) ^ (~x));
  // 不是 -1
  int b = !!((x + 1) ^ 0x0);
  return a & b;
}
```

### allOddBits

```c
/*
 * odd-numbered： 奇数
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
```

判断是否奇数位置全部为 1 ，即 1010 。也就是说原数字和 0xA 取与运算之后还是 0xA  。

```c
int allOddBits(int x)
{
  int y = 0xAA; // 要求限制最多 8 位
  int a = (x & y); // 还是 0xAA
  int b = (x >> 8) & y; // 还是 0xAA
  int c = (x >> 16) & y; // 还是 0xAA
  int d = (x >> 24) & y; // 还是 0xAA
  a = a & b & c & d; // 还是 0xAA
  return !(a ^ y); // 异或取反实现 ==
}
```

### negate

```c
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
```

相反数，取反 + 1

```c
int negate(int x)
{
  return (~x) + 1;
}
```

### isAsciiDigit

```c
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
```

判断给定数字是否是 0x30 <= x <= 0x39 。那么高位一定是 0x3 。接下来就是判断低 4 位小于 10 ，也就是 x < 0xA ，也就是 x + (-0xA) 是负数，减号可以取反 + 1 ，负数只要判断符号位。

```c
int isAsciiDigit(int x)
{
  // 高位和 0x3 相等
  int y = 0x3;
  y = !((x >> 4) ^ y);
  // 得到低 4 位
  x = x & 0xf;
  // x < 0xA 
  x = ((x + (~0xA + 1)) >> 31) & 1;
  return x & y;
}
```

### conditional

```c
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
```

我们需要寻找一种方法当`x != 0`时候 让x变成`0xFFFFFFFF`。

```c
int conditional(int x, int y, int z)
{
  // x == 0 -> x == 0x111111111111
  // x == 1 -> x == 0x000000000000
  x = ~(!(x ^ 0x0)) + 1;
  return (~x & y) + (x & z);
}
```

### isLessOrEqual

```c
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
```

单纯判断 x - y < 0,是负数不够，因为有溢出，所以特判一下两个会溢出的情况。

```c
int isLessOrEqual(int x, int y)
{
  // a = 1 表示 x - y < 0,是负数
  int a = ((x + (~y + 1)) >> 31) & 1;
  // b = 1 表示 x = y
  int b = !(x ^ y);
  // c = 1 表示 x > 0, y < 0
  int c = (!((x >> 31) & 0x1)) & ((y >> 31) & 0x1);
  // d = 1 表示 x < 0, y > 0
  int d = ((x >> 31) & 0x1) & (!((y >> 31) & 0x1));
  return (a | b | d) & (!c);
}
```

### logicalNeg

```c
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
```

```c
int logicalNeg(int x)
{
  // 0 的特殊之处在于相反数和他同号，取或了还是 0 
  // 其他的要么是 0 | 1 ，要么是 1 | 1（INT_MIN 的相反数也特别）
  // 100000000 左移会是 11111111110000
  // 否则后面就应该是 ^ 1
  return ((x | (~x + 1)) >> 31) + 1;
}
```

### howManyBits

```c
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
```

感觉理解题意比较难，大致就是正数需要符号位和到最高位的 1 即可，负数需要 0 和到最高位的 0 即可。

```c
int howManyBits(int x)
{
  int b16, b8, b4, b2, b1, b0;
  int flag = x >> 31;
  x = (flag & ~x) | (~flag & x); // x为非正数则不变 ,x 为负数 则相当于按位取反
  // 二分法
  b16 = !!(x >> 16) << 4;        //如果高16位不为0,则我们让b16=16
  x >>= b16;                     //如果高16位不为0 则我们右移动16位 来看高16位的情况
  //下面过程基本类似
  b8 = !!(x >> 8) << 3;
  x >>= b8;
  b4 = !!(x >> 4) << 2;
  x >>= b4;
  b2 = !!(x >> 2) << 1;
  x >>= b2;
  b1 = !!(x >> 1);
  x >>= b1;
  b0 = x;
  return b0 + b1 + b2 + b4 + b8 + b16 + 1;
}
```

### floatScale2

```c
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
```

我们读入一个数进来，当成浮点数，然后乘以 2 ，输出。

```c
unsigned floatScale2(unsigned uf)
{
  int flag = uf >> 31; // 符号位
  int exp = (uf >> 23) & ((1 << 8) - 1);
  int frac = (uf & ((1 << 23) - 1));
  if (exp == 0xFF) // 正无穷
    return uf;
  // 代表 frac 首位一定是 0
  else if (a == 0x0)
  {
    b <<= 1;
  }
  // 乘以 2
  else
  {
    a += 1;
  }
  return (flag << 31) | (a << 23) | b;
}
```

### floatFloat2Int

```c
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
```

将浮点数转化为整数

```c
int floatFloat2Int(unsigned uf)
{
  int flag = uf >> 31;
  int a = (uf >> 23) & ((1 << 8) - 1);
  int b = (uf & ((1 << 23) - 1));
  // 超出上界，2^31 * 1.xxxxxxxx 是表达不了的，int 最大 2^31 - 1
  if (a - 127 >= 31)
    return 0x80000000u;
  // 小数也不行
  else if (a < 127)
    return 0;
  else
  {
    if (flag == 0)
      return (1 << (a - 127)) + (b << (a - 127) >> 23);
    else
      return -(1 << (a - 127)) - (b << (a - 127) >> 23);
  }
}
```

### floatPower2

```
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
```

求 2^x 用浮点数表示，最大是 2^127 * 1.xxxxxxxx，2^128 就表示不了了。 INF = 0x7F8000，指数部分全满。

最小是 2 ^ -126 * 0.00……001 = 1.0 * 2 ^ -149 。

```c
unsigned floatPower2(int x)
{
  if (x > 127)
  {
    return 0xFF << 23;
  }
  else if (x < -149)
    return 0;
  // 移动整数部分
  else if (x >= -126)
  {
    int exp = x + 127;
    return (exp << 23);
  }
  // 移动小数部分
  else
  {
    int t = 149 + x;
    return (1 << t);
  }
}
```

- 规格化的数 exp != 0 and exp != 255
- 非规格化的数 exp = 0，阶码 = 1 - bias，对于 float，即是 -126
- 无穷大，exp == 255， frac == 0
- NaN，exp = 255 ， frac != 0