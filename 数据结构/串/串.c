/*	由0个或多个字符组成的有限序列, 即字符串
	ASCII: 空格: 32	0: 48	A: 65	a: 97

ADT 串(string)
Data
串中元素仅由1个字符组成, 相邻元素具有前驱后继的关系
Operation
StrAssign(T, *chars): 生成1个其值等于字符串常量chars的串T
StrCopy(T, S): 串S存在, 由串S复制得串T
ClearString(S): 串S存在, 则清空
EmptyString(S): 若串S存在, 返回true, 否则返回false
StrLength(S): 返回串S的元素个数
StrCompare(S, T): S>T, 返回值>0; S=T, 返回0; S<T, 返回值<0
Concat(T, S1, S2): 用T返回由S1和S2连接而成的新串
SubString(Sub, S, pos, len): 串S存在, 1<=pos<=StrLength(S),
							且0<=len<=StrLength(S)-pos+1,
							用Sub返回串S的第pos个字符起长度为len的字串
Index(S, T, pos): 串S和串T存在, T非空, 1<=pos<=StrLength(S),
				 若主串S中存在和串T相同的子串, 则返回其在S中
				 第pos个字符之后第一次出现的位置, 否则返回0
Replace(S, T, V): 串S, 串T和串V存在, T非空,
				 用V替换主串S中出现所有与T相等的不重叠的子串
StrInsert(S, pos, T): 串S,和串T存在, 1<=pos<=StrLength(S)+1,
					 在串S的第pos个字符之前插入串T
StrDelete(S, pos, len): 串S存在, 1<=pos<=StrLength(S)-len+1,
					   在串S中删除第pos个字符起长度为len的子串
*/

