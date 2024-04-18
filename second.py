# Вопрос №2

# На языке Python написать минимум по 2 класса реализовывающих циклический 
# буфер FIFO. Объяснить плюсы и минусы каждой реализации.

# Оценивается:

#     Полнота и качество реализации
#     Оформление кода
#     Наличие сравнения и пояснения по быстродействию

# первый вариант - первым пришедший
# плюсы - просто и быстро без лишних связей, как будто статическое 
# выделение памяти, но правда стоит сразу выделить достаточно памяти для 
# максимально возможного элемента, добавление/удаление О(1)
# минусы - по факту буфер всегда заполнен, происходит лишь сдвиг для записи.
# 
# 

class CircularBuffer:
    def __init__(self, capacity):
        self.capacity = capacity
        self.buffer = [None] * capacity
        self.size = 0
        self.head = 0

    def is_empty(self):
        return self.size == 0

    def is_full(self):
        return self.size == self.capacity

    def enqueue(self, item):
        if self.is_full():
            # Если буфер заполнен, перезаписываем head элемент
            self.buffer[self.head] = item
            self.head = (self.head + 1) % self.capacity
        else:
            # Если буфер не заполнен, добавляем элемент в конец
            self.buffer[(self.head + self.size) % self.capacity] = item
            self.size += 1

    def dequeue(self):
        if self.is_empty():
            # raise IndexError("Buffer is empty")
            return None
        item = self.buffer[self.head]
        self.head = (self.head + 1) % self.capacity
        self.size -= 1
        return item
    
    # вообще для проверки сделал, по сути не нужно
    def display(self):
        if self.is_empty():
            print("Buffer is empty")
            return None
        
        print("CircularBuffer:", end=" ")
        index = self.head
        for _ in range(self.size):
            print(self.buffer[index], end=" ")
            index = (index + 1) % self.capacity
        print()


# второй вариант на основе двусвязного списка
# плюсы - как будто динамическое использование памяти, что как будто выгоднее, 
# дальше в минусах
# скорость вставки и удаления тоже О(1).
#
# минусы - сложнее для чтения и понимания, память с другой стороны постоянно 
# выделять новую, тоже так себе, там потом обращения в разные места
# это все увеличивает время в теории

class Node:
    def __init__(self, value=None):
        self.value = value
        self.next = None
        self.prev = None

class CircularBuffer_2:
    def __init__(self, capacity):
        self.capacity = capacity
        self.size = 0
        self.head = None
        self.tail = None

    def is_empty(self):
        return self.size == 0

    def is_full(self):
        return self.size == self.capacity

    def enqueue(self, item):
        new_node = Node(item)
        
        if self.is_full():
            # Если буфер полный, перезаписываем старое значение
            self.head.value = item
            self.head = self.head.next
            self.tail = self.tail.next
        else:
            # если пустой содаем
            if self.is_empty():
                self.head = new_node
                self.tail = new_node
                new_node.next = new_node
                new_node.prev = new_node
            # меняем связи в иных случаях
            else:
                new_node.prev = self.tail
                new_node.next = self.head
                self.tail.next = new_node
                self.head.prev = new_node
                self.tail = new_node
            self.size += 1

    def dequeue(self):
        # пишите в тз что должно быть в разных случаях
        if self.is_empty():
            # raise IndexError("Buffer is empty")
            return None
        
        item = self.head.value
        
        if self.size == 1:
            self.head = None
            self.tail = None
        else:
            self.head = self.head.next
            self.tail.next = self.head
            self.head.prev = self.tail
        
        self.size -= 1
        return item
    
    # для проверки
    def display(self):
        if self.is_empty():
            print("Buffer is empty")
            return None
        
        current = self.head
        print("CircularBuffer:", end=" ")
        for _ in range(self.size):
            print(current.value, end=" ")
            current = current.next
        print()

# 3 вариант с использованием очереди
# плюсы - легко читать, наследование позволяет не писать методы с нуля,
#  О(1), можно легко изменить под многопоточность 
# так как методы queue ее поддерживают 
# минусы - наследование привязывает к изначальному классу, 
# если все же нужна многоп1оточность, нужно менять метод put, 
# чтобы избежать блокировок
from queue import Queue, Empty

class CircularBuffer_3(Queue):
    def __init__(self, capacity):
        super().__init__(maxsize=capacity)
        self.capacity = capacity

    #перегружаем пут, чтобы циклично заменять самый старый элемент
    def put(self, item, block=False):
        if self.full():
            # Если очередь полная, удаляем самый старый элемент
            try:
                self.get()
            except Empty:
                pass
        super().put(item, block)

    def get(self, block=False):
        try:
            return super().get(block)
        except Empty:
            return None


    def display(self):
        if self.empty():
            print("Buffer is empty")
            return
        
        print("CircularBuffer:", end=" ")
        queue_items = list(self.queue)
        print(" ".join(map(str, queue_items)))


if __name__ == "__main__":
    buf = CircularBuffer_3(capacity=3)
