#include <iostream>

using namespace std;

typedef struct treeNode
{
    char data;
    char parent;
    struct treeNode* Left;
    struct treeNode* Right;
} Tree, * PTree;

char ch;//���ַ�
PTree Stack[20];//һ��СС������ջ
int bottom = 0;//ջ��
int top = 0;//ջ��

//��������
PTree create_NewRoot(char data);//����������
void create_Left(PTree root, char data);//������ӽڵ�
void create_Right(PTree root, char data);//������ӽڵ�
void insert_Left(PTree root, PTree left);//����������
void insert_Right(PTree root, PTree right);//����������
void press_Stack(PTree tree);//����һ��ջ��ѹ
PTree pop_and_save_Stack();//����һ��ջ�ĵ�(���Ǳ��浯�����Ǹ�ջ)
char pop_Stack();//����һ��ջ�ĵ������ǽ����浯����ջ��ֵ��
void merge_Tree();//��ջ�е������
void print_Tree_m(PTree);//������������
void delete_Node(PTree root);//ɾ���ڵ㣬�ͷ��ڴ�


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


//����������
PTree create_NewRoot(char data)
{
    PTree root = new Tree;
    root->data = data;
    root->Left = nullptr;
    root->Right = nullptr;
    root->parent = '#';
    return root;
}

//������ӽڵ�
void create_Left(PTree root, char data)
{
    root->Left = new Tree;
    root->Left->data = data;
    root->Left->Left = nullptr;
    root->Left->Right = nullptr;
    root->Left->parent = root->data;
}

//������ӽڵ�
void create_Right(PTree root, char data)
{
    root->Right = new Tree;
    root->Right->data = data;
    root->Right->Left = nullptr;
    root->Right->Right = nullptr;
    root->Right->parent = root->data;
}

//����������
void insert_Left(PTree root, PTree left)
{
    root->Left = left;
    root->Left->parent = root->data;
}

//����������
void insert_Right(PTree root, PTree right)
{
    root->Right = right;
    root->Right->parent = root->data;
}

//����һ��ջ��ѹ
void press_Stack(PTree tree)
{
    top++;
    Stack[top] = tree;
    if (tree->Left == nullptr && (Stack[top]->data == '+' || Stack[top]->data == '-' || Stack[top]->data == '*' || Stack[top]->data == '/'))
    {
        merge_Tree();
    }
}

//����һ��ջ�ĵ�(���Ǳ��浯�����Ǹ�ջ)

PTree pop_and_save_Stack()
{
    PTree p = Stack[top];
    Stack[top] = nullptr;
    top--;
    return p;
}

//����һ��ջ�ĵ������ǽ����浯����ջ��ֵ��
char pop_Stack()
{
    char p = Stack[top]->data;
    Stack[top] = nullptr;
    delete Stack[top];
    Stack[top] = nullptr;
    top--;
    return p;
}

//��ջ�е������
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

//������������
void print_Tree_m(PTree root)
{
    if (root == nullptr)
    {
        return;
    }
    //�����Ƕ����ŵĲ���
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

    delete_Node(root);//�����˾�ɾ
}


//ɾ���ڵ㣬�ͷ��ڴ�
void delete_Node(PTree root)
{
    delete root;
}