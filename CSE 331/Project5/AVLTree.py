'''
PROJECT 5 - AVL Trees
Name:Tianhao Yang
PID:A54555923
'''

import random as r      # To use for testing

class Node:
    # DO NOT MODIFY THIS CLASS #
    __slots__ = 'value', 'parent', 'left', 'right', 'height'

    def __init__(self, value, parent=None, left=None, right=None):
        """
        Initialization of a node
        :param value: value stored at the node
        :param parent: the parent node
        :param left: the left child node
        :param right: the right child node
        """
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right
        self.height = 0

    def __eq__(self, other):
        """
        Determine if the two nodes are equal
        :param other: the node being compared to
        :return: true if the nodes are equal, false otherwise
        """
        if type(self) is not type(other):
            return False
        return self.value == other.value

    def __str__(self):
        """String representation of a node by its value"""
        return str(self.value)

    def __repr__(self):
        """String representation of a node by its value"""
        return str(self.value)



class AVLTree:

    def __init__(self):
        # DO NOT MODIFY THIS FUNCTION #
        """
        Initializes an empty Binary Search Tree
        """
        self.root = None    # The root Node of the tree
        self.size = 0       # The number of Nodes in the tree

    def __eq__(self, other):
        # DO NOT MODIFY THIS FUNCTION #
        """
        Describe equality comparison for BSTs ('==')
        :param other: BST being compared to
        :return: True if equal, False if not equal
        """
        if self.size != other.size:
            return False
        if self.root != other.root:
            return False
        if self.root is None or other.root is None:
            return True  # Both must be None

        if self.root.left is not None and other.root.left is not None:
            r1 = self._compare(self.root.left, other.root.left)
        else:
            r1 = (self.root.left == other.root.left)
        if self.root.right is not None and other.root.right is not None:
            r2 = self._compare(self.root.right, other.root.right)
        else:
            r2 = (self.root.right == other.root.right)

        result = r1 and r2
        return result

    def _compare(self, t1, t2):
        # DO NOT MODIFY THIS FUNCTION #
        """
        Recursively compares two trees, used in __eq__.
        :param t1: root node of first tree
        :param t2: root node of second tree
        :return: True if equal, False if nott
        """
        if t1 is None or t2 is None:
            return t1 == t2
        if t1 != t2:
            return False
        result = self._compare(t1.left, t2.left) and self._compare(t1.right, t2.right)
        return result

    def visual(self):
        """
        Returns a visual representation of the AVL Tree in terms of levels
        :return: None
        """
        root = self.root
        if not root:
            print("Empty tree.")
            return
        bfs_queue = []
        track = {}
        bfs_queue.append((root, 0, root.parent))
        h = self.height(self.root)
        for i in range(h+1):
            track[i] = []
        while bfs_queue:
            node = bfs_queue.pop(0)
            track[node[1]].append(node)
            if node[0].left:
                bfs_queue.append((node[0].left, node[1] + 1, node[0]))
            if node[0].right:
                bfs_queue.append((node[0].right, node[1] + 1, node[0]))
        for i in range(h+1):
            print(f"Level {i}: ", end='')
            for node in track[i]:
                print(tuple([node[0], node[2]]), end=' ')
            print()

    ### Implement/Modify the functions below ###

    def insert(self, node, value):
        """
        Takes in a value to be added in the form of a node to the tree
        Takes in the root of the (sub)tree the node will be added into
        :param node: root of the (sub)tree
        :param value:value to be added
        :return:None
        """
        if value is None:
            return
        add = Node(value)
        if self.root is None:
            self.root = add
            add.parent = None
            self.size += 1
            return
        cur = node
        if cur is None:
            return
        if add.value == cur.value:
            return
        if add.value < cur.value:
            if cur.left is None:
                cur.left = add
                add.parent = cur
                self.size += 1
            else:
                "recursion below !!!!!!"
                self.insert(cur.left,value)
        else:
            if cur.right is None:
                cur.right = add
                add.parent = cur
                self.size += 1
            else:
                "recursion below !!!!!!"
                self.insert(cur.right,value)
        add = add.parent
        while add is not None:
            self.rebalance(add)
            add = add.parent



    def remove(self, node, value):
        """
        Takes in a value to remove from the tree
        Takes in the root of the (sub)tree the node will be removed from
        Do nothing if the value is not found
        When removing a value with two children, replace with the maximum of the left subtree
        Return the root of the subtree
        :param node: root of the (sub)tree the node
        :param value: value to remove
        :return:Return the root of the subtree
        """
        if value is None:
            return node
        if node is None:
            return None
        if self.search(node,value).value == value:
            parent = self.search(node,value).parent
            root = self.search(node,value)

            if root.left is not None and root.right is not None:
                succnode = root.left
                while succnode.right is not None:
                    succnode = succnode.right
                temp = root.value
                root.value = succnode.value
                succnode.value = temp
                "recursion below !!!!!!"
                self.remove(succnode, temp)
            elif root == self.root:
                if root.left is not None:
                    self.root = root.left
                else:
                    self.root = root.right
                if self.root is not None:
                    self.root.parent = None
                self.size -= 1
            elif root.left is not None:
                if parent.left == root:
                    parent.left = root.left
                    if root.left is not None:
                        root.left.parent = parent
                    self.update_height(parent)
                elif parent.right == root:
                    parent.right = root.left
                    if root.left is not None:
                        root.left.parent = parent
                    self.update_height(parent)
                self.size -= 1
            else:
                if parent.left == root:
                    parent.left = root.right
                    if root.right is not None:
                        root.right.parent = parent
                    self.update_height(parent)
                elif parent.right == root:
                    parent.right = root.right
                    if root.right is not None:
                        root.right.parent = parent
                    self.update_height(parent)
                self.size -= 1
            nod = parent
            while nod is not None:
                self.rebalance(nod)
                nod = nod.parent
            if self.size == 0:
                return None
            return node
        else:
            return node

    def search(self, node, value):
        """
        Takes in a value to search for and a node which is the root of a given tree or subtree
        Returns the node with the given value if found, else returns the potential parent node
        :param node: node which is the root of a given tree or subtree
        :param value:value to search
        :return:
        """
        if value is None:
            return
        if self.root is None:
            return
        cur = node
        while cur is not None:
            if value == cur.value:
                return cur
            if value < cur.value:
                if cur.left is None:
                    return cur
                else:
                    cur = cur.left
            else:
                if cur.right is None:
                    return cur
                else:
                    cur = cur.right


    def inorder(self, node):
        """
        Returns a generator object of the tree traversed using the inorder method of traversal starting at the given node
        :param node:node which is the root of a given tree or subtree
        :return:Inorder form of tree
        """
        if node is None:
            return
        yield from self.inorder(node.left)
        yield node
        yield from self.inorder(node.right)


    def preorder(self, node):
        """
        Same as inorder, only using the preorder method of traversal
        :param node:node which is the root of a given tree or subtree
        :return:Preorder form of tree
        """
        if node is None:
            return
        yield node
        if node.left:
            yield from self.preorder(node.left)
        if node.right:
            yield from self.preorder(node.right)


    def postorder(self, node):
        """
        Same as inorder, only using the postorder method of traversal
        :param node:node which is the root of a given tree or subtree
        :return:Postorder form of tree
        """
        if node is None:
            return
        yield from self.postorder(node.left)
        yield from self.postorder(node.right)
        yield node


    def depth(self, value):
        """
        Returns the depth of the node with the given value
        :param value:node with the given value
        :return:depth of the node with the given value
        """
        if self.root is None:
            return -1
        depth = 0
        find = self.search(self.root,value)
        if find.value == value:
            while find != self.root:
                find = find.parent
                depth += 1
            return depth
        return -1

    def height(self, node):
        """
        Returns the height of the tree rooted at the given node
        :param node:node which is the root of a given tree or subtree
        :return:height of the tree rooted at the given node
        """
        if self.root is None:
            return -1
        return node.height


    def min(self, node):
        """
        Returns the minimum of the tree rooted at the given node
        :param node:node which is the root of a given tree or subtree
        :return:minimum of the tree
        """
        if self.root is None:
            return None
        if node is None or node.left is None:
            return node
        return self.min(node.left)

    def max(self, node):
        """
        Returns the maximum of the tree rooted at the given node
        :param node:node which is the root of a given tree or subtree
        :return:maximum of the tree rooted at the given node
        """
        if self.root is None:
            return None
        if node is None or node.right is None:
            return node
        return self.max(node.right)


    def get_size(self):
        """
        Returns the number of nodes in the AVL Tree
        :return:number of nodes in the AVL Tree
        """
        return self.size


    def get_balance(self, node):
        """
        Returns the balance factor of the node passed in
        Balance Factor = height of left subtree mins height of right subtree
        :param node:node which is the root of a given tree or subtree
        :return:Returns the balance factor of the node passed in
        """
        left_height = -1
        if node.left is not None:
            left_height = node.left.height
        right_height = -1
        if node.right is not None:
            right_height = node.right.height
        return left_height - right_height

    def left_rotate(self, root):
        """
        Performs an AVL left rotation on the subtree rooted at root
        Returns the root of the new subtree
        :param root:rotation root
        :return:root of the new subtree
        """
        RightleftChild = root.right.left
        if root.parent is not None:
            if root.parent.right == root:
                root.parent.right = root.right
                if root.right is not None:
                    root.right.parent = root.parent
                self.update_height(root.parent)
            elif root.parent.left == root:
                root.parent.left = root.right
                if root.right is not None:
                    root.right.parent = root.parent
                self.update_height(root.parent)
        else:
            if root.right is None:
                pass
            self.root = root.right
            self.root.parent = None
            root.parent = self.root

        root.right.left = root
        if root is not None:
            root.parent = root.right
            root.height -= 1
        self.update_height(root.right)
        root.right = RightleftChild
        if RightleftChild is not None:
            RightleftChild.parent = root
        self.update_height(root)

    def right_rotate(self, root):
        """
        Performs an AVL right rotation on the subtree rooted at root
        Returns the root of the new subtree
        :param root:rotation root
        :return:the root of the new subtree
        """
        leftRightChild = root.left.right
        if root.parent is not None:
            if root.parent.left == root:
                root.parent.left = root.left
                if root.left is not None:
                    root.left.parent = root.parent
                self.update_height(root.parent)
            elif root.parent.right == root:
                root.parent.right = root.left
                if root.left is not None:
                    root.left.parent = root.parent
                self.update_height(root.parent)
        else:
            self.root = root.left
            self.root.parent = None
            root.parent = self.root

        root.left.right = root
        if root is not None:
            root.parent = root.left
            root.height -= 1
        self.update_height(root.left)

        root.left = leftRightChild
        if leftRightChild is not None:
            leftRightChild.parent = root
        self.update_height(root)

    def rebalance(self, node):
        """
        Rebalances the subtree rooted at node, if needed
        Returns the root of the new, balanced subtree
        :param node:node which is the root of a given tree or subtree
        :return:the root of the new, balanced subtree
        """
        self.update_height(node)
        if self.get_balance(node) == -2:
            if self.get_balance(node.right) == 1:
                self.right_rotate(node.right)
            return self.left_rotate(node)
        elif self.get_balance(node) == 2:
            if self.get_balance(node.left) == -1:
                self.left_rotate(node.left)
            return self.right_rotate(node)
        return node


    def update_height(self, node) :
        """
            Update the height for the input node
            :param node:node which the height need to update
            :return:None
        """
        left_height = -1
        if node.left is not None:
           left_height = node.left.height
        right_height = -1
        if node.right is not None:
           right_height = node.right.height
        node.height = max(left_height, right_height) + 1

def repair_tree(tree):
    """
    Takes in a tree where two values may have been swapped, violating the BST property of nodes on the left
    being less than the parent node, and nodes on the right being larger than the parent node
    Repairs the tree by finding if two values have actually been swapped, and swapping them back if necessary
    :param tree:The tree that has two swapped node need to repair
    :return:None
    """
    if tree is None:
        return
    gen = tree.inorder(tree.root)
    size = tree.get_size()
    node1 = None
    node2 = None
    list = [None] * size
    for i in range(size):
        list[i]=next(gen, None)
    for i in range(size):
        if i < size-1:
            if list[i].value>list[i+1].value:
                if node1 is None:
                    node1=list[i]
        if i > 0:
            if list[i-1].value > list[i].value:
                node2 = list[i]
    if node1 is not None and node2 is not None:
        temp = node1.value
        node1.value = node2.value
        node2.value = temp


