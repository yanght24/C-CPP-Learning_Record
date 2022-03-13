//n (n>=0)个结点的有限集
//结点包括1个数据元素及若干指向其子树的分支
//结点拥有的子树个数: 度
//度为0, 叶节点/终端结点; 度不为0, 分支结点/非终端结点
//除根结点外, 分支结点也叫内部结点
//树中结点度的最大值:  树的度
//树中结点的最大层次:  树的深度/高度
/*
ADT 树(tree)
Data
	由1个根结点和若干棵子树构成, 树中结点具有相同数据类型和层次关系
Operation
InitTree(*T): 构造空树T;
DestroyTree(*T): 销毁树T;
CreateTree(*T, definition): 按definition中给出的树的定义来构造树;
ClearTree(*T): 若树T存在, 则将树T清为空树;
EmptyTree(T): 若树T为空树, 返回true, 否则返回false;
DepthTree(T): 返回树T的深度;
Root(T): 返回树T的根结点;
Value(T, cur_e): 返回cur_e结点的值;
Assign(T, cur_e, value): 给结点cur_e赋值为value;
Parent(T, cur_e): 若cur_e为非根结点, 则返回其双亲;
LeftChild(T, cur_e): 若cur_e为非叶结点, 则返回其最左孩子;
RightSibling(T, cur_e): 返回其右兄弟;
InsertChild(*T, *p, i, c): p指向树T的某结点, i为所指结点p的度加1, 非空树c与T不相交
						  插入c为树T中p所指结点的第i棵子树
DeleteChild(*T, *p, i): p指向树T的某结点, i为所指结点p的度加1,
					   删除T中p所指结点的第i棵子树
endADT
*/
//前序遍历: 根---左---右
//中序遍历: 左---根---右
//后序遍历: 左---右---根
//将树中的结点变成某种意义的线性序列
