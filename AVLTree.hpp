//=================================================================================================================
/**
 *  Example of implementation of a class that defines an AVL tree.
 */
 //=================================================================================================================

#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

// Includes
#include <stdexcept>    // For std::out_of_range
#include <iostream>     // For std::cout
#include <vector>       // For std::vector

/**
 *  Structure that defines a node of an AVL tree.
 * 
 *  @tparam T   The type of the data stored in the node.
 */
template <typename T>
struct AVLNode {

    T data;             /**< The data value stored in the node. */

    int height;         /**< The height of the node. */

    AVLNode* left;      /**< Pointer to the child node on the left side. */

    AVLNode* right;     /**< Pointer to the child node on the right side. */


    /**
     *  Constructs a new AVLNode object with the given value.
     *
     *  @param[in]  value   The value to be stored in the node.
     */
    AVLNode(const T& value)
    {
        data = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }

    /**
     *  Constructs a new AVLNode object by moving the given value.
     *
     *  @param[in]  value   The value to be stored in the node.
     */
    AVLNode(T&& value)
    {
        data = std::move(value);
        left = nullptr;
        right = nullptr;
    }
};

/**
 *  Class that defines an AVL tree.
 *
 *  @tparam T   The type of the data stored in the AVL tree.
 */
template <typename T>
class AVLTree {

public:

    /**
     *  Constructs an empty search tree.
     */
    AVLTree() = default;

    /**
     *  Constructs an AVL tree with the given root node.
     *
     *  @param[in]  r   Pointer to the root node of the AVL tree.
     */
    AVLTree(AVLNode<T>* r) 
    {
        root_ = r;
    }

    /**
     *  Class destructor.
     */
    ~AVLTree() 
    {
        clear();
    }

    /**
     *  Returns the root node of the AVL tree.
     *
     *  @return Pointer to the root node of the AVL tree.
     */
    const AVLNode<T>* root() const 
    {
        return root_;
    }

    /**
     *  Returns the number of elements in the AVL tree.
     *
     *  @return The number of elements in the AVL tree.
     */
    unsigned long long size() const
    {
        return size(root_);
    }

    /**
     *  Returns the node with the minimum value in the AVL tree.
     *
     *  @return The node with the minimum value in the AVL tree.
     */
    const AVLNode<T>* find_min() const
    {
        return find_min(root_);
    }

    /**
     *  Returns the node with the maximum value in the AVL tree.
     *
     *  @return The node with the maximum value in the AVL tree.
     */
    const AVLNode<T>* find_max() const
    {
        return find_max(root_);
    }

    /**
     *  Clears the AVL tree.
     */
    void clear() 
    {
        clear(root_);
        root_ = nullptr;
    }

    /**
     *  Finds the node with the specified value.
     *
     *  @param[in]  value   The value to search for.
     * 
     *  @return Pointer to the node with the specified value, or nullptr if not found.
     */
    const AVLNode<T>* find(const T& value) const
    {
        return find(root_, value);
    }

    /**
     *  Inserts a new node with the given value into the AVL tree.
     *
     *  @param[in]  value   The value to insert.
     */
    void insert(const T& value) 
    {
        root_ = insert(root_, value);
    }

    /**
     *  Erases the node with the specified value from the AVL tree.
     *
     *  @param[in]  value   The value to delete.
     */
    void erase(const T& value) 
    {
        root_ = erase(root_, value);
    }

    /**
     *  Prints the contents of the AVL tree in preorder.
     */
    void print_preorder() const
    {
        print_preorder(root_);
    }

    /**
     *  Prints the contents of the AVL tree in inorder.
     */
    void print_inorder() const
    {
        print_inorder(root_);
    }

    /**
     *  Prints the contents of the AVL tree in postorder.
     */
    void print_postorder() const
    {
        print_postorder(root_);
    }

    /**
     *  Prints the AVL tree in a graphical way.
     */
    void print_tree() const
    {
        print_tree(root_);
    }

    /**
     *  Returns a vector with the elements of the tree in preorder.
     * 
     *  @return A vector with the elements of the tree in preorder.
     */
    std::vector<T> preorder_traversal() const
    {
        std::vector<T> res;
        preorder_traversal(root_, res);
        return res;
    }

    /**
     *  Returns a vector with the elements of the tree in inorder.
     * 
     *  @return A vector with the elements of the tree in inorder.
     */
    std::vector<T> inorder_traversal() const
    {
        std::vector<T> res;
        inorder_traversal(root_, res);
        return res;
    }

    /**
     *  Returns a vector with the elements of the tree in preorder.
     * 
     *  @return A vector with the elements of the tree in postorder.
     */
    std::vector<T> postorder_traversal() const
    {
        std::vector<T> res;
        postorder_traversal(root_, res);
        return res;
    }       

private:

    /**
     *  Returns the number of elements in the AVL tree from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start counting.
     * 
     *  @return The number of elements in the AVL tree from the given node.
     */
    unsigned long long size(AVLNode<T>* node) const
    {
        if (node == nullptr)
            return 0;

        return 1 + size(node->left) + size(node->right);
    }

    /**
     *  Clears the AVL tree starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start clearing.
     */
    void clear(AVLNode<T>* node) 
    {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);
        delete node;        
    }    

    /**
     *  Calculates the height of a node.
     *
     *  @param[in] node Pointer to the node to calculate the height.
     * 
     *  @return The height of the node.
     */
    int height(AVLNode<T>* node) const
    {
        return node ? node->height : 0;
    }

    /**
     *  Updates the height of a node.
     *
     *  @param[in] node Pointer to the node to update.
     */
    void update_height(AVLNode<T>* node)
    {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    /**
     *  Calculates the balance factor of a node.
     *
     *  @param[in] node Pointer to the node whose balance factor is to be calculated.
     * 
     *  @return The balance factor of the node.
     */
    int calculate_balance_factor(AVLNode<T>* node) const
    {
        return node ? height(node->right) - height(node->left) : 0;
    }

    /**
     *  Returns the node with the minimum value in the AVL tree
     *  starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start searching.
     *
     *  @return The node with the minimum value starting from the given node.
     */
    AVLNode<T>* find_min(AVLNode<T>* node) const
    {
        if (node == nullptr)
            throw std::out_of_range("The tree is empty.");

        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    /**
     *  Returns the node with the maximum value in the AVL tree
     *  starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start searching.
     *
     *  @return The node with the maximum value starting from the given node.
     */
    AVLNode<T>* find_max(AVLNode<T>* node) const
    {
        if (node == nullptr)
            throw std::out_of_range("The tree is empty.");

        while (node->right != nullptr)
            node = node->right;

        return node;
    }

    /**
     *  Finds the node with the specified value starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start searching.
     *  @param[in]  value   The value to search for.
     *
     *  @return Pointer to the node with the specified value, or nullptr if not found.
     */
    AVLNode<T>* find(AVLNode<T>* node, const T& value) const
    {
        if ((node == nullptr) || (value == node->data))
            return node;
        else if (value < node->data)
            return find(node->left, value);
        else
            return find(node->right, value);
    }    

    /**
     *  Inserts a new node with the given value into the AVL tree starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start inserting.
     *  @param[in]  value   The value to insert.
     *
     *  @return Pointer to the new node.
     */
    AVLNode<T>* insert(AVLNode<T>* node, const T& value)
    {
        if (node == nullptr)
            node = new AVLNode<T>(value);
        else if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node;

        // Update height and balance the node
        update_height(node);
        return balance(node);
    }

    /**
     *  Erases the node with the specified value from the AVL tree starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start deleting.
     *  @param[in]  value   The value to delete.
     *
     *  @return Pointer to the new node in the position of node. This is needed to update the parent node.
     */
    AVLNode<T>* erase(AVLNode<T>* node, const T& value)
    {
        if (node == nullptr)
            return node;

        if (value < node->data) {
            node->left = erase(node->left, value);      // The value is in the left subtree
        }
        else if (value > node->data) {
            node->right = erase(node->right, value);    // The value is in the right subtree
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                // The node has one child or no children
                AVLNode<T>* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else {
                // The node has two children
                AVLNode<T>* temp = find_max(node->left);
                node->data = temp->data;
                node->left = erase(node->left, temp->data);
            }
        }

        // Update height and balance the node
        update_height(node);
        return balance(node);
    }

    /**
     *  Simple rotation to the left.
     *
     *  @param[in] node Pointer to the current node.
     *
     *  @return Pointer to the new root node after the rotation.
     */
    AVLNode<T>* rotate_left(AVLNode<T>* node)
    {
        AVLNode<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        // Update heights
        update_height(node);
        update_height(newRoot);

        return newRoot;
    }

    /**
     * Simple rotation to the right.
     *
     * @param[in] node Pointer to the current node.
     *
     * @return Pointer to the new root node after the rotation.
     */
    AVLNode<T>* rotate_right(AVLNode<T>* node)
    {
        AVLNode<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        // Update heights
        update_height(node);
        update_height(newRoot);

        return newRoot;
    }

    /**
     * Left-right double rotation.
     *
     * @param[in] node Pointer to the current node.
     *
     * @return Pointer to the new root node after the rotation.
     */
    AVLNode<T>* rotate_left_right(AVLNode<T>* node)
    {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    /**
     * Right-left double rotation.
     *
     * @param[in] node Pointer to the current node.
     *
     * @return Pointer to the new root node after the rotation.
     */
    AVLNode<T>* rotate_right_left(AVLNode<T>* node)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    /**
     *  Balances the AVL tree starting from the given node.
     *
     *  @param[in] node Pointer to the node from which to start balancing.
     *
     *  @return Pointer to the new root node after balancing.
     */
    AVLNode<T>* balance(AVLNode<T>* node)
    {
        int bf = calculate_balance_factor(node);

        // Rotation to the left
        if (bf == 2) {
            if (calculate_balance_factor(node->right) >= 0)
                return rotate_left(node);
            else
                return rotate_right_left(node);
        }
        // Rotation to the right
        else if (bf == -2) {
            if (calculate_balance_factor(node->left) <= 0)
                return rotate_right(node);
            else
                return rotate_left_right(node);
        }

        return node;
    }

    /**
     *  Prints the contents of the AVL tree in preorder starting from the given node.
     * 
     *  @param[in]  node    Pointer to the node from which to start printing.
     */
    void print_preorder(AVLNode<T>* node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->data << " ";
        print_preorder(node->left);
        print_preorder(node->right);
    }

    /**
     *  Prints the contents of the AVL tree in inorder starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start printing.
     */
    void print_inorder(AVLNode<T>* node) const
    {
        if (node == nullptr)
            return;

        print_inorder(node->left);        
        std::cout << node->data << " ";
        print_inorder(node->right);
    }

    /**
     *  Prints the contents of the AVL tree in postorder starting from the given node.
     *
     *  @param[in]  node    Pointer to the node from which to start printing.
     */
    void print_postorder(AVLNode<T>* node) const
    {
        if (node == nullptr)
            return;

        print_postorder(node->left);
        print_postorder(node->right);
        std::cout << node->data << " ";
    }    

    /**
     *  Prints the AVL tree in a graphical way.
     *
     *  @param[in]  node        Pointer to the node from which to start printing.
     *  @param[in]  indent      The indentation string.
     *  @param[in]  isRight     Flag to indicate if the node is the right child of its parent.
     */
    void print_tree(AVLNode<T>* node, std::string indent = "", bool isRight = true) const
    {
        if (node == nullptr)
            return;

        print_tree(node->right, indent + (isRight ? "        " : " |      "), true);
        std::cout << indent;
        if (isRight) {
            std::cout << " /";
        }
        else {
            std::cout << " \\";
        }
        std::cout << "----- ";
        std::cout << node->data << "(bf=" << calculate_balance_factor(node) << ")" << std::endl;
        print_tree(node->left, indent + (isRight ? " |      " : "        "), false);
    }

    /**
     *  Obtains the contents of the AVL tree in preorder starting from the given node.
     *
     *  @param[in]  node        Pointer to the node from which to start printing.
     *  @param[out] traversal   Vector to store the elements of the tree.
     */
    void preorder_traversal(AVLNode<T>* node, std::vector<T>& traversal) const
    {
        if (node == nullptr)
            return;

        traversal.push_back(node->data);
        preorder_traversal(node->left, traversal);
        preorder_traversal(node->right, traversal);
    }

    /**
     *  Obtains the contents of the AVL tree in inorder starting from the given node.
     *
     *  @param[in]  node        Pointer to the node from which to start printing.
     *  @param[out] traversal   Vector to store the elements of the tree.
     */
    void inorder_traversal(AVLNode<T>* node, std::vector<T>& traversal) const
    {
        if (node == nullptr)
            return;

        inorder_traversal(node->left, traversal);
        traversal.push_back(node->data);
        inorder_traversal(node->right, traversal);
    }

    /**
     *  Obtains the contents of the AVL tree in postorder starting from the given node.
     *
     *  @param[in]  node        Pointer to the node from which to start printing.
     *  @param[out] traversal   Vector to store the elements of the tree.
     */
    void postorder_traversal(AVLNode<T>* node, std::vector<T>& traversal) const
    {
        if (node == nullptr)
            return;
        postorder_traversal(node->left, traversal);
        postorder_traversal(node->right, traversal);
        traversal.push_back(node->data);
    }


    AVLNode<T>* root_{ nullptr };    /**< Pointer to the root node of the AVL tree. */
};


#endif
//=================================================================================================================
//  END OF FILE
//=================================================================================================================