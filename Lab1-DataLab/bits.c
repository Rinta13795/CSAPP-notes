/* 
 * CS:APP Data Lab 
 * 
 * <Rinta>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:(integer coding rules)
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES(float point)

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.(最大数量的operator使用)

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~((~((~x)&y))&(~(x&(~y))));
}
/*
一：
德摩根定律：
~(x | y) = ~x & ~y
~(x & y) = ~x | ~y
变式：
x | y = ~(~x & ~y)
x & y = ~(~x | ~y)
(用真值表证明，记住结论就行)
二：
XOR 的定义：两个位不同时输出1，相同时输出0。
两种"不同"的情况：(就是讨论输出为真的情况，不满足则输出为假)

x=0, y=1 → ~x & y
x=1, y=0 → x & ~y
——>(~x & y)|(x & ~y)
*/
/* 
 * tmin - return minimum two's complement integer (返回最小补码数)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}//把谁移到目标位置，谁就在左边。 想要1到第31位，就是 1 << 31
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  return (!((~(x+1))^x))&(!!(x+1));//这个&理解成且的意识就可以，不要听Claude说的那些公式
}//
/*
用
TMax+1=TMin
(a^a)=0
!(a^a)=1
! 是逻辑非：
!0 = 1
!任何非零值 = 0

2.
~(x+1) == x 这个性质，满足的只有 Tmax 和 -1 两个值

~(x+1) == x 等价于!(~(x+1)^x)
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int mask=0xAA;
  mask=mask^mask<<8;
  mask=mask^mask<<16;//造0xAAAAAAAA
  return !(mask^(x&mask));
}
/*
1
规则里说的是不能用大常数（超过255的），但可以用变量  
2
思路：
奇数位全为1，就是x和掩码 0xAAAAAAAA 做&后还是 0xAAAAAAAA
*/
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return  ~x + 1  ;
}
/*
补码的性质：
-x = ~x + 1  
令返回y
x+y=0
因为x+~x=-1
所以x+~x+1=0
*/
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int m=x>>4;
  int s1=!((m|0)^0x03);//为1
  int s2=(x>>3)&1;//可能为0，1，大多是0
  //为0:一组
  int first=!s2;
  //为1:
  int temp=!((0x6)&x);
  int second=s2&temp;
  return s1&(first|second);
}
/*
写了20分钟+十几分钟调试(我独自写出来的！！！！！)
后面没问题，主要在前面

  int s1=!((m|0)^0x03);//为1
  int s2=(x>>3)&1;//可能为0，1，大多是0
  两行。注意Tmin,0,[0x7ffffff9]等数据

  另外一解法：
  int isAsciiDigit(int x) {
    int a = x + (~0x30 + 1);  // x - 0x30，>=0说明x>=0x30
    int b = 0x39 + (~x + 1);  // 0x39 - x，>=0说明x<=0x39
    return !(a>>31) & !(b>>31);
}

*/
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  
  int first=!!x;//判断x非0还是0，x=0——>first=0——>mark=0,x=非0——>first=1——>mark=-1
  /*选择公式：
  (全1(mark) & y) | (全0 & z) = y | 0 = y (x是非0的时候)
  (全0 & y) | (全1 & z) = 0 | z = z (x是0的时候)
  ————>需要制造一个全1和0，mark和～mark
  */
  int mark=(~first+1);
  return (mark&y)|(~mark&z);
}
/*
逻辑：
1.
x非零：(全1 & y) | (全0 & z) = y | 0 = y
x为0：(全0 & y) | (全1 & z) = 0 | z = z

*/
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  //判断是否相同符号
  int signx=(x>>31)&1;
  int signy=(y>>31)&1;
  int diffsign=signx^signy;//相同为0，不同为1
  //相同符号
  // int s=x-y;改成：
  int s=x+(~y+1);
  int one=(!diffsign)&(((s>>31)&1)|!s);
  //不同符号
  int two=(diffsign)&signx;
  return one|two;
}
/*
思路对的：用x-y<0的做法  但是溢出问题会干扰等式
————>
分类：
x,y同符号以及x,y不同符号
*/
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int neg=~x+1;
  int s=((neg|x)>>31)&1;//要加上&1,保证逻辑右移和算数右移都是对的
  return s^1;
}
/*
区别0和非0性质：
对于任意非零数 x：
  x 和 -x 的符号位至少有一个是 1
对于 0：
  0 和 -0 都是全 0，符号位都是 0  
  然后移到开头就可以
*/
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

 //这题超级难，要反复复习
int howManyBits(int x) {
  int sign = x >> 31;    // 提取符号
  x = x ^ sign;          // 负数翻转，正数不变
  //二分法————找最高位(定义是：左边高位的一堆0不算（那些是填充位），从最高的1开始，到最低位（这是有效数值部分）)，最后加上符号位
  int result=0;//数值部分位数(0到31的)
  //16位
  int sum16=!!(x>>16);//说明16位到31位至少有1————>至少16个数
  result+=sum16<<4;
  x>>=(sum16<<4);
  //8位
  int sum8=!!(x>>8);
  result+=sum8<<3;
  x>>=(sum8<<3);
  //4位
  int sum4=!!(x>>4);
  result+=sum4<<2;
  x>>=(sum4<<2);
  //2位
  int sum2=!!(x>>2);
  result+=sum2<<1;
  x>>=(sum2<<1);
  //1位(只剩0位，1位了)
  int sum1=!!(x>>1);
  result+=sum1<<0;
  x>>=(sum1<<0);
  //加最后一位
  result+=x;
  //加上符号位
  result+=1;
  return result;
}
/*
返回的是位数，记得

公式：
x ^ 全1 = ~x
套路：
int sign = x >> 31;    // 提取符号
x = x ^ sign;          // 负数翻转，正数不变

错误总结：
1✅ 移位改成 sum << n 而不是 n << sum
✅ 所有 >> 改成 >>=（赋值）
✅ 最后简化成 result += x 然后 +1
(为什么？
符号位要计算+最后一位(反复验证调试需要，太tm难了这题

)
)
*/
//float
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
unsigned floatScale2(unsigned uf) {//这题有点懵逼，在非规格交界处
  unsigned exp=(uf>>23)&0xFF;
  unsigned s=(uf>>31)&1;
  unsigned frac=uf&0x7FFFFF;
  if(exp==0xFF){
    return uf;
  }
  //非规格数————>整体左移+保留符号位
  else if(exp==0){
    return (uf & 0x80000000) | (uf << 1);
  }
  //阶码+1，对于规格数
  return uf+(1<<23);
}
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
int floatFloat2Int(unsigned uf) {
  unsigned exp=(uf>>23)&0xFF;
  unsigned s=(uf>>31)&1;
  unsigned frac=uf&0x7FFFFF;
  if(exp==0xFF){
    return 0x80000000u;
  }
  if(exp==0){
    //浮点数转化成int
    return 0;
  }
  //规格数不会写啊，差的就是不会表达浮点数
  int E=exp-127;//为什么要E，指数？
  //有效值去小数点
  unsigned sum=frac|1<<23;
  //太小
  if(E<0){
    return 0;
  }
  //溢出,因为是unsigned
  if(E>=31){
    return 0x80000000u;
  }
  /*
`int` 的范围是：
```
最大值：2^31 - 1 = 2147483647
```E=31——>  2^31大于了
  */
  //浮点数数值
  // int value=sum*(2^(E-23));错误，c语言，^不能表示幂运算！！！！！！只能移位数，移位要分类
  int value=0;//忘记定义了！！！导致结果随便给
  if(E>23){
    value=sum<<(E-23);
  }
  else
  {
    value=sum>>(23-E);
  }
  if (s) {
        value = -value;
    }
  return value;
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
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {

}

/*


 */