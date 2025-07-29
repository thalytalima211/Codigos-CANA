class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class List:
    def __init__(self):
        self.start = None
        self.size = 0
    
    def insert(self, value):
        new = Node(value)
        if not self.start:
            self.start = new
        else:
            current = self.start
            while current.next:
                current = current.next
            current.next = new
        self.size += 1
    
    def bubbleSort(self):
        if self.size < 2:
            return 
        
        for _ in range(self.size):
            current = self.start
            while current and current.next:
                if current.value > current.next.value:
                    current.value, current.next.value = current.next.value, current.value
                current = current.next 

    def show(self):
        current = self.start
        while current:
            print(current.value, end=" -> ")
            current = current.next
        print("None")

list = List()

list.insert(5)
list.insert(6)
list.insert(-9)
list.insert(9)
list.insert(0)
list.insert(4)

list.show()
list.bubbleSort()
list.show()