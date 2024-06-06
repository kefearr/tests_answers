#include <iostream>
#include <deque>
#include <stdexcept>
#include <memory>

class BaseItem {
public:
    virtual ~BaseItem() {}
    virtual void display() const = 0;
};

template <typename T>
class Item : public BaseItem {
public:
    Item(const T& value) : value_(value) {}

    void display() const override {
        std::cout << value_;
    }

private:
    T value_;
};

class CircularBuffer {
public:
    CircularBuffer(size_t capacity) : capacity_(capacity) {}

    bool isEmpty() const {
        return buffer_.empty();
    }

    bool isFull() const {
        return buffer_.size() == capacity_;
    }

    template <typename T>
    void enqueue(const T& item) {
        if (isFull()) {
            buffer_.pop_front(); // Удаляем первый элемент, если буфер полон
        }
        buffer_.push_back(std::make_shared<Item<T>>(item));
    }

    std::shared_ptr<BaseItem> dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Buffer is empty");
        }
        auto item = buffer_.front();
        buffer_.pop_front();
        return item;
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Buffer is empty" << std::endl;
            return;
        }

        std::cout << "CircularBuffer: ";
        for (const auto& item : buffer_) {
            item->display();
            std::cout << " ";
        }
        std::cout << std::endl;
    }

private:
    size_t capacity_;
    std::deque<std::shared_ptr<BaseItem>> buffer_;
};

int main() {
    CircularBuffer cb(3);

    cb.enqueue(1);
    cb.enqueue(2.5);
    cb.enqueue(std::string("three"));
    cb.enqueue(std::string("four"));
    cb.enqueue('5');
    cb.display(); // CircularBuffer: three four 5 

    cb.enqueue(std::string("six"));
    cb.display(); // CircularBuffer: four 5 six

    auto dequeuedItem = cb.dequeue();
    std::cout << "Dequeued: ";
    dequeuedItem->display(); // Dequeued: four
    std::cout << std::endl;
    
    cb.display(); // CircularBuffer: 5 six

    return 0;
}