########################################
# PROJECT 1 - Linked List
# Author:  Tianhao Yang
# PID: A54555923
########################################


class Node:
    # DO NOT MODIFY THIS CLASS #
    __slots__ = 'value', 'next_node'

    def __init__(self, value, next_node=None):
        """
        DO NOT EDIT
        Initialize a node
        :param value: value of the node
        :param next_node: pointer to the next node, default is None
        """
        self.value = value  # element at the node
        self.next_node = next_node  # reference to next node

    def __eq__(self, other):
        """
        DO NOT EDIT
        Determine if two nodes are equal (same value)
        :param other: node to compare to
        :return: True if nodes are equal, False otherwise
        """
        if other is None:
            return False
        if self.value == other.value:
            return True
        return False

    def __repr__(self):
        """
        DO NOT EDIT
        String representation of a node
        :return: string of value
        """
        return str(self.value)

    __str__ = __repr__


class LinkedList:
    def __init__(self):
        """
        DO NOT EDIT
        Create/initialize an empty linked list
        """
        self.head = None  # Node
        self.tail = None  # Node
        self.size = 0  # Integer

    def __eq__(self, other):
        """
        DO NOT EDIT
        Defines "==" (equality) for two linked lists
        :param other: Linked list to compare to
        :return: True if equal, False otherwise
        """
        if self.size != other.size:
            return False
        if self.head != other.head or self.tail != other.tail:
            return False

        # Traverse through linked list and make sure all nodes are equal
        temp_self = self.head
        temp_other = other.head
        while temp_self is not None:
            if temp_self == temp_other:
                temp_self = temp_self.next_node
                temp_other = temp_other.next_node
            else:
                return False
        # Make sure other is not longer than self
        if temp_self is None and temp_other is None:
            return True
        return False

    def __repr__(self):
        """
        DO NOT EDIT
        String representation of a linked list
        :return: string of list of values
        """
        temp_node = self.head
        values = []
        if temp_node is None:
            return None
        while temp_node is not None:
            values.append(temp_node.value)
            temp_node = temp_node.next_node
        return str(values)

    __str__ = __repr__

    ###### students modify the below functions #####

    # ------------------------Accessor Functions---------------------------

    def length(self):
        """
        returns the number of nodes in the list
        :return: size of the list
        """
        return self.size

    def is_empty(self):
        """
        returns true if the linked list is empty, false if it is not empty
        :return: True or False determine empty or not
        """
        if self.size > 0:
            return False
        else:
            return True

    def front_value(self):
        """
        returns the value of the front (head) node, None for empty lists
        :return: return the head value of the list
        """
        if self.head is None:
            return None
        return self.head.value

    def back_value(self):
        """
        returns the value of the back (tail) node, None for empty lists
        :return: return the Tail value of the list
        """
        if self.head is None:
            return None
        return self.tail.value

    def count(self, val):
        """
        takes a value ‘val’ and counts how many times that value occurs in the linked list,
        returns the number of occurrences
        :param : value x
        :return: the sum of the nodes in the list
        """
        num = 0
        temp = self.head
        while temp is not None:
            if temp.value == val:
                num += 1
            temp = temp.next_node
        return num

    def find(self, val):
        """
        takes a parameter ‘val’ and returns true if the value is found in the list, false if the value is not found
        :param : value x
        :return: True or False determine if find the fey in the list
        """
        temp = self.head
        while temp is not None:
            if temp.value == val:
                return True
            temp = temp.next_node
        return False

    # ------------------------Mutator Functions---------------------------

    def push_front(self, val):
        """
        takes a parameter ‘val’ and inserts a node with value ‘val’ at the front (head) of the linked list
        :param : value x
        :return: none
        """
        new_front = Node(val, self.head)
        if self.head is not None:
            self.head = new_front
            self.size += 1
        else:
            self.head = new_front
            self.tail = new_front
            self.size += 1

    def push_back(self, val):
        """
        takes a parameter ‘val’ and inserts a node with value ‘val’ at the back (tail) of the linked list
        :param : value x
        :return: none
        """
        new_back = Node(val)
        if self.head is None:
            self.head = new_back
            self.tail = new_back
            self.size += 1
        else:
            self.tail.next_node = new_back
            self.tail = new_back
            self.size += 1

    def pop_front(self):
        """
        removes the front (head) node of the linked list and returns the value of the removed node
        :return: none
        """
        if self.head is None:
            return None
        temp = self.head
        self.head = self.head.next_node
        self.size -= 1
        return temp.value

    def pop_back(self):
        """
        removes the back (tail) node of the linked list and returns the value of the removed node
        :return: none
        """
        temp = self.head
        last = None
        if self.head is None:
            return None
        while temp.next_node is not None:
            last = temp
            temp = temp.next_node
        if last is None:
            self.head = None
            self.tail = None
            self.size = 0
        else:
            last.next_node = None
            self.tail = last
            self.size -= 1
        return temp.value


def partition(linked_list, x):
    """
    take the LinkedList object that is passed in as a parameter and partition it such that values less than the
    parameter x occur before values greater than or equal to x.
    :param : linked list, value x
    :return: the Linked_list after being partition
    """
    if linked_list.is_empty():
        return None
    for num in range(linked_list.length()):
        if linked_list.front_value() >= x:
            value = linked_list.pop_front()
            linked_list.push_back(value)
        else:
            continue
    return linked_list
