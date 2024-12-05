## Applications
#### 1.已知模式串 t = "abcaabbabcab", 写出用KMP法求得的每个字符对应的 next 和 nextval 函数值;

#### 2. 设目标为 t = "abcaabbabcabaacbacba", 模式为 p = "abcabaa"。 

>(1)计算模式p 的 nextval 函数值； 
>
>(2)画出利用KMP算法进行模式匹配时每一趟的匹配过程。

## Programs
#### 1.用KMP算法写一个搜索算法，搜索文档中特定词汇的出现总次数;

> 搜索《老人与海》小说txt文件中，“马林鱼”一词，出现的次数；

#### 2. 除了BF算法和KMP算法外，还有其他的高效串匹配算法，如Sunday算法。它比的KMP算法和BM算法都要晚提出。不过其逻辑和处理方式比二者要更简单清晰。
> Sunday算法会提前记录子串的组成和每种字符在子串中最右出现的位置，比如  : "abcab"（位序：0，1，2，3，4），每种字符在模板中的最靠右的位置为{'a':3, 'b':4, 'c':2}。
>
> 在每一次的比较中，一旦出现失配，算法会去看子串中在当前匹配段后一位的字符 ，找到这个字符在子串中最右出现的位置，并与其对齐，如果在子串中没有对应的字符 ，则直接右移跳过整段的匹配段。
>
> 看下面的例子：
> 
> ![image](https://github.com/abydym/Diamond/blob/main/Data%20Structure/String%2C%20Array%20%26%20Generalized%20tables/Sunday/Pictures/Q1.png)
> 
> 母串与子串在当前第五个字母位置失配，直接去看子串在当前匹配段（灰色线框）的后一个字符为'b'（绿色方框），并在子串中找到最靠右的'b'， 右移1步至两个'b'对齐（下图蓝色线框）。
> 
> ![image](https://github.com/abydym/Diamond/blob/main/Data%20Structure/String%2C%20Array%20%26%20Generalized%20tables/Sunday/Pictures/Q2.png)
> 
> 新的位置仍然失配， 在该匹配段的后一个字符  为'c'，同样的操作，将子串右移3位，使子串中的'c'与母串中的这个'c'对齐，成功匹配。
> 
> ![image](https://github.com/abydym/Diamond/blob/main/Data%20Structure/String%2C%20Array%20%26%20Generalized%20tables/Sunday/Pictures/Q3.png)
> 
> 可以看到，巧妙地利用字符串的特点可以有效减少匹配的次数，提高匹配效率。
>
> ##### 要求：实现Sunday算法（网上也都能搜到源码，要求仿照实现），并使用Sunday算法，搜索《百年孤独》小说txt文件中，“布恩地亚”一词，出现的次数。
