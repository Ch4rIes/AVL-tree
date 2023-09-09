

### AVL Tree Implementation in C++

An AVL (Adelson-Velsky and Landis) tree is a self-balancing binary search tree, where the difference between heights of left and right subtrees cannot be more than one for all nodes.

#### Features:
- **Balanced Insertion**: Ensures that the tree remains balanced after inserting a new node. If any node becomes unbalanced, the tree is restructured using left, right, or double rotations.
  
- **Balanced Deletion**: Deletes nodes while maintaining the AVL tree's balanced property. The tree is restructured if necessary after a node is removed.
  
- **Height Tracking**: Each node in the tree keeps track of its height to ensure efficient balancing operations.
  
- **Tree Validation**: Utility function to check if the tree satisfies the AVL property.

#### Usage:
Simply include the AVL tree class in your C++ project and use the provided public methods (`insert`, `del`, and `count`) to manipulate and query the tree.

