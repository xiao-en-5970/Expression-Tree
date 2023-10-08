#include <iostream>

using namespace std;

typedef struct treeNode
{
    char data;
    char parent;
    struct treeNode* Left;
    struct treeNode* Right;
} Tree, * PTree;

char ch;//读字符
PTree Stack[20];//一个小小的数组栈
int bottom = 0;//栈底
int top = 0;//栈顶

//函数声明
PTree create_NewRoot(char data);//创建新树根
void create_Left(PTree root, char data);//添加左子节点
void create_Right(PTree root, char data);//添加右子节点
void insert_Left(PTree root, PTree left);//插入左子树
void insert_Right(PTree root, PTree right);//插入右子树
void press_Stack(PTree tree);//进行一个栈的压
PTree pop_and_save_Stack();//进行一个栈的弹(但是保存弹出的那个栈)
char pop_Stack();//进行一个栈的弹（但是仅保存弹出的栈的值）
void merge_Tree();//将栈中的树组合
void print_Tree_m(PTree);//中序遍历这个树
void delete_Node(PTree root);//删除节点，释放内存


int main()
{
    while ((ch = getchar()) != '\n')
    {
        press_Stack(create_NewRoot(ch));
    }
    if (top != 1)
    {
        cout << "ERROR!" << endl;
        return 0;
    }
    print_Tree_m(Stack[top]);
    return 0;
}


//创建新树根
PTree create_NewRoot(char data)
{
    PTree root = new Tree;
    root->data = data;
    root->Left = nullptr;
    root->Right = nullptr;
    root->parent = '#';
    return root;
}

//添加左子节点
void create_Left(PTree root, char data)
{
    root->Left = new Tree;
    root->Left->data = data;
    root->Left->Left = nullptr;
    root->Left->Right = nullptr;
    root->Left->parent = root->data;
}

//添加右子节点
void create_Right(PTree root, char data)
{
    root->Right = new Tree;
    root->Right->data = data;
    root->Right->Left = nullptr;
    root->Right->Right = nullptr;
    root->Right->parent = root->data;
}

//插入左子树
void insert_Left(PTree root, PTree left)
{
    root->Left = left;
    root->Left->parent = root->data;
}

//插入右子树
void insert_Right(PTree root, PTree right)
{
    root->Right = right;
    root->Right->parent = root->data;
}

//进行一个栈的压
void press_Stack(PTree tree)
{
    top++;
    Stack[top] = tree;
    if (tree->Left == nullptr && (Stack[top]->data == '+' || Stack[top]->data == '-' || Stack[top]->data == '*' || Stack[top]->data == '/'))
    {
        merge_Tree();
    }
}

//进行一个栈的弹(但是保存弹出的那个栈)

PTree pop_and_save_Stack()
{
    PTree p = Stack[top];
    Stack[top] = nullptr;
    top--;
    return p;
}

//进行一个栈的弹（但是仅保存弹出的栈的值）
char pop_Stack()
{
    char p = Stack[top]->data;
    Stack[top] = nullptr;
    delete Stack[top];
    Stack[top] = nullptr;
    top--;
    return p;
}

//将栈中的树组合
void merge_Tree()
{
    if (top <= 2)
    {
        cout << "ERROR!" << endl;
        exit(0);
    }
    PTree root = pop_and_save_Stack();
    PTree right = pop_and_save_Stack();
    PTree left = pop_and_save_Stack();
    insert_Left(root, left);
    insert_Right(root, right);
    press_Stack(root);
}

//中序遍历这个树
void print_Tree_m(PTree root)
{
    if (root == nullptr)
    {
        return;
    }
    //以下是对括号的补充
    if ((root->parent == '*' || root->parent == '/') && root->Left != nullptr && (root->data == '+' || root->data == '-'))
    {
        cout << '(' << ' ';
        print_Tree_m(root->Left);
    }
    else if (root->Left != nullptr && (root->data == '*' || root->data == '/') && root->Left != nullptr)
    {
        print_Tree_m(root->Left);
    }
    else if ((root->parent != '*' && root->parent != '/') && root->Left != nullptr && (root->data == '+' || root->data == '-'))
    {
        print_Tree_m(root->Left);
    }
    cout << root->data << ' ';
    if ((root->parent == '*' || root->parent == '/') && root->Right != nullptr && (root->data == '+' || root->data == '-'))
    {
        print_Tree_m(root->Right);
        cout << ')';
    }
    else if (root->Right != nullptr && (root->data == '*' || root->data == '/') && root->Right != nullptr)
    {
        print_Tree_m(root->Right);
    }
    else if ((root->parent != '*' && root->parent != '/') && root->Right != nullptr && (root->data == '+' || root->data == '-'))
    {
        print_Tree_m(root->Right);
    }

    delete_Node(root);//用完了就删
}


//删除节点，释放内存
void delete_Node(PTree root)
{
    delete root;
}