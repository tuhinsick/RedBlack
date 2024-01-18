#include <bits/stdc++.h>
using namespace std; //

class Node
{
public:
    int key;
    string str;
    Node *left;
    Node *right;
    char color;
    Node *parent;

    Node(int key, string str)
    {
        this->left = NULL;
        this->right = NULL;
        this->key = key;
        this->str = str;
        this->color = 'R';
    }
};

class RedBlackTree
{
    Node *root;
    bool ll, lr, rl, rr, f;

    // rotate functions

    Node *leftRotate(Node *node)
    {
        cout << "Inside Left Rotate Function" << endl;
        Node *y = node->right;
        Node *x = y->left;
        y->left = node;
        node->right = x;
        node->parent = y;
        if (x != NULL)
        {
            x->parent = node;
        }

        return y;
    }

    Node *rightRotate(Node *node)
    {
        Node *y = node->left;
        Node *x = y->right;
        y->right = node;
        node->left = x;
        node->parent = y;
        if (x != NULL)
        {
            x->parent = node;
        }

        return y;
    }

    // insert helper function

    Node *insertHelp(Node *root, int key, string str)
    {
        // bool f = false;

        if (root == NULL)
        {
            return new Node(key, str);
        }

        if (root->key == key)
        {
            root->str = str;
            return root; // value modified
        }

        if (root->key < key)
        {
            root->right = insertHelp(root->right, key, str);
            root->right->parent = root;
            if (root->color == 'R' && root->right->color == 'R')
            {
                cout << "hello" << endl;
                f = true;
            }
        }

        if (root->key > key)
        {
            root->left = insertHelp(root->left, key, str);
            root->left->parent = root;
            if (root->color == 'R' && root->left->color == 'R')
            {
                f = true;
            }
        }

        if (ll)
        {
            cout<<"inside ll data : "<<root->key<<endl; 
            root = leftRotate(root);
            cout<<"after ll data : "<<root->key<<endl;
            root->color = 'B';
            root->left->color = 'R';
            ll = false;
        }
        else if (rr)
        {
            root = rightRotate(root);
            root->color = 'B';
            root->right->color = 'R';
            rr = false;
        }
        else if (rl)
        {
            root->right = rightRotate(root->right);
            root->right->parent = root;
            root = leftRotate(root);
            root->color = 'B';
            root->left->color = 'R';
            rl = false;
        }
        else if (lr)
        {
            root->left = leftRotate(root->left);
            root->left->parent = root;
            root = rightRotate(root);
            root->color = 'B';
            root->right->color = 'R';
            lr = false;
        }

        // Conflicts occured

        if (f)
        {
            if (root->parent->right == root)
            {
                if (root->parent->left == NULL || root->parent->left->color == 'B')
                {
                    if (root->left != NULL && root->left->color == 'R'){
                        cout<<"rl triggered"<<endl;
                        rl = true; 
                    }
                    else if (root->right != NULL && root->right->color == 'R')
                    {
                        cout << "ll triggered" << endl;
                        ll = true;
                    }
                }
                else
                {
                    root->parent->left->color = 'B';
                    root->color = 'B';
                    if (root->parent != this->root)
                        root->parent->color = 'R';
                }
            }
            else
            {
                if (root->parent->right == NULL || root->parent->right->color == 'B')
                {
                    if (root->left != NULL && root->left->color == 'R'){
                        rr = true; 
                        cout<<"rr triggered"<<endl;
                    }
                        
                    else if (root->right != NULL && root->right->color == 'R'){
                        lr = true; 
                        cout<<"lr triggered"<<endl;
                    }
                }
                else
                {
                    root->parent->right->color = 'B';
                    root->color = 'B';
                    if (root->parent != this->root)
                        root->parent->color = 'R';
                }
            }
            f = false;
        }

        return root;
    }

    void inorderHelp(Node *node)
    {
        if (node == NULL)
        {
            return;
        }

        inorderHelp(node->left);
        cout << node->key << " => " << node->str << endl;
        inorderHelp(node->right);
    }

    void printHelp(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        cout << root->key << "_" << root->str << " ";
        if (root->left != NULL)
        {
            cout << root->left->key << "_" << root->left->str << " ";
        }
        else
        {
            cout << "no left child ";
        }

        if (root->right != NULL)
        {
            cout << root->right->key << "_" << root->right->str << " ";
        }

        else
        {
            cout << "no right child ";
        }

        cout << endl;

        printHelp(root->left);
        printHelp(root->right);
    }

public:
    RedBlackTree()
    {
        root = NULL;
        ll = false;
        rr = false;
        lr = false;
        rl = false;
        f = false;
    }

    void insert(int key, string str)
    {
        if (root == NULL)
        {
            root = new Node(key, str);
            root->color = 'B';
            return;
        }
        insertHelp(root, key, str);
    }

    void printParentChild()
    {
        printHelp(root);
    }

    void inorder()
    {
        inorderHelp(root);
    }
};