#include <iostream>
#include <ctime>
#include <algorithm>
#include <set>

using namespace std;

struct Node
{
    Node *left;
    Node *right;
    int key;
};



struct Node* NodeCreate(int key_temp)
{
    struct Node* temp = new struct Node;
    temp->key=key_temp;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

struct Node* insert_node(struct Node* node, int key)
{
    if(node==NULL)
    {
        return NodeCreate(key);
    }
    if(key>node->key)
    {
        node->right = insert_node(node->right,key);
    }
    else if(key<node->key)
    {
        node->left = insert_node(node->left,key);
    }
    return node;
}

void max_node(struct Node* node)
{
        cout << node->key << endl;
        if(node->right==NULL)
        {
            return;
        }
        max_node(node->right);
        return;
    
}

struct Node* generate_random_bst(struct Node* root)
{
    int n; 
    int k;
    int x;

    srand(time(NULL));

    cout << "number of elements" << endl;
    cin >> n;
    cout << "max numer k" << endl;
    cin >> k;
    set<int> s;

    for(int i = 0; i < n; i++)
    {
        do 
        {
            x = rand()%(k-10)+10;
            if(s.find(x)==s.end())
            {
                s.insert(x);
                root = insert_node(root,x);
                break;
            }
        }while(1);
    }
    s.clear();
    return root;
}

struct Node* generate_random_avl(struct Node* root)
{
    int n,k,x;
    set<int> s;

    srand(time(NULL));

    cout << "number of elements" << endl;
    cin >> n;

    do 
    {
        cout << "max numer k" << endl;
        cin >> k;
    }while(k<=10 || k<n);
    
    int *key_table = new int [n];
    //int key_table[10000];

    for(int i = 0; i < n; i++)
    {
        do 
        {
            x = rand()%(k-10)+10;
            if(s.find(x)==s.end())
            {
                s.insert(x);
                key_table[i] = x;
                break;
            }
        }while(1);
    }
    s.clear();

    for(int i = 0; i < n; n--)
    {
        sort(key_table,key_table+n);
        root = insert_node(root,key_table[n/2]);
        swap(key_table[n/2],key_table[n-1]);
    }

    delete[] key_table;
    return root;
}

void delete_tree(struct Node* root)
{
    if(root=NULL)
    {
        return;
    }

    delete_tree(root->left);
    delete_tree(root->right);

    delete root;
}


int main()
{
    char yn='y';
    int choice;
    struct Node* root = NULL;
  
    while(1)
    {   
        cout << "1-AVL" << endl;
        cout << "2-BST" << endl;
        cout << "3-END" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            root = generate_random_avl(root);
            break;
        case 2:
            root = generate_random_bst(root);
            break; 
        default:
            yn = 'n';
            break;
        }

        if(yn=='n')
        {
            break;
        }
        
        cout << "1-max and min" << endl;
        cout << "2-level of node - all nodes - remove node" << endl;
        cout << "3-write high to low" << endl;
        cout << "4-write preorder subtree - subtree hight - remove it postorder" << endl;
        cout << "5-preorder - balancing tree - preorder" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            max_node(root);
            delete_tree(root);
            root = NULL;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;

        

        } 
    }
    return 0;
}