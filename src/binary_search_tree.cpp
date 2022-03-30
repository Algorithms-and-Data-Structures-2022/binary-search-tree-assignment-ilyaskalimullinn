#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    if (root_ == nullptr) {
      root_ = new Node(key, value);
      return;
    }
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node = find(key, root_);

    if (node != nullptr) {
      return node->value;
    }

    return std::nullopt;
  }

  bool BinarySearchTree::Contains(int key) const {
    // Write your code here...
    return (Find(key) != std::nullopt);
  }

  bool BinarySearchTree::IsEmpty() const {
    return (root_ == nullptr);
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    Node* node = find_min(root_);
    if (node == nullptr) return std::nullopt;
    return node->value;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    Node* node = find_max(root_);
    if (node == nullptr) return std::nullopt;
    return node->value;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node->key == key) {
      node->value = value;
      return;
    }
    if (node->key < key) {
      if (node->right == nullptr) {
        node->right = new Node(key, value);
        return;
      }
      insert(key, value, node->right);
      return;
    }
    if (node->left == nullptr) {
      node->left = new Node(key, value);
      return;
    }
    insert(key, value, node->left);
  }

  bool BinarySearchTree::remove(int key, Node*& node) {

    if (node == nullptr) return false;

    if (node->key == key) {

      //case 1: a leaf
      if (node->left == nullptr && node->right == nullptr) {
        if (node == root_) Clear();
        // finding a parent node for this node
        Node* parent_node = root_;
        Node* this_node = parent_node;
        while (this_node->key != key) {
          parent_node = this_node;
          this_node = (this_node->key > key) ? this_node->left : this_node->right;

        }
        if (parent_node->key > key) {
          parent_node->left = nullptr;
        } else {
          parent_node->right = nullptr;
        }
        delete this_node;
        return true;
      }

      //case 2: has one child on the left
      if (node->left != nullptr && node->right == nullptr) {
        Node* old_node = node;
        node = node->left;
        delete old_node;
        return true;
      }

      //case 3: has one child on the right
      if (node->left == nullptr && node->right != nullptr) {
        Node* old_node = node;
        node = node->right;
        delete old_node;
        return true;
      }

      //case 4: has two children
      Node* new_node = find_min(node->right);
      int key = new_node->key;
      int value = new_node->value;
      remove(new_node->key, root_);
      node->key = key;
      node->value = value;
      return true;
    }

    if (node->key < key) return remove(key, node->right);
    if (node->key > key) return remove(key, node->left);
  }

  void BinarySearchTree::clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;
    if (node->key < key) return find(key, node->right);
    return find(key, node->left);
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    return find_min(node->left);
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node == nullptr) return nullptr;
    if (node->right == nullptr) return node;
    return find_max(node->right);
  }

}  // namespace assignment