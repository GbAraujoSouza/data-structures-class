import random
class Node:
    def __init__(self, data) -> None:
        self.data = data
        self.left = None
        self.right = None

    def __str__(self) -> str:
        return str(self.data)

class BinaryTree:
    def __init__(self, data=None, node=None) -> None:
        if node:
            self.root = node
        elif data:
            self.root = Node(data)
        else:
            self.root = None

    # print in-order
    def traverseInOrder(self, node=None):
        if node is None:
            node = self.root
        if node.left:
            self.traverseInOrder(node.left)
        print(node, end=" ")
        if node.right:
            self.traverseInOrder(node.right)

class BinarySearchTree(BinaryTree):
    def insert(self, val):
        parent = None
        x = self.root
        while(x):
            parent = x
            if val < x.data:
                x = x.left
            else:
                x = x.right
        if parent is None:
            self.root = Node(val)
            return
        if parent.data < val:
            parent.right = Node(val)
        else:
            parent.left = Node(val)

    def search(self, val):
        return self._search(val, self.root)

    def _search(self, val, node):
        if node is None:
            return node
        if node.data == val:
            return BinarySearchTree(node)
        if val < node.data:
            return self._search(val, node.left)
        return self._search(val, node.right)

if __name__ == "__main__":
    tree = BinarySearchTree()
    random.seed(77)
    values = random.sample(range(1,1000), 42)

    for value in values:
        tree.insert(value)

    tree.traverseInOrder()
    print()

    items = [1, 3, 981, 520, 510, 100]
    for item in items:
        r = tree.search(item)
        if r is None:
            print(item, "Nao encontrado")
        else:
            print(r.root.data, "encontrado") # lembrando que search retorna uma subarbore


