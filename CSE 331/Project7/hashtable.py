'''
PROJECT 7 - Hash Tables
Name: Tianhao Yang
PID: A54555923
'''

class HashNode:
    """
    DO NOT EDIT
    """
    __slots__ = ["key", "value", "deleted"]

    def __init__(self, key, value, deleted=False):
        self.key = key
        self.value = value
        self.deleted = deleted

    def __repr__(self):
        return f"HashNode({self.key}, {self.value})"

    def __eq__(self, other):
        return self.key == other.key and self.value == other.value


class HashTable:
    """
    Hash Table Class
    """
    __slots__ = ['capacity', 'size', 'table', 'collisions', 'prime_index']

    primes = (
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
        89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
        181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
        281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
        397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
        503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617,
        619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
        743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
        863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991,
        997)

    def __init__(self, capacity=8):
        """
        DO NOT EDIT
        Initializes hash table
        :param capacity: capacity of the hash table
        """
        self.capacity = capacity
        self.size = 0
        self.table = [None] * capacity

        i = 0
        while HashTable.primes[i] <= self.capacity:
            i += 1
        self.prime_index = i - 1

    def __eq__(self, other):
        """
        DO NOT EDIT
        Equality operator
        :param other: other hash table we are comparing with this one
        :return: bool if equal or not
        """
        if self.capacity != other.capacity or self.size != other.size:
            return False
        for i in range(self.capacity):
            if self.table[i] != other.table[i]:
                return False
        return True

    def __repr__(self):
        """
        DO NOT EDIT
        Represents the table as a string
        :return: string representation of the hash table
        """
        represent = ""
        bin_no = 0
        for item in self.table:
            represent += "[" + str(bin_no) + "]: " + str(item) + '\n'
            bin_no += 1
        return represent

    def __setitem__(self, key, value):
        """
        DO NOT EDIT
        Allows for the use of the set operator to insert into table
        :param key: string key to insert
        :param value: value to insert
        :return: None
        """
        return self.insert(key=key, value=value)

    def __getitem__(self, item):
        """
        DO NOT EDIT
        Allows get operator to retrieve a value from the table
        :param item: string key of item to retrieve from tabkle
        :return: HashNode
        """
        return self.get(item)

    def __contains__(self, item):
        """
        DO NOT EDIT
        Checks whether a given key exists in the table
        :param item: string key of item to retrieve
        :return: Bool
        """
        if self.get(item) is not None:
            return True
        return False

    def _hash_1(self, key):
        """
        ---DO NOT EDIT---
        Converts a string x into a bin number for our hash table
        :param x: key to be hashed
        :return: bin number to insert hash item at in our table, -1 if x is an empty string
        """
        if not key:
            return None
        hashed_value = 0

        for char in key:
            hashed_value = 181 * hashed_value + ord(char)
        return hashed_value % self.capacity

    def _hash_2(self, key):
        """
        ---DO NOT EDIT---
        Converts a string x into a hash
        :param x: key to be hashed
        :return: a hashed value
        """
        if not key:
            return None
        hashed_value = 0

        for char in key:
            hashed_value = 181 * hashed_value + ord(char)

        prime = HashTable.primes[self.prime_index]

        hashed_value = prime - (hashed_value % prime)
        if hashed_value % 2 == 0:
            hashed_value += 1
        return hashed_value


    """ **************** Student Section Below ******************************"""

    def hash(self, key, inserting=False):
        """
        Double hashing.
        If the key exists in the hash table, return the index of the existing HashNode
        If the key does not exist in the hash table, return the index of the next available empty position in the hash table.
        :param : key string
        :param : boolean weather insert index or lookup/delete index
        :return: Index in the hash table
        """
        if key is None:
            return None
        i = 0
        bucketsProbed = 0
        while bucketsProbed < self.capacity:
            bucket = (self._hash_1(key) + i * self._hash_2(key)) % self.capacity
            if inserting is True:
                if self.table[bucket] is None or self.table[bucket] == HashNode(None, None, True):
                    return bucket
            if self.table[bucket] is not None:
                if self.table[bucket].key == key:
                    return bucket
            if self.table[bucket] is None:
                return bucket
            i = i + 1
            bucketsProbed = bucketsProbed + 1

        return None

    def insert(self, key, value):
        """
        Use the key and value parameters to add a HashNode to the hash table.
        :param : key to be insert
        :param : value to be insert
        :return: None
        """
        if key is None or value is None:
            return None
        index = self.hash(key, inserting=True)
        if index is None:
            return
        if self.table[index] is None or self.table[index] == HashNode(None, None, True):
            self.size += 1
        Node = HashNode(key, value)
        self.table[index] = Node
        if self.capacity < 500:
            if (self.size / self.capacity) >= 0.5:
                self.grow()

    def get(self, key):
        """
        Find the HashNode with the given key in the hash table.
        :param : key to get from the hash table
        :return: type HashNode
        """
        if key is None or self.size <= 0:
            return None
        index = self.hash(key, inserting=False)
        if index is None:
            return
        if self.table[index] is None:
            return None
        return self.table[index]

    def delete(self, key):
        """
        Removes the HashNode with the given key from the hash table
        :param : key to be delete
        :return: None
        """
        if key is None:
            return None
        index = self.hash(key, inserting=False)
        if index is None:
            return
        if self.table[index] is not None:
            self.table[index] = HashNode(None, None, True)
            self.size -= 1
        return None

    def grow(self):
        """
        Double the capacity of the existing hash table.
        Update self.prime_index
        :return: None
        """
        self.capacity = self.capacity*2
        i = 0
        while HashTable.primes[i] <= self.capacity:
            i += 1
        self.prime_index = i - 1
        temp = self.table
        self.table = [None] * self.capacity
        self.size = 0
        for Node in temp:
            if Node is not None and Node != HashNode(None, None, True):
                self.insert(Node.key, Node.value)



def word_frequency(string, lexicon, table):
    """
    Given a string S with no spaces or punctuation and a list of words
    (lexicon) return the frequency of the longest words in the string.
    :param string: type string
    :param lexicon: type List[string]
    :param table: type HashTable
    :return: a hashed table
    """
    temp = string
    temp2 = string
    while temp != "":
        if temp in lexicon:
            temp3 = temp2[:-len(temp)]
            for word in lexicon:
                if word in temp3 or temp3 == "":
                    if table.get(temp) is None:
                        table.insert(temp,1)
                        temp2= temp2[:-len(temp)]
                    else:
                        table.get(temp).value+=1
                        temp2 = temp2[:-len(temp)]
                    temp = temp2
                    break
                else:
                    if table.get(word) is None:
                        table.insert(word,0)
                if word == lexicon[-1]:
                    temp = temp[1:]
                    break
            continue
        temp = temp[1:]
    return table
