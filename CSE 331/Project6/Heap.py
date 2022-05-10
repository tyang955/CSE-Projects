'''
PROJECT 6 - Heaps
Name: Tianhao Yang
PID: A54555923
'''

class Node:
    """
    Class definition shouldn't be modified in anyway
    """
    __slots__ = ('_key', '_val')

    def __init__(self, key, val):
        self._key = key
        self._val = val

    def __lt__(self, other):
        return self._key < other._key or (self._key == other._key and self._val < other._val)

    def __gt__(self, other):
        return self._key > other._key or (self._key == other._key and self._val > other._val)

    def __eq__(self, other):
        return self._key == other._key and self._val == other._val

    def __str__(self):
        return '(k: {0} v: {1})'.format(self._key, self._val)

    __repr__ = __str__

    @property
    def val(self):
        """
        :return: underlying value of node
        """
        return self._val


class Heap:
    """
    Class definition is partially completed.
    Method signatures and provided methods may not be edited in any way.
    """
    __slots__ = ('_size', '_capacity', '_data')

    def __init__(self, capacity):
        self._size = 0
        self._capacity = capacity + 1  # additional element space for push
        self._data = [None for _ in range(self._capacity)]

    def __str__(self):
        return ', '.join(str(el) for el in self._data if el is not None)

    __repr__ = __str__

    def __len__(self):  # allows for use of len(my_heap_object)
        return self._size

#    DO NOT MODIFY ANYTHING ABOVE THIS LINE
#    Start of Student Modifications

    def _percolate_up(self):
        """
        When an element initially exists in the last spot of the underlying data list, percolate
         it up to its valid spot in the heap representation.
        :param :None
        :return:None
        """
        nodeindex = self.__len__() - 1
        while nodeindex > 0:
            parentindex = (nodeindex - 1) // 2
            if self._data[nodeindex].__gt__(self._data[parentindex]):
                return
            if self._data[nodeindex].__eq__(self._data[parentindex]):
                return
            if self._data[nodeindex].__lt__(self._data[parentindex]):
                temp = self._data[nodeindex]
                self._data[nodeindex] = self._data[parentindex]
                self._data[parentindex] = temp
                nodeindex = parentindex


    def _percolate_down(self):
        """
        When an element initially exists in the first spot of the underlying data list,
         percolate it down to its valid spot in the heap representation.
        :param :None
        :return:None
        """
        nodeIndex = 0
        while nodeIndex * 2 + 1 < self.__len__():
            if self._data[nodeIndex].__eq__(self._data[self._min_child(nodeIndex)]):
                return
            elif self._data[nodeIndex].__lt__(self._data[self._min_child(nodeIndex)]):
                return
            elif self._data[nodeIndex].__gt__(self._data[self._min_child(nodeIndex)]):
                temp = self._data[nodeIndex]
                index = self._min_child(nodeIndex)
                self._data[nodeIndex] = self._data[self._min_child(nodeIndex)]
                self._data[self._min_child(nodeIndex)] = temp
                nodeIndex = index


    def _min_child(self, i):
        """
        Given an index of a node, return the index of the smaller child.
        :param :int
        :return:int
        """
        if 2 * i + 1 >= self.__len__():
            return -1
        if 2 * i + 1 == self.__len__() - 1:
            return 2 * i + 1
        else:
            if self._data[2 * i + 1].__gt__(self._data[2 * i + 2]):
                return 2 * i + 2
            else:
                return 2 * i + 1

    def push(self, key, val):
        """
        Use the key and value parameters to add a Node to the heap.
        In the event that pushing will exceed the limit, you must pop
        the smallest element out after pushing in the new element.
        :param :string
        :param :int
        :return:None
        """
        if key is None or val is None:
            return None
        node = Node(key, val)
        self._data[self.__len__()] = node
        self._size += 1
        self._percolate_up()
        if self.__len__() == self._capacity:
            self.pop()

    def pop(self):
        """
        Removes the smallest element from the heap.
        :param :None
        :return:type same as Node.val
        """
        if self.__len__() == 0:
            return
        if self.__len__() == 1:
            temp = self._data[0].val
            self._data[0] = None
            self._size = 0
            return temp
        temp = self._data[0].val
        self._data[0] = self._data[self.__len__() - 1]
        self._data[self.__len__() - 1] = None
        self._size -= 1
        self._percolate_down()
        return temp

    @property  # do not remove
    def empty(self):
        """
        Checks if the heap is empty.
        :param :None
        :return:Bool
        """
        if self.__len__() == 0:
            return True
        else:
            return False

    @property  # do not remove
    def top(self):
        """
        Gives the root value.
        :param :None
        :return:type same as Node.val
        """
        if self.empty:
            return None
        else:
            return self._data[0].val

    @property  # do not remove
    def levels(self):
        """
        Returns all Node values on a single level into a list
        i.e. All node values in the first level  go in list at index 0,
        All node values in the second level, go in list at index 1, and so on and so forth.
        :param :None
        :return:List[List[Node]]
        """
        level = []
        if self.empty:
            return level
        num = 0
        index = 0
        while index < self.__len__():
            list = []
            for i in range(2**num):
                if self._data[index] is None:
                    if list is not None:
                        level.append(list)
                    return level
                list.append(self._data[index])
                index += 1
            level.append(list)
            num += 1
        return level

def most_x_common(vals, X):
    """
    Given a list of elements, return the X most commonly occurring elements.
    Example: most_x_common(['a', 'a', 'a', 'b', 'b', 'c'], 2) == {'a','b'}
    :param :list
    :param :int
    :return:set
    """
    dic = {}
    for val in vals:
        dic[val] = dic.get(val, 0) + 1
    heap = Heap(X)
    for the_key, the_frequency in dic.items():
        heap.push(the_frequency, the_key)
    answer = set()
    for i in range(X):
        answer.update(heap.pop())
    return answer

