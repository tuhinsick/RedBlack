#include "header.h"

int main(){ 
    freopen("in.txt","r",stdin);
    RedBlackTree rbt; 
    while(true) {
        //cout<<"taking input"<<endl;
        int x; 
        string s; 
        cin>>x>>s; 
        if(x == 0){
            break;
        }

        rbt.insert(x,s); 
    } 

    //rbt.inorder();
    rbt.printParentChild();

}