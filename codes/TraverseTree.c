#include "stdio.h"
#include "stdlib.h"
#include "string.h"

///树
struct Tree
{
	char data;
	struct Tree *left;
	struct Tree *right;
} ta,tb,tc,td,te,tf,tg,th;


///结点
struct Node
{
	void *val;
	Node *next;
	int topCount;
};


Node *stackTop = NULL;
///栈
class Stack{
	public:

	Node * top()
	{
		return stackTop;
	}

	void *pop()
	{
		if (stackTop == NULL)
		{
			return stackTop;
		}else{
			Node *node = stackTop;
			stackTop = stackTop->next;
			return node->val;
		}
	}

	void push(void *val)
	{
		if (val != NULL)
		{
			Node *p = (Node *)malloc(sizeof(Node));
			p->val = val;
			p->next = stackTop;
			stackTop = p;
		}
	}
};


///初始化一棵树
Tree * initTree()
{
	struct Tree *pta,*ptb,*ptc,*ptd,*pte,*ptf,*ptg,*pth;
	pta = &ta;
	ptb = &tb;
	ptc = &tc;
	ptd = &td;
	pte = &te;
	ptf = &tf;
	ptg = &tg;
	pth = &th;

	pta->data = 'A';
	pta->left = ptb;
	pta->right = ptc;

	ptb->data = 'B';
	ptb->left = ptd;
	ptb->right = pte;

	ptc->data = 'C';
	ptc->left = ptf;
	ptc->right = ptg;

	ptd->data = 'D';
	ptd->left = NULL;
	ptd->right = NULL;

	pte->data = 'E';
	pte->left = pth;
	pte->right = NULL;

	ptf->data = 'F';
	ptf->left = NULL;
	ptf->right = NULL;

	ptg->data = 'G';
	ptg->left = NULL;
	ptg->right = NULL;

	pth->data = 'H';
	pth->left = NULL;
	pth->right = NULL;

	return pta;
}


///声明方法
void preOrder(struct Tree *tree);
void preOrderNon(struct Tree *tree);
void inOrder(struct Tree *tree);
void inOrderNon(struct Tree *tree);
void postOrder(struct Tree *tree);
void postOrderNon1(struct Tree *tree);
void postOrderNon2(struct Tree *tree);

int main(int argc, char const *array[])
{
	struct Tree *root = initTree();

	printf("递归前序遍历（根左右）\n");
	preOrder(root);
	printf("\n");

	printf("非递归前序遍历（根左右）\n");
	preOrderNon(root);
	printf("\n");

	printf("递归中序遍历（左根右）\n");
	inOrder(root);
	printf("\n");

	printf("非递归中序遍历（左根右）\n");
	inOrderNon(root);
	printf("\n");

	printf("递归后序遍历（左右根）\n");
    postOrder(root);
    printf("\n");

	printf("非递归后序遍历（左右根）\n");
    postOrderNon1(root);
    printf("\n");

    printf("非递归后序遍历（左右根）\n");
    postOrderNon2(root);
    printf("\n");

	return 0;
}


///递归前序遍历（根左右）
void preOrder(struct Tree *tree)
{
	if (tree != NULL)
	{
		printf("%c,", tree->data);
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

///非递归前序遍历（根左右）
void preOrderNon(struct Tree *tree)
{
	struct Tree *p = tree;
	Stack *s;

	while(p != NULL || s->top() != NULL)
	{
		while(p != NULL){
			printf("%c,", p->data);
			s->push((void *)p);
			p = p->left;
		}

		if (s->top() != NULL)
		{
			p = (struct Tree *)s->pop();	
			p = p->right;	
		}
	}
}


///递归中序遍历（左根右）
void inOrder(struct Tree *tree)
{
	if (tree != NULL)
	{
		inOrder(tree->left);
		printf("%c,", tree->data);
		inOrder(tree->right);
	}
}


///非递归中序遍历（左根右）
void inOrderNon(struct Tree *tree)
{
	struct Tree *p = tree;
	Stack *s;
	while(p != NULL || s->top()!= NULL)
	{
		while(p != NULL)
		{
			s->push((void *)p);
			p = p->left;
		}
		if (s->top() != NULL)
		{
			p = (struct Tree *)s->pop();
			printf("%c,", p->data);
			p = p->right;
		}
	}
}


///递归后序遍历（左右根）
void postOrder(struct Tree *tree)
{
	if (tree != NULL)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		printf("%c,", tree->data);
	}
}


///非递归后序遍历（左右根）
void postOrderNon1(struct Tree *tree)
{
	///这种思路是A结点先压栈，然后访问左子树，A结点出栈，A结点入栈，访问右子树，然后A结点出栈，访问A结点。
	///所以是A结点第二次出栈的时候访问
	struct Tree *p = tree;
	Stack *s;
	while(p != NULL || s->top() != NULL)
	{
		while(p != NULL)
		{
			Node *node = (Node *)malloc(sizeof(Node));
			node->topCount = 0;
			node->val = p;
			s->push(node);
			p = p->left;
		}
		if (s->top() != NULL)
		{	
			Node *node = (struct Node *)s->pop();
			node->topCount ++;
			// return;
			if (node->topCount == 2)
			{
				//第二次出现在栈顶
				p = (struct Tree *)node->val;
				printf("%c,", p->data);
				p = NULL;
			}else{
				//第一次出现在栈顶
				p = (struct Tree *)node->val;
				s->push(node);
				p = p->right;
			}
		}
	}
}


///非递归后序遍历（左右根）
void postOrderNon2(struct Tree *tree)
{
	//如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
	//若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
    Tree *cur;                      
    Tree *pre = NULL;              
    Stack *s;
    s->push((void *)tree);
    while(s->top() != NULL)
    {
        Node *top=s->top();
        cur = (struct Tree *)top->val;
        if((cur->left==NULL&&cur->right==NULL)||
           (pre!=NULL&&(pre==cur->left||pre==cur->right)))
        {
            printf("%c,", cur->data);
            s->pop();
            pre=cur; 
        }
        else
        {
            if(cur->right != NULL)
            {
                s->push(cur->right);
            }
            if(cur->left != NULL)    
            {
                s->push(cur->left);
            }
        }
    }
}
