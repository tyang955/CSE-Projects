"""
PROJECT 4 - QUEUES
Name: Tianhao Yang
PID: A54555923
"""


class CircularQueue:
    """
    Circular Queue Class
    """
    # DO NOT MODIFY THESE METHODS
    def __init__(self, capacity=4):
        """
        DO NOT MODIFY.
        Initialize the queue with an initial capacity
        :param capacity: the initial capacity of the queue
        """
        self.capacity = capacity
        self.size = 0
        self.data = [None] * capacity
        self.head = 0
        self.tail = 0


    def __eq__(self, other):
        """
        DO NOT MODIFY.
        Defines equality for two queues
        :return: true if two queues are equal, false otherwise
        """
        if self.capacity != other.capacity:
            return False
        for i in range(self.capacity):
            if self.data[i] != other.data[i]:
                return False
        return self.head == other.head and self.tail == other.tail and self.size == other.size

    def __str__(self):
        """
        DO NOT00 MODIFY.
        String representation of the queue
        :return: the queue as a string
        """
        if self.is_empty():
            return "Empty queue"
        result = ""
        str_list = [str(self.data[(self.head + i)%self.capacity]) for i in range(self.size)]
        return "Queue: " + (", ").join(str_list)

    # -----------MODIFY BELOW--------------
    def __len__(self):
        """
        Find the size of the queue
        :param :None
        :return:int
        """
        return self.size

    def is_empty(self):
        """
        FInd whether or not the queue is empty (bool)
        :param :None
        :return: Boolean
        """
        if self.size == 0:
            return True
        else:
            return False

    def head_element(self):
        """
        Find the front element of the queue
        :param :None
        :return:int
        """
        return self.data[self.head]

    def tail_element(self):
        """
        Returns the last element of the queue
        :param :None
        :return:int
        """
        if self.size == 0:
            return None
        return self.data[self.tail-1]

    def enqueue(self, val):
        """
        Add an element to the back of the queue
        :param val:The element that going to add
        :return: None
        """
        if self.size == self.capacity:
            self.grow()
        if val is None:
            return None
        self.size += 1
        self.data[self.tail] = val
        self.tail += 1
        if self.size == self.capacity:
            self.grow()
        if self.tail == self.capacity:
            self.tail = 0
        return None

    def dequeue(self):
        """
        Remove an element from the front of a queue.
        :param : None
        :return: Return element popped. If empty, return None
        """
        if self.size == 0:
            return None
        else:
            self.size -= 1
            val = self.data[self.head]
            self.data[self.head] = None
            self.head += 1
            if self.head == self.capacity:
                self.head = 0
        if self.capacity > 7:
            if self.size <= self.capacity // 4:
                self.shrink()
        return val

    def tail_dequeue(self):
        """
        Remove an element from the back of a queue
        :param :None
        :return:Return element popped. If empty, return None.
        """
        if self.capacity > 7:
            if self.size <= self.capacity // 4:
                self.shrink()
        if self.size == 0:
            return None
        else:
            val = self.data[self.tail-1]
            self.data[self.tail - 1] = None
            self.tail -= 1
            self.size -= 1
        if self.capacity > 7:
            if self.size <= self.capacity // 4:
                self.shrink()
        return val

    def grow(self):
        """
        Doubles the capacity of the queue immediately when capacity is reached to make room for new element
        Moves the head to the front of the newly allocated list
        :param :None
        :return:None
        """
        val = self.capacity
        self.capacity = self.capacity * 2
        data = [None] * self.capacity
        for i in range(self.size):
            data[i] = self.data[self.head]
            self.head += 1
            if self.head == val:
                self.head = 0
        self.data = data
        self.tail = self.size
        self.head = 0

    def shrink(self):
        """
        Halves the capacity of the queue immediately if the size is 1/4 or less of the capacity
        Capacity should never go below 4
        Moves the head to the front of the newly allocated list
        :param :None
        :return:None
        """
        val = self.capacity
        self.capacity = self.capacity // 2
        data = [None] * self.capacity
        for i in range(self.size):
            data[i] = self.data[self.head]
            self.head += 1
            if self.head == val:
                self.head = 0
        self.data = data
        self.tail = self.size
        self.head = 0


def greatest_val(w, values):
    """
    Find the greatest value in the list values at each possible array of size w using circuit queue
    :param :array size of w
    :param :value list that compute
    :return:New list with greatest value in array
    """
    final = []
    if values == final:
        return final
    temp = CircularQueue()
    for i in values:
        temp.enqueue(i)
    for n in range(temp.__len__()-w+1):
        queue = CircularQueue()
        for i in range(w):
            queue.enqueue(values[i+n])
        max = queue.dequeue()
        while queue.is_empty() is False:
            temp = queue.dequeue()
            if temp > max:
                max = temp
        final.append(max)
    return final
