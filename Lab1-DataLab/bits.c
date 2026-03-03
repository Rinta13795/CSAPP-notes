

#if 0
整数题规则（Integer Coding）
✅ 只能用的操作：

常量：0-255 (0xFF)
一元运算：! ~
二元运算：& ^ | + << >>
局部变量和函数参数

❌ 禁止使用：

控制流：if while for switch
宏定义：#define
其他运算：&& || - ?:
类型转换、数组、结构体
大常量（如 0xffffffff）

⚠️ 重要假设：

32位补码表示
右移是算术右移
移位量必须在 0-31 之间


浮点数题规则（Floating Point Coding）
✅ 可以用：

if while for 等控制流
int 和 unsigned 类型
任意整数常量
算术/逻辑/比较运算

❌ 禁止使用：

浮点类型 float double
类型转换
数组、结构体


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
  return (!((~(x+1))^x))&(!!(x+1));
}//
/*
验证Tmax方式：
TMax+1=TMin
TMax^TMin=-1

! 是逻辑非：
!0 = 1
!任何非零值 = 0

~(x+1) == x 这个性质，满足的只有 Tmax 和 -1 两个值
~(x+1) == x 等价于!(~(x+1)^x)
!!(x+1)用于排除-1
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
2判断2数是否相等:
!(x^y)
3
思路：
构造y=0xAAAAAAA，与x进行&仍是y，则x奇数位全是1
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
  int s1=!(m^0x03);//为1，判断高位0x03
  int s2=(x>>3)&1;//可能为0，1，大多是0(&1取符号)
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
}很妙


发现的技巧：
### 💡 巧妙的掩码设计：`0x6`

判断低4位是否为 8 或 9：
```c
int temp = !((0x6) & x);
```

**原理**：
- `0x6 = 0110` 只检查 bit2 和 bit1
- `8 = 1000`, `9 = 1001` 的 bit2、bit1 都是 0
- `A-F` 的 bit2 或 bit1 至少有一个是 1

🎯 **精准过滤**：忽略 bit0，只看关键位！
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
  int one=(!diffsign)&(((s>>31)&1)|!s);//同符号&<=条件
  //不同符号
  int two=(diffsign)&signx;//不同符号&x是否为负
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
  int s=((neg|x)>>31)&1;//&1来取符号
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
  int result;
  int sum16, sum8, sum4, sum2, sum1;//定义全放开头
  x = x ^ sign;          // 负数翻转，正数不变
  //二分法————找最高位(定义是：左边高位的一堆0不算（那些是填充位），从最高的1开始，到最低位（这是有效数值部分）)，最后加上符号位
  result=0;//数值部分位数(0到31的)
  //16位————筛查16位
  sum16=!!(x>>16);
  result+=sum16<<4;
  x>>=(sum16<<4);
  //8位
  sum8=!!(x>>8);
  result+=sum8<<3;
  x>>=(sum8<<3);
  //4位
  sum4=!!(x>>4);
  result+=sum4<<2;
  x>>=(sum4<<2);
  //2位
  sum2=!!(x>>2);
  result+=sum2<<1;
  x>>=(sum2<<1);
  //1位(只剩0位，1位了)
  sum1=!!(x>>1);
  result+=sum1<<0;
  x>>=(sum1<<0);
  //最后只剩下bit0位
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


### 💡 两种"二分"的区别

**传统二分**：取**索引**的一半
- `mid = (left + right) / 2`
- 找某个**位置**的值
- 原因：数组支持 `arr[索引]` 访问


**位的二分**：取**数量**的一半  
- `x >> (位数/2)`
- 检查某个**范围**有没有1
- 原因：整数只支持 `>>` 移位操作

🎯 **本质**：数据结构的访问方式不同，决定了分割方法不同

### 💡 howManyBits 核心思路

1. **翻转**：负数 XOR 全1 → 变正数（统一处理）
2. **二分**：对数值二分，找最高位的1（数值宽度）
3. **+1**：补码需要额外的符号位

🎯 二分统计数值部分，符号位单独加
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
  int mark;
  unsigned sum;
  int value=0;//忘记定义了！！！导致结果随便给
  if(exp==0xFF){
    return 0x80000000u;
  }
  if(exp==0){
    //浮点数转化成int
    return 0;
  }
  //规格数不会写啊，差的就是不会表达浮点数
  mark=exp-127;//为什么要E，指数？
  //有效值去小数点
  sum=frac|1<<23;
  //太小
  if(mark<0){
    return 0;
  }
  //溢出,因为是unsigned
  if(mark>=31){
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
  
  if(mark>23){
    value=sum<<(mark-23);
  }
  else
  {
    value=sum>>(23-mark);
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
    //E指数
    //最大：127
    //最小；-126
  if(x<-149){
    return 0;
  }
  if(x>127){
    return 0x7F800000;
  }
  if(x<=-126){
    return (1<<23)>>(~(x+126)+1);
    //
    /*
**思路**：
- 先构造 bit23
- 右移 `-(x+126)` 位到目标位置

**例子**：
- x=-127: 右移1位 → bit22 ✅
- x=-149: 右移23位 → bit0 ✅  
    */
    //可以简化成1<<(149-x);
    
  }
  else{
    return (x+127)<<23;
  }
}

/*
value = 0.frac × 2^(-126)
        ↑         ↑
     23位尾数   固定指数

frac = 000...001 (只有bit0=1)

value = 0.000...001 × 2^(-126)
      = 2^(-23) × 2^(-126)
      = 2^(-149)  ✅

重点：

情况范围处理方式
太小     x < -149          返回 0 
太大     x > 127           返回 +INF (0x7F800000)
非规格化  -149 ≤ x ≤ -127   E=0, 设置 frac 的某一位
规格化   -126 ≤ x ≤ 127     E=x+127, frac=0

 */