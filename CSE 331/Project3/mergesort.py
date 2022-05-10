"""
PROJECT 3 - Merge Sort
Name: Tianhao Yang
PID: A54555923
"""

from Project3.LinkedList import LinkedList


def merge_lists(lists, threshold):
    """
    This function will sort and combine every LinkedList in lists
    :param lists: a list of n different unsorted LinkedLists
    :param threshold: Use insertion sort when the LinkedList is smaller than or equal to the threshold
    :return: return the final LinkedList
    """
    final = LinkedList()
    for i in range(len(lists)):
        final = merge(final, (merge_sort(lists[i], threshold)))
    return final


def merge_sort(linked_list, threshold):
    """
    This function will use merge sort to sort the given linked list.
    :param :  an unsorted singly LinkedList
    :param threshold: Use insertion sort when the LinkedList is smaller than or equal to the threshold
    :return: return the sorted linked list
    """
    if linked_list.length() == 0:
        return linked_list
    if linked_list.length() > threshold:
        tuple = split_linked_list(linked_list)
        merge1 = merge_sort(tuple[0], threshold)
        merge2 = merge_sort(tuple[1], threshold)
        return merge(merge1, merge2)
    else:
        linked_list.insertion_sort()
    return linked_list


def split_linked_list(linked_list):
    """
    This function will take a linked list and split it in half.
    :param : a linked list
    :return: return a tuple of 2 linked lists.
    """
    i = 0
    if linked_list.length() == 0:
        return linked_list
    list1 = LinkedList()
    if linked_list.length() % 2 == 0:
        half = linked_list.length() // 2
        while i < half:
            list1.push_back(linked_list.pop_front())
            i += 1
        return list1, linked_list
    else:
        half = linked_list.length() // 2
        while i < half:
            list1.push_back(linked_list.pop_front())
            i += 1
        return list1, linked_list


def merge(list1, list2):
    """
    This function takes in 2 sorted LinkedLists and merges them together.
    :param: list1
    :param: list2
    :return: return one sorted linked list
    """
    final = LinkedList()
    while list1 is not None or list2 is not None:
        if list1.is_empty():
            while list2.length() >= 1:
                final.push_back(list2.pop_front())
            return final
        if list2.is_empty():
            while list1.length() >= 1:
                final.push_back(list1.pop_front())
            return final
        if list1.front_value() <= list2.front_value():
            final.push_back(list1.pop_front())
        else:
            final.push_back(list2.pop_front())
    return final
