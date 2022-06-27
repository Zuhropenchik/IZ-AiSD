#ifndef SELF_DEVELOPMENT_REDBLACKTREE_H
#define SELF_DEVELOPMENT_REDBLACKTREE_H
enum Color {
    Black, Red
};

template<class T>
struct TreeNode {
    T data;
    TreeNode *left;
    TreeNode *right;
    Color color;

    TreeNode();

    explicit TreeNode(T _data);
};

template<class T, class C>
class RedBlackTree {
public:
    explicit RedBlackTree(C &cmp);

    ~RedBlackTree();


    void Add(T _key);

    void Delete(T _key);
    
private:
    void delete_node(TreeNode<T> *key);

    TreeNode<T> *_root;
    C _cmp;
};


#endif //SELF_DEVELOPMENT_REDBLACKTREE_H
