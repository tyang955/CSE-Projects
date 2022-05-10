"""
PROJECT 2 - Recursion
Name: Tianhao Yang
PID: A54555923
"""

class LinkedNode:
    # DO NOT MODIFY THIS CLASS #
    __slots__ = 'value', 'next_node'

    def __init__(self, value, next_node = None):
        """
        DO NOT EDIT
        Initialize a node
        :param value: value of the node
        :param next_node: pointer to the next node, default is None
        """
        self.value = value  # element at the node
        self.next_node = next_node  # reference to next node


    def __repr__(self):
        """
        DO NOT EDIT
        String representation of a node
        :return: string of value
        """
        return str(self.value)

    __str__ = __repr__


def insert(value, node=None):
    """
    Insert the given value into the linked list that has head node
    :param :value that going to be inserted
    :param :linked list's head node
    :return:Return the starting node of the linked list
    """
    if node is None:
        node = LinkedNode(value, next_node=None)
        return node
    if node.next_node is not None:
        insert(value, node.next_node)
    else:
        node.next_node = LinkedNode(value, next_node=None)
    return node


def string(node):
    """
    Generate and return a string representation of the list, starting at node
    :param :the head node
    :return:return a string representation of the list
    """
    if node is None:
        return ""
    if node.next_node is None:
        return str(node.value)
    else:
        return str(node.value) + ", " + string(node.next_node)


def remove(value, node):
    """
    Remove the first node in the list with the given value starting at head node
    :param : value that is going to remove
    :param : the head node
    :return:Return the starting node of the linked list
    """
    if node is None:
        return node
    if node.value == value:
        node = node.next_node
        return node
    else:
        node.next_node = remove(value, node.next_node)
    return node


def remove_all(value, node):
    """
    Remove all nodes in the list with the given value starting at head node
    :param : the value key that is going to be removed
    :param : head node
    :return: Return the starting node of the linked list
    """
    if node is None:
        return node
    if node.value == value:
        node = node.next_node
        if node is not None:
            node = remove_all(value, node)
        return node
    if node.next_node is not None:
        node.next_node = remove_all(value, node.next_node)
    return node


def search(value, node):
    """
    Looks for value in list starting with head node
    :param : The value key that is going to search
    :param : The head node
    :return:Returns True if the value is in the list and False if it is not in the list
    """
    if node is None:
        return False
    if node.value == value:
        return True
    if node.next_node is not None:
        if search(value, node.next_node):
            return True
    else:
        return False


def length(node):
    """
    Calculates and returns the length of the list starting with head node
    :param : Head node
    :return: returns the length of the list
    """
    if node is None:
        return 0
    if node.next_node is None:
        return 1
    else:
        return 1 + length(node.next_node)


def sum_all(node):
    """
    Calculates and returns the sum of the list starting with head node
    :param : The head node
    :return: returns the sum of the list
    """
    if node is None:
        return 0
    if node.next_node is None:
        return node.value
    else:
        return node.value + sum_all(node.next_node)


def count(value, node):
    """
    Counts and returns how many times the given value occurs in the list starting at head node
    :param : value that is going to count for
    :param : head node
    :return: how many times the given value occurs in the list
    """
    if node is None:
        return 0
    if node.next_node is None:
        if node.value == value:
            return 1
    else:
        if node.value == value:
            return 1 + count(value, node.next_node)
        else:
            return count(value, node.next_node)
    return 0


# Application Problem
def palindrome(node, length, compare):
    """
    Determines if the list with head node and length length is a palindrome
    :param : the head node
    :param : the length of the list
    :param : the compare list
    :return: Boolean if the list is palindrome
    """

    if length == 1:
        compare[0] = node.next_node
        return True
    if length == 0:
        compare[0] = node
        return True
    if palindrome(node.next_node, length-2, compare):
        if node.value == compare[0].value:
            compare[0] = compare[0].next_node
            return True
        else:
            return False
    else:
        return False
