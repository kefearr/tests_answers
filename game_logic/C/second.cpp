#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class CircularBuffer {
public:
    CircularBuffer(size_t capacity)
        : capacity_(capacity), buffer_(capacity), size_(0), head_(0) {}

    bool isEmpty() const {
        return size_ == 0;
    }

    bool isFull() const {
        return size_ == capacity_;
    }

    void enqueue(const T& item) {
        if (isFull()) {
            // Если буфер заполнен, перезаписываем head элемент
            buffer_[head_] = item;
            head_ = (head_ + 1) % capacity_;
        } else {
            // Если буфер не заполнен, добавляем элемент в конец
            buffer_[(head_ + size_) % capacity_] = item;
            ++size_;
        }
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Buffer is empty");
        }
        T item = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return item;
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Buffer is empty" << std::endl;
            return;
        }

        std::cout << "CircularBuffer: ";
        size_t index = head_;
        for (size_t i = 0; i < size_; ++i) {
            std::cout << buffer_[index] << " ";
            index = (index + 1) % capacity_;
        }
        std::cout << std::endl;
    }

private:
    size_t capacity_;
    std::vector<T> buffer_;
    size_t size_;
    size_t head_;
};

int main() {
    CircularBuffer<std::string> cb(3);

    cb.enqueue("one");
    cb.enqueue("two");
    cb.enqueue("three");
    cb.enqueue("four");
    cb.enqueue("five");

    cb.display(); // CircularBuffer: three four five

    cb.enqueue("six");
    cb.display(); // CircularBuffer: four five six

    std::cout << "Dequeued: " << cb.dequeue() << std::endl; // Dequeued: four
    cb.display(); // CircularBuffer: five six
    cb.enqueue(std::to_string(7));
    cb.display(); // CircularBuffer: five six 7

    return 0;
}