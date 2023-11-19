#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;
     bool red;
     bool black;

     Node() {
         left = nullptr;
         right = nullptr;
         parent = nullptr;
         red = true;
         black = false;
     }
     Node(T value){
         left = nullptr;
         right = nullptr;
         parent = nullptr;
         data = value;
         red = true;
         black = false;
     }

    void makeBlack(){
        black = true;
        red = false;
    }
    void makeRed(){
        red = true;
        black = false;
    }
};
template<typename T>
class Tree {
public:
    int size;
    Node<T> * root;

    Tree(){
        size = 0;
        root = nullptr;
    }
    ~Tree(){
        deleteAll(root);
        root = nullptr;
    }
    void deleteAll(Node<T>*curr){
        if(curr){
            deleteAll(curr->left);
            deleteAll(curr->right);
           delete curr;
        }
    }

     Node<int> * insertBST(T value){
        if(size == 0){
            root = new Node<int>(value);
            size++;
            return root;
        }
        Node<T>*temp = root;
        while(temp && temp->data !=value) {
            if (temp->data > value&&temp->left== nullptr) {
                temp->left = new Node<T>(value);
                temp->left->parent = temp;
                ++size;
                return temp->left;
            }
            if (temp->data < value&&temp->right== nullptr) {
                temp->right = new Node<T>(value);
                temp->right->parent = temp;
                ++size;
                return temp->right;
            }if (temp->data > value) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
    }

    void insertBRT(T value) {
        Node<T> *node = insertBST(value);
        node->makeRed();
        while (node != root && node->parent->red) {
            if (node->parent == node->parent->parent->left) {
                Node<T> *y = node->parent->parent->right;
                    if(y!= nullptr && y->red) {
                        node->parent->makeBlack();
                        y->makeBlack();
                        node->parent->parent->makeRed();
                        node = node->parent->parent;
                    }else {
                        if (node == node->parent->right) {
                            node = node->parent;
                            rotationL(node);
                        }
                        node->parent->makeBlack();
                        node->parent->parent->makeRed();
                        rotationR(node->parent->parent);
                    }
               }else{
                Node<T> *y = node->parent->parent->left;
                if(y!= nullptr && y->red) {
                    node->parent->makeBlack();
                    y->makeBlack();
                    node->parent->parent->makeRed();
                    node = node->parent->parent;
                }else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotationR(node);
                    }
                    node->parent->makeBlack();
                    node->parent->parent->makeRed();
                    rotationL(node->parent->parent);
                }
            }
        }
        root->makeBlack();
    }
    void rotationL(Node<T>*grand){
      Node<T> * temp = grand->right;
      grand->right = temp->left;
      if(grand->right != nullptr){
        grand->right->parent = grand;
      }
      if(grand->parent == nullptr){
          root = temp;
          temp->parent = nullptr;
      }else{
       temp->parent = grand->parent;
      if(grand==grand->parent->left){
          grand->parent->left = temp;
      }else{
          grand->parent->right = temp;
       }
      }
      temp->left = grand;
      grand->parent = temp;
    }
    void rotationR(Node<T>*grand){
        Node<T> * temp = grand->left;
        grand->left = temp->right;
        if(grand->left != nullptr){
            grand->left->parent = grand;
        }
        if(grand->parent == nullptr){
            root = temp;
            temp->parent = nullptr;
        }else{
            temp->parent = grand->parent;
            if(grand==grand->parent->right){
                grand->parent->right = temp;
            }else{
                grand->parent->left = temp;
            }
        }
        temp->right = grand;
        grand->parent = temp;
    }
    Node<T> * seacrh(T value){
        Node<T>*curr = root;
        while(curr&&curr->data !=value){
            if(curr->data > value)
                curr = curr->left;
            else
                curr = curr->right;
        }if(curr) {
            cout << curr->data;
            return curr;
        }
    }
    int HeightOfTree(Node<T> *node) {
        if(node == nullptr)
            return 0;
        int left, right;
        if (node->left != NULL) {
            left = HeightOfTree(node->left);
        }else
            left = -1;
        if (node->right != NULL) {
            right = HeightOfTree(node->right);
        }else
            right = -1;
        int max = left > right ? left : right;
        return max+1;
    }
    void in(){
        Node<T>* curr = root;
        while(curr){
            if (!curr->left){
                cout << curr->data << " ";
                curr = curr->right;
            }
            else {
                Node<T>* pre = curr->left;
                while(pre->right && pre->right != curr){
                    pre = pre->right;
                }
                if (!pre->right){
                    pre->right = curr;
                    curr = curr->left;
                }
                else {
                    pre->right = nullptr;
                    cout << curr->data << " ";
                    curr = curr->right;
                }
            }
        }
    }
    void pre(){
        Node<T>* curr = root;
        while(curr){
            if (!curr->left){
                cout << curr->data << (curr->red ? " (Red) " : " (Black) ");
                curr = curr->right;
            }
            else {
                Node<T>* pre = curr->left;
                while(pre->right && pre->right != curr){
                    pre = pre->right;
                }
                if (!pre->right){
                    cout << curr->data << (curr->red ? " (Red) " : " (Black) ");
                    pre->right = curr;
                    curr = curr->left;
                }
                else {
                    pre->right = nullptr;
                    curr = curr->right;
                }
            }
        }
    }
};

int main() {
     clock_t start,end;
     start = clock();
     Tree<int> tree;
     tree.insertBRT(10);
     tree.insertBRT(15);
     tree.insertBRT(12);
     tree.insertBRT(5);
     tree.insertBRT(30);
     tree.insertBRT(25);
     tree.insertBRT(35);
     tree.insertBRT(7);
     tree.insertBRT(2);
     tree.insertBRT(33);

     tree.in();
     cout << endl;

     tree.pre();
     cout << endl;

     tree.seacrh(25);
     cout<< endl;

     int height = tree.HeightOfTree(tree.root);
     cout<<"Height: "<<height<<endl;

     end = clock();
     cout<<"Program dziala "<<(float)(end-start)/CLOCKS_PER_SEC*1000000<<" mikrosekund"<<endl;
    return 0;
}
