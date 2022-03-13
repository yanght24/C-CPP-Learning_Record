/*
ADT 栈(stack)	//限定只在表尾进行插入和删除操作的线性表
Data
	同线性表, 元素具有相同的类型, 相邻元素具有前驱后继关系
Operatioon
InitStack(*S): 初始化操作, 建立一个空栈
DestoryStack(*S): 若栈存在, 则销毁
ClearStack(*S): 清空栈
EmptyStack(S): 若栈为空, 返回true, 否则返回false
GetTop(S, *e): 若栈存在且非空, 用e返回栈顶元素
Push(*S, e): 插入新元素e到栈顶
Pop(*S, *e): 删除栈的栈顶元素, 并用e返回其值
StackLength(S): 返回栈的元素个数
endADT

ADT 队列(queen)	//一端插入, 另一端删除的线性表
Data
	同线性表, 元素具有相同的类型, 相邻元素具有前驱后继关系
OPeration
InitQueue(*Q): 初始化操作, 建立一个空队列
DestoryQueue(*Q): 若队列存在, 则销毁
ClearQueue(*Q): 清空队列
EmptyQueue(Q): 若队列为空, 返回true, 否则返回false
GetHead(Q, *e): 若队列存在且非空, 用e返回队头元素
EnQueue(*Q, e): 插入新元素e到队列中并成为队尾元素
DeQueue(*Q, *e): 删除队列中对头元素, 并用e返回其值
QueueLength(Q): 返回队列的元素个数
endADT
*/
