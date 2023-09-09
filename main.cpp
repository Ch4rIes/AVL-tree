#include <iostream>


//design of AVL tree in C++
class Node{
public:
    Node *left , *right;
    int val , height;
    Node(int v){
        val = v;
        left = nullptr;
        right = nullptr;
        height = -1;
    }
    Node(){
        val = -1;
        left = nullptr;
        right = nullptr;
        height = -1;
    }
};

// 1. count(val): check if a value is in a tree
// 2. insert(val): insert a node into the tree
// 3. delete(val): delete a node out of the tree

class AVL{
public:
    Node* root;
    AVL(){
        root = nullptr;
    }
    //public interface
    void insert(int val){
        if(count(val))
            std::cout << val << " already in tree" << std::endl;
        else
            root = dfs_insert(root , val);
    }
    void del(int val){
        if(!count(val))
            std::cout << val << " not in tree" << std::endl;
        else
            dfs_remove(root , val);
    }
    bool count(int val){
        return dfs_count(root , val);
    }
    bool validate(){
        return dfs_validate(root);
    }

private:
    int get_height(Node *node){
        if(node == nullptr){
            return 0;
        }
        return node->height;
    }
    Node* dfs_insert(Node *cur , int val){
        //when we find a empty slot in the tree leaf level, we fill
        if(cur == nullptr){
            Node* newNode = new Node(val);
            newNode->height = 1;
            return newNode;
        }
        if(val >= cur->val){
            cur->right = dfs_insert(cur->right , val);
        }else{
            cur->left = dfs_insert(cur->left , val);
        }
        int left_height = get_height(cur->left) , right_height = get_height(cur->right);
        Node* res = cur;
        if(left_height - right_height > 1){
            //rotate_right
            res =  rotate_right(cur);
        }
        if(right_height - left_height > 1){
            //rotate_left
            res = rotate_left(cur);
        }
        cur->height = 1 + std::max(get_height(cur->left) , get_height(cur->right));
        return res;
    }
    void dfs_remove(Node*& cur , int val){
        if(cur == nullptr) return;
        if(cur->val == val){
            //remove the cur node
            delete cur;
            cur = nullptr;
            return;
        }
        if(cur->val > val){
            dfs_remove(cur->left , val);
        }else{
            dfs_remove(cur->right , val);
        }

        //maintain the AVL tree
        int left_height = get_height(cur->left) , right_height = get_height(cur->right);
        if(left_height - right_height > 1){
            //rotate_right
            rotate_right(cur);
        }
        if(right_height - left_height > 1){
            //rotate_left
            rotate_left(cur);
        }
        cur->height = 1 + std::max(get_height(cur->left) , get_height(cur->right));
        return;
    }
    Node* rotate_left(Node* x){
        Node *y = x->right;
        Node *temp = y->left;
        y->left = x;
        x->right = temp;

        //update height for x then y
        x->height = 1 + std::max(get_height(x->left) , get_height(x->right));
        y->height = 1 + std::max(get_height(y->left) , get_height(y->right));
        return y;
    }
    Node* rotate_right(Node* x){
        Node *y = x->left;
        Node *temp = y->right;
        y->right = x;
        x->left = temp;

        //update height for x then y
        x->height = 1 + std::max(get_height(x->left) , get_height(x->right));
        y->height = 1 + std::max(get_height(y->left) , get_height(y->right));
        return y;
    }
    bool dfs_count(Node *cur , int val){
        if(cur == nullptr) return false;
        if(cur->val == val){
            //cout << "found" << endl;
            return true;
        }
        if(cur->val > val){
            return dfs_count(cur->left , val);
        }else{
            return dfs_count(cur->right , val);
        }
    }
    bool dfs_validate(Node *cur){
        if(cur == nullptr) return true;
        //fail to meet AVL condition
        if(abs(get_height(cur->left) - get_height(cur->right)) > 1){
            return false;
        }

        //recursively check subtree
        return dfs_validate(cur->left) && dfs_validate(cur->right);
    }
};

int main(){
    AVL bst;
    bst.insert(1);
    bst.insert(1);
    bst.insert(1);
    bst.insert(1);
    bst.insert(10);
    bst.insert(11);
    bst.insert(12);
    bst.insert(1);
    bst.insert(17);
    bst.insert(1);
    bst.insert(17);
    bst.del(17);
    std::cout << bst.validate() << std::endl;
    bst.insert(17);
    std::cout << bst.validate() << std::endl;

}
