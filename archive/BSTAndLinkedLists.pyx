#distutils: language = c++
ctypedef Py_ssize_t ind
ctypedef int bstVal
cimport cython
from libc.stdlib cimport malloc, free
from cython cimport sizeof as size
from libcpp.list cimport list as llist
cimport cython.operator.dereference as deref
cimport cython.operator.preincrement as preincrement

cdef bstNode* nullBSTNodePtr
cdef struct bstNode:
    int key
    bstVal val
    bstNode* left
    bstNode* right



cdef bstNode* makeBSTNode(bstVal* valPtr, int key):
    cdef bstNode* ptr = <bstNode*>malloc(size(bstNode))
    ptr[0].key = key
    ptr[0].val = valPtr[0]
    ptr[0].left = NULL
    ptr[0].right = NULL
    return ptr



cdef bstNode* makeBSTNodeWithVal(bstVal val, int key):
    cdef bstNode* ptr = makeBSTNode(&val, key)
    return ptr

cdef bstNode* addItemToNode(bstNode* nodePtr, bstVal* valPtr, int key):
    cdef bstNode* newNodePtr
    if nodePtr == NULL:
        newNodePtr = makeBSTNode(valPtr, key)
        return newNodePtr
    if key < nodePtr[0].key: # try left
        nodePtr[0].left = addItemToNode(nodePtr[0].left, valPtr, key)
        return nodePtr
    else: # try right
        nodePtr[0].right = addItemToNode(nodePtr[0].right, valPtr, key)
        return nodePtr

cdef bstAddItem(BST* bstPtr, bstVal val, int key):
    if bstPtr[0].root == NULL:
        bstPtr[0].root = makeBSTNode(&val, key)
    else:
        addItemToNode(bstPtr[0].root, &val, key)
    bstPtr[0].num += 1

cdef void traverseNodePop(bstNode* node, llist[bstVal]* llistPtr):
    if node != NULL:
        traverseNodePop(node[0].left, llistPtr)
        llistPtr[0].push_back(node[0].val)
        traverseNodePop(node[0].right, llistPtr)
        free(node)


cdef void traverseNodePrint(bstNode* node):
    if node != NULL:
        traverseNodePrint(node[0].left)
        print(node[0].key, node[0].val)
        traverseNodePrint(node[0].right)
    else:
        pass






cdef void traverseTreePop(BST* tree, llist[bstVal]* ll):
    print('attempting tree')
    traverseNodePop(tree[0].root, ll)
    free(tree)

cdef void traverseTreePrint(BST* tree):
    print('attempting tree')
    traverseNodePrint(tree[0].root)


cdef struct BST:
    bstNode* root
    int num




cdef BST* tree = <BST*>malloc(size(BST))
tree[0].num = 0
tree[0].root = NULL
bstAddItem(tree, 1, 1)
bstAddItem(tree, 0, 0)
bstAddItem(tree, 2, 2)
iterate()
print('done once')
iterate()

def add(item):
    bstAddItem(tree, <int> item, <int> item)


cpdef iterate():
    cdef llist[bstVal] LL = llist[int]()
    cdef llist[bstVal].iterator it, end
    traverseTreePop(tree, &LL)
    it = LL.begin()
    end = LL.end()

    while it != end:
        print(deref(it))
        preincrement(it)



#Linked list stuff from stack overflow
'''
cdef struct CDLinkedList:
    ListNode* head
    int length

cdef struct ListNode:
    ListNode** links #[0] = previous, [1] = next or vice versa, doesn't matter.
    void* data

cdef ListNode* list_node_create(void* data) nogil:
    cdef ListNode* n = <ListNode *> malloc(sizeof(ListNode))
    n.links = <ListNode **> malloc(sizeof(ListNode*) * 2)
    n.data = data
    return n

cdef inline void listNodeFree(ListNode* node) nogil:
    free(node.links)
    free(node)

cdef CDLinkedList* listCreate() nogil:
    cdef CDLinkedList* lst = <CDLinkedList *> malloc(sizeof(CDLinkedList))
    lst.head = list_node_create(NULL)
    lst.head.links[0] = lst.head
    lst.head.links[1] = lst.head
    lst.length = 0
    return lst

cdef void listFree(CDLinkedList* lst) nogil:
    while lst.length > 0:
        list_pop(lst, 0)
    listNodeFree(lst.head)
    free(lst)

cdef void list_insert(CDLinkedList* lst, void* data, int link_side) nogil:
    cdef:
        int next = link_side
        int prev = 1 - link_side
        ListNode* next_node = lst.head.links[next]
        ListNode* new_node = list_node_create(data)
    next_node.links[prev] = new_node
    lst.head.links[next] = new_node
    new_node.links[prev] = lst.head
    new_node.links[next] = next_node
    lst.length += 1

cdef void* list_pop(CDLinkedList* lst, int link_side) nogil:
    if lst.length <= 0:
        return NULL
    cdef:
        int next = link_side
        int prev = 1 - link_side
        ListNode* next_node = lst.head.links[next]
        ListNode* next_next_node = next_node.links[next]
        void* data = next_node.data
    lst.head.links[next] = next_next_node
    next_next_node.links[prev] = lst.head
    listNodeFree(next_node)
    lst.length -= 1
    return data
'''








