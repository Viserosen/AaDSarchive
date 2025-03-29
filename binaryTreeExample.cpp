#include <iostream>
#include <ctime>
#include <algorithm>

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

void random_gen(int *data,int n)
{
    srand(time(NULL));
    for(int i=0; i<n; i++)
    {
        data[i] = rand()%1000+1;
        cout << data[i] << " ";
    }

    sort(data,data+n);
    cout << endl;

    for(int i = 0; i < n; i++)
    {
        cout << data[i] << " ";
    }

    cout << endl;

}



 
struct Node* avl_print(int *data, int o,int n, struct Node* root)
{
    if(o>n)
    {
       return root;
    }
    int s = (o+n)/2;
    cout << data[s] << " ";
    
    root = insert_node(root, data[s]);
   
     
    root = avl_print(data,o,s-1,root);
    root = avl_print(data,s+1,n,root); 
    return root; 


    
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

int main()
{
    int n;
    cout << "n: " << endl;
    cin >> n;
    int *data = new int [n];
    struct Node* root = NULL;

    random_gen(data,n);
    root = avl_print(data,0,n-1,root);
    cout << endl;
    max_node(root);
    delete[] data;
    return 0;
}