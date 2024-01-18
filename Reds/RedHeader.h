#include<bits/stdc++.h>
using namespace std; //

class Node {
    public : 
      int key; 
      string str; 
      Node* left; 
      Node* right; 
      Node* parent; 
      string color; 
      Node(int key, string str){ 
        this->key = key; 
        this->str = str; 
        this->left = NULL; 
        this->right = NULL; 
        this->color = "red"; 
        this->parent = NULL; 
      }
};

class Reds{
    Node* root; 

    Node* leftRotate(Node* node){ 
        Node* y = node->right; 
        Node* m = y->left; 
        y->left = node; 
        y->parent = node->parent; 
        if(node->parent == NULL){ 
            y->parent = NULL; 
            this->root=y;
        }
        else if(node == node->parent->left){ 
            node->parent->left = y; 
        }
        else{
            node->parent->right = y; 
        }

        node->parent = y;  
        node->right = m;
        if(m!=NULL){ 
            m->parent = node; 
        }

        return y; 

    }


    Node* rightRotate(Node* node){ 
        Node* y = node->left; 
        Node* m = y->right; 
        y->right = node; 
        y->parent = node->parent; 
        if(node->parent == NULL){ 
            cout<<"inside NULL"<<endl;
            y->parent = NULL;
            this->root=y; 
        }

        else if( node == node->parent->left){
            node->parent->left = y; 
        }

        else{ 
            node->parent->right = y; 
        }

        node->parent = y; 
        node->left = m; 
        if(m != NULL){ 
            m->parent = node; 
        }

        return y; 
    }

    void InsertFix(Node* node){ 
        while(node->parent != NULL && node->parent->color.compare("red")==0){
            if(node->parent->parent == NULL){ 
                node->parent->color = "black"; 
                this->root = node->parent; 
                return; 
            }
            else if(node->parent == node->parent->parent->left){ // parent of node is a left child of its grand parent
                if( node->parent->parent->right == NULL || node->parent->parent->right->color.compare("black") == 0){
                    if(node == node->parent->left){   // ll rotations
                        node = rightRotate(node->parent->parent); 
                        node->color = "black"; 
                        node->right->color = "red"; 
                        return; 
                    }

                    else{  // lr roations
                        node = leftRotate(node->parent); 
                        node = rightRotate(node->parent); 
                        node->color = "black"; 
                        node->right->color = "red"; 
                        return; 
                    }
                }

                else{
                    node->parent->color = "black"; 
                    node->parent->parent->right->color = "black"; 
                    if(node->parent->parent != this->root){
                        node->parent->parent->color = "red";
                    }
                    else{
                        node->parent->parent->color = "black"; 
                    }
                    // node->parent->parent->color = "red"; 
                    node = node->parent->parent; 
                }


            }

            else{
                if( node->parent->parent->left == NULL || node->parent->parent->left->color.compare("black")==0){
                    if(node == node->parent->right){ // rr rotations 
                         cout<<"rr"<<endl;
                         node = leftRotate(node->parent->parent); 
                         node->color = "black"; 
                         node->left->color = "red"; 
                         return;
                    }

                    else{  // rl rotations
                        node = rightRotate(node->parent); 
                        node = leftRotate(node->parent); 
                        node->color = "black"; 
                        node->left->color = "red";
                        return;

                    }
                }

                else{
                    node->parent->color = "black"; 
                    node->parent->parent->left->color = "black"; 
                    if(node->parent->parent != this->root){ 
                        node->parent->parent->color = "red";
                    }
                    else{
                        node->parent->parent->color = "black"; 
                    }
                    //node->parent->parent->color = "red"; 
                    node = node->parent->parent; 
                }

            }
        }
        this->root->color="black";
    }

    Node* insertHelp(Node* root, int key, string str){ 
        if(root == NULL){ 
            return new Node(key,str);  
        }

        if(root->key == key) {
            cout<<"key already exists"<<endl;
            root->str = str; 
        }

        else if(root->key < key){ 
            root->right = insertHelp(root->right,key,str); 
            root->right->parent = root; 
        }

        else{
            root->left = insertHelp(root->left,key,str); 
            root->left->parent = root; 
        }

        return root; 
    }

    void inorderHelp(Node* root){
        if(root == NULL){ 
            return; 
        }
        inorderHelp(root->left); 
        cout<<root->key<<" "<<root->color<<endl; 
        inorderHelp(root->right); 
    }




    public : 
       Reds(){ 
        root = NULL;
       }


    void insert(int key, string str) {
        if(root == NULL){ 
            root = new Node(key,str); 
            root->color = "black"; 
            return;
        }

        root = insertHelp(root,key,str);
        Node* x = root; 
        while(x->key != key){ 
            if(x->key > key){ 
                x = x->left;
            }

            else{
                x = x->right; 
            }
        } 
        if(x == NULL){ 
            cout<<"didn't inserted well"<<endl;
        }
        InsertFix(x); 
        this->root->color = "black";
       }

    void print() {
        cout<<this->root->key<<endl;
        inorderHelp(root); 
       }
      
};