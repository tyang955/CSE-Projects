'''
PROJECT 8 - Graphs
Name: Tianhao Yang
PID: A54555923
'''

import random

def Generate_edges(size, connectedness):
    """
    DO NOT EDIT THIS FUNCTION
    Generates directed edges between vertices to form a DAG
    :return: A generator object that returns a tuple of the form (source ID, destination ID)
    used to construct an edge
    """

    assert connectedness <= 1
    random.seed(10)
    for i in range(size):
        for j in range(i + 1, size):
            if random.randrange(0, 100) <= connectedness * 100:
                yield f'{i} {j}'


# Custom Graph error
class GraphError(Exception): pass


class Vertex:
    """
    Class representing a Vertex in the Graph
    """
    __slots__ = ['ID', 'index', 'visited']

    def __init__(self, ID, index):
        """
        Class representing a vertex in the graph
        :param ID : Unique ID of this vertex
        :param index : Index of vertex edges in adjacency matrix
        """
        self.ID = ID
        self.index = index  # The index that this vertex is in the matrix
        self.visited = False

    def __repr__(self):
        return f"Vertex: {self.ID}"

    __str__ = __repr__

    def __eq__(self, other):
        """
        DO NOT EDIT THIS METHOD
        :param other: Vertex to compare
        :return: Bool, True if same, otherwise False
        """
        return self.ID == other.ID and self.index == other.index

    def out_degree(self, adj_matrix):
        """
        Given an adj_matrix, type: List[List[Optional[Vertex.ID]],
        return the number of out coming edges to its vertex
        :param adj_matrix: List[List[Optional[Vertex.ID]]
        :return: int
        """
        num = 0
        for vertex in adj_matrix[self.index]:
            if vertex is not None:
                num += 1
        return num

    def in_degree(self, adj_matrix):
        """
        Given an adj_matrix, type: List[List[Optional[Vertex.ID]],
        return the number of incoming edges to its vertex
        :param adj_matrix: List[List[Optional[Vertex.ID]]
        :return: int
        """
        num = 0
        for list in adj_matrix:
            if list[self.index] is not None:
                num += 1
        return num

    def visit(self):
        """
        Set the visit flag to seen
        :return: None
        """
        self.visited = True


class Graph:
    """
    Graph Class ADT
    """

    def __init__(self, iterable=None):
        """
        DO NOT EDIT THIS METHOD
        Construct a random Directed Graph
        :param size: Number of vertices
        :param: iterable: iterable containing edges to use to construct the graph.
        """
        self.id_map = {}
        self.size = 0
        self.matrix = []
        self.iterable = iterable
        self.construct_graph()
        if hasattr(iterable, 'close'):
            iterable.close()

    def __eq__(self, other):
        """
        DO NOT EDIT THIS METHOD
        Determines if 2 graphs are Identical
        :param other: Graph Object
        :return: Bool, True if Graph objects are equal
        """
        return self.id_map == other.id_map and self.matrix == other.matrix and self.size == other.size

    def get_vertex(self, ID):
        """
        Given an ID that is the same type as Vertex.ID,
        get the corresponding Vertex object.
        :param :  Vertex ID
        :return: Vertex
        """
        if ID in self.id_map:
            return self.id_map[ID]
        else:
            return None

    def get_edges(self, ID):
        """
        Given an ID with type: Vertex.ID, return the
        set of outgoing vertex ID's from the input vertex
        :return: Set[Vertex.ID]
        """
        out = set()
        ver = self.get_vertex(ID)
        if ver is None:
            return out
        index = ver.index
        for vertex_id in self.matrix[index]:
            if vertex_id is not None:
                out.add(vertex_id)
        return out


    def construct_graph(self):
        """
        Iterates through iterable and calls insert_edge to
        create the graph representation stored in self.matrix.
        :return: None
        """
        try:
            self.iterable = iter(self.iterable)
        except:
            raise GraphError
        for line in self.iterable:
            data = line.split()
            self.insert_edge(int(data[0]),int(data[1]))


    def insert_edge(self, source, destination):
        """
        Creates vertex objects, if needed, then adds edge representation
        into the matrix between the given source and destination, and updates self.id_map
        :param : source type: Vertex.ID
        :param : destination type: Vertex.ID
        :return: None
        """
        if self.get_vertex(source) is None:
            new_source = Vertex(source,self.size)
            self.matrix.append([None] * self.size)
            self.id_map[source] = new_source
            for list in self.matrix:
                list.append(None)
            self.size += 1
        if self.get_vertex(destination) is None:
            new_source = Vertex(destination, self.size)
            self.matrix.append([None] * self.size)
            self.id_map[destination] = new_source
            for list in self.matrix:
                list.append(None)
            self.size += 1
        index1 = self.get_vertex(source).index
        index2 = self.get_vertex(destination).index

        self.matrix[index1][index2] = destination

    def bfs(self, start, target, path=None):
        """
        Does a breadth first search to generate a path from start to target visiting a node only once.
        :param : start type: Vertex.ID
        :param : target type: Vertex.ID
        :return: Optional[List[Vertex.ID]]
        """
        all_path = []

        start_vertex = self.get_vertex(start)
        target_vertex = self.get_vertex(target)
        if start_vertex is None or target_vertex is None:
            return all_path

        temp_path = [start]

        all_path.append(temp_path)
        start_vertex.visit()

        while all_path:
            current = all_path.pop()

            if current[-1] is target:
                return current
            else:
                self.get_vertex(current[-1]).visit()
                edge_list = self.get_edges(current[-1])

                for edge in edge_list:
                    temp = current[:]
                    temp.append(edge)
                    all_path.insert(0, temp)


    def dfs(self, start, target, path=None):
        """
        Does a depth first search to generate a path from start to target visiting a node only once.
        :param : start type: Vertex.ID
        :param : target type: Vertex.ID
        :return: Optional[List[Vertex.ID]]
        """

        start_vertex = self.get_vertex(start)
        target_vertex = self.get_vertex(target)
        if start_vertex is None or target_vertex is None:
            return []
        mix = [[start]]
        while mix:
            cur = mix.pop(0)
            if cur[-1] is target:
                return cur
            else:
                self.get_vertex(cur[-1]).visit()
                edges = self.get_edges(cur[-1])
                for edge in edges:
                    mix.insert(0, cur[:] + [edge])


def find_k_away( K, iterable, start):
    """
    Given a starting ID and value K, return all vertex ID's that are K (inclusive) vertices away.
    :param K : int
    :param iterable : some iterable holding strings that represent edges
    :param start  : Vertex.ID
    """
    stu = Graph(iterable)
    result = set()
    start_vertex = stu.get_vertex(start)
    if start_vertex is None:
        return result
    mix_path = [[start]]
    start_vertex.visit()
    while mix_path:
        current = mix_path.pop()
        if len(current) is K+1:
            result.add(current[-1])
            continue
        edge_list = stu.get_edges(current[-1])
        for edge in edge_list:
            if stu.get_vertex(edge).visited is True:
                continue
            stu.get_vertex(current[-1]).visit()
            temp = current[:]
            temp.append(edge)
            mix_path.insert(0, temp)
    return result

