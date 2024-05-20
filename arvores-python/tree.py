class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

    def __str__(self):
        return str(self.data)

class BinaryTree:
    def __init__(self, data=None, node=None):
        if node:
            self.root = node
        elif data:
            self.root = Node(data)
        else:
            self.root = None
    
    def posOrderTraverse(self, node=None):
        if node is None:
            node = self.root
        if node.left:
            self.posOrderTraverse(node.left)
        if node.right:
            self.posOrderTraverse(node.right)
        print(node)

if __name__=="__main__":
    tree = BinaryTree()
    n1 = Node('3')
    n2 = Node('e')
    n3 = Node('5')
    n4 = Node('i')
    n5 = Node('r')
    n6 = Node('a')
    n7 = Node('n')
    n8 = Node('c')
    n9 = Node('v')
    n10 = Node('s')

    n1.left = n2
    n1.right = n3

    n2.left = n4
    n2.right = n5

    n3.left = n6

    n5.left = n7
    n5.right = n8

    n6.right = n9

    n8.right = n10

    tree.root = n1

    tree.posOrderTraverse()



