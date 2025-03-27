#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm> // For std::swap

namespace custom_ds_algo {

    // 1. Singly Linked List
    template <typename T>
    class SinglyLinkedList {
    private:
        struct Node {
            T data;
            std::shared_ptr<Node> next;

            Node(const T& value) : data(value), next(nullptr) {}
        };

        std::shared_ptr<Node> head;

    public:
        SinglyLinkedList() : head(nullptr) {}

        // Copy constructor
        SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr) {
            if (other.head) {
                head = std::make_shared<Node>(other.head->data);
                auto currentOther = other.head->next;
                auto current = head;
                while (currentOther) {
                    auto newNode = std::make_shared<Node>(currentOther->data);
                    current->next = newNode;
                    current = newNode;
                    currentOther = currentOther->next;
                }
            }
        }

        // Move constructor
        SinglyLinkedList(SinglyLinkedList&& other) noexcept : head(std::move(other.head)) {
            other.head = nullptr;
        }

        // Destructor
        ~SinglyLinkedList() {} // The smart pointers will handle memory

        // Copy assignment
        SinglyLinkedList& operator=(const SinglyLinkedList& other) {
            if (this != &other) {
                SinglyLinkedList temp(other); // Use copy constructor
                std::swap(head, temp.head);
            }
            return *this;
        }

        // Move assignment
        SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
            if (this != &other) {
                head = std::move(other.head);
                other.head = nullptr;
            }
            return *this;
        }

        void insert(const T& value) {
            auto newNode = std::make_shared<Node>(value);
            if (!head) {
                head = newNode;
            } else {
                auto current = head;
                while (current->next) {
                    current = current->next;
                }
                current->next = newNode;
            }
        }

        void print() const {
            auto current = head;
            while (current) {
                std::cout << current->data << " -> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }

        T get(size_t index) const {
            auto current = head;
            size_t i = 0;
            while (current && i < index) {
                current = current->next;
                i++;
            }
            if (!current) {
                throw std::out_of_range("Index out of bounds");
            }
            return current->data;
        }

        void remove(size_t index) {
            if (!head) return;
            if (index == 0) {
                head = head->next;
                return;
            }
            size_t i = 0;
            auto current = head;
            while (current && current->next && i < index - 1) {
                current = current->next;
                i++;
            }
            if (current && current->next) {
                current->next = current->next->next;
            }
        }
    };

    // 2. Doubly Linked List
    template <typename T>
    class DoublyLinkedList {
    private:
        struct Node {
            T data;
            std::shared_ptr<Node> prev;
            std::shared_ptr<Node> next;

            Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
        };

        std::shared_ptr<Node> head;
        std::shared_ptr<Node> tail;

    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr) {}

          // Copy constructor
        DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr) {
            if (other.head) {
                head = std::make_shared<Node>(other.head->data);
                auto currentOther = other.head->next;
                auto current = head;
                while (currentOther) {
                    auto newNode = std::make_shared<Node>(currentOther->data);
                    newNode->prev = current;
                    current->next = newNode;
                    current = newNode;
                    currentOther = currentOther->next;
                }
                tail = current;
            }
        }

        // Move constructor
        DoublyLinkedList(DoublyLinkedList&& other) noexcept : head(std::move(other.head)), tail(std::move(other.tail)) {
            other.head = nullptr;
            other.tail = nullptr;
        }

        // Destructor
        ~DoublyLinkedList() {}

        // Copy assignment
        DoublyLinkedList& operator=(const DoublyLinkedList& other) {
            if (this != &other) {
                DoublyLinkedList temp(other);
                std::swap(head, temp.head);
                std::swap(tail, temp.tail);
            }
            return *this;
        }

        // Move assignment
        DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
            if (this != &other) {
                head = std::move(other.head);
                tail = std::move(other.tail);
                other.head = nullptr;
                other.tail = nullptr;
            }
            return *this;
        }

        void insertFront(const T& value) {
            auto newNode = std::make_shared<Node>(value);
            if (!head) {
                head = tail = newNode;
            } else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }

        void insertBack(const T& value) {
            auto newNode = std::make_shared<Node>(value);
            if (!tail) {
                head = tail = newNode;
            } else {
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
            }
        }

        void print() const {
            auto current = head;
            while (current) {
                std::cout << current->data << " <-> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }

        T get(size_t index) const{
            if(!head){
                throw std::out_of_range("List is empty");
            }
            size_t i=0;
            auto current = head;
            if(index < size()/2){
                while(current && i < index){
                    current = current->next;
                    i++;
                }
            }
            else{
                 i = size() -1;
                 current = tail;
                 while(current && i > index){
                    current = current->prev;
                    i--;
                 }
            }
            if(!current){
                 throw std::out_of_range("Index out of bounds");
            }
            return current->data;
        }

        size_t size() const {
            size_t count = 0;
            auto current = head;
            while (current) {
                count++;
                current = current->next;
            }
            return count;
        }

         void removeFront() {
            if (!head) return;
            if (head == tail) {
                head = tail = nullptr;
                return;
            }
            head = head->next;
            head->prev = nullptr;
        }

        void removeBack() {
            if (!tail) return;
            if (head == tail) {
                head = tail = nullptr;
                return;
            }
            tail = tail->prev;
            tail->next = nullptr;
        }
    };

    // 3. Stack
    template <typename T>
    class Stack {
    private:
        std::vector<T> data;

    public:
        Stack() {}

        void push(const T& value) {
            data.push_back(value);
        }

        T pop() {
            if (data.empty()) {
                throw std::out_of_range("Stack is empty");
            }
            T top = data.back();
            data.pop_back();
            return top;
        }

        T peek() const {
            if (data.empty()) {
                throw std::out_of_range("Stack is empty");
            }
            return data.back();
        }

        bool isEmpty() const {
            return data.empty();
        }
    };

    // 4. Queue
    template <typename T>
    class Queue {
    private:
        std::vector<T> data;

    public:
        Queue() {}

        void enqueue(const T& value) {
            data.push_back(value);
        }

        T dequeue() {
            if (data.empty()) {
                throw std::out_of_range("Queue is empty");
            }
            T front = data.front();
            data.erase(data.begin());
            return front;
        }

        T peek() const {
            if (data.empty()) {
                throw std::out_of_range("Queue is empty");
            }
            return data.front();
        }

        bool isEmpty() const {
            return data.empty();
        }
    };

    // 5. Binary Search Tree
    template <typename T>
    class BinarySearchTree {
    private:
        struct Node {
            T data;
            std::shared_ptr<Node> left;
            std::shared_ptr<Node> right;

            Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
        };

        std::shared_ptr<Node> root;

        // Helper function for insert
        std::shared_ptr<Node> insertRecursive(std::shared_ptr<Node> node, const T& value) {
            if (!node) {
                return std::make_shared<Node>(value);
            }
            if (value < node->data) {
                node->left = insertRecursive(node->left, value);
            } else if (value > node->data) {
                node->right = insertRecursive(node->right, value);
            }
            return node;
        }
        std::shared_ptr<Node> findMin(std::shared_ptr<Node> node){
            while(node->left){
                node=node->left;
            }
            return node;
        }

        std::shared_ptr<Node> deleteNode(std::shared_ptr<Node> node, const T& value) {
            if (!node) return nullptr;

            if (value < node->data) {
                node->left = deleteNode(node->left, value);
            } else if (value > node->data) {
                node->right = deleteNode(node->right, value);
            } else { // Found the node to delete
                // Case 1: No children or one child
                if (!node->left) {
                    auto temp = node->right;
                    return temp;
                } else if (!node->right) {
                    auto temp = node->left;
                    return temp;
                }
                // Case 2: Two children
                else {
                    auto minRight = findMin(node->right);
                    node->data = minRight->data;
                    node->right = deleteNode(node->right, minRight->data);
                }
            }
            return node;
        }

        void printInOrderRecursive(std::shared_ptr<Node> node) const {
            if (node) {
                printInOrderRecursive(node->left);
                std::cout << node->data << " ";
                printInOrderRecursive(node->right);
            }
        }

        bool searchRecursive(std::shared_ptr<Node> node, const T& value) const {
             if (!node) return false;
            if (node->data == value) return true;
            return value < node->data ? searchRecursive(node->left, value) : searchRecursive(node->right, value);
        }
    public:
        BinarySearchTree() : root(nullptr) {}

        void insert(const T& value) {
            root = insertRecursive(root, value);
        }

        void printInOrder() const {
            printInOrderRecursive(root);
            std::cout << std::endl;
        }
        void deleteValue(const T& value) {
            root = deleteNode(root, value);
        }

        bool search(const T& value) const{
            return searchRecursive(root, value);
        }
    };

    // 6. Sorting Algorithms

    // 6.1 Bubble Sort
    template <typename T>
    void bubbleSort(std::vector<T>& arr) {
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // 6.2 Selection Sort
    template <typename T>
    void selectionSort(std::vector<T>& arr) {
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; ++i) {
            size_t minIndex = i;
            for (size_t j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                std::swap(arr[i], arr[minIndex]);
            }
        }
    }

    // 6.3 Insertion Sort
    template <typename T>
    void insertionSort(std::vector<T>& arr) {
        size_t n = arr.size();
        for (size_t i = 1; i < n; ++i) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    // 7. Searching Algorithms

    // 7.1 Linear Search
    template <typename T>
    int linearSearch(const std::vector<T>& arr, const T& target) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == target) {
                return static_cast<int>(i); // Cast size_t to int
            }
        }
        return -1;
    }

    // 7.2 Binary Search (requires sorted array)
    template <typename T>
    int binarySearch(const std::vector<T>& arr, const T& target) {
        int left = 0;
        int right = static_cast<int>(arr.size()) - 1; // Cast size_t to int
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1; // Not found
    }

} // namespace custom_ds_algo

int main() {
    // 1. Singly Linked List Test
    std::cout << "Singly Linked List Test:" << std::endl;
    custom_ds_algo::SinglyLinkedList<int> list1;
    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.print();
    std::cout << "Element at index 1: " << list1.get(1) << std::endl;

    custom_ds_algo::SinglyLinkedList<int> list2 = list1; // Copy constructor
    std::cout << "List 2: ";
    list2.print();
    list2.remove(1);
    std::cout << "List 2 after removing element at index 1: ";
    list2.print();
    std::cout << "List 1 after removing element from list 2: ";
    list1.print();

    custom_ds_algo::SinglyLinkedList<int> list3 = std::move(list1); // Move constructor
    std::cout << "List 3 after moving data from list 1: ";
    list3.print();
    std::cout << "List 1 after moving its data to list 3: ";
    list1.print();

    // 2. Doubly Linked List Test
    std::cout << "\nDoubly Linked List Test:" << std::endl;
    custom_ds_algo::DoublyLinkedList<int> dll;
    dll.insertFront(1);
    dll.insertBack(2);
    dll.insertBack(3);
    dll.print(); // Output: 1 <-> 2 <-> 3 <-> nullptr
    std::cout << "Element at index 2: " << dll.get(2) << std::endl;
    std::cout << "Size of dll: " << dll.size() << std::endl;
    dll.removeFront();
    dll.removeBack();
    dll.print();

    //3. Stack test
     std::cout << "\nStack Test:" << std::endl;
    custom_ds_algo::Stack<int> myStack;
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    std::cout << "Top element: " << myStack.peek() << std::endl; // Output: 30
    std::cout << "Popped element: " << myStack.pop() << std::endl; // Output: 30
    std::cout << "Is stack empty? " << (myStack.isEmpty() ? "Yes" : "No") << std::endl; // Output: No

    // 4. Queue Test
    std::cout << "\nQueue Test:" << std::endl;
    custom_ds_algo::Queue<int> myQueue;
    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);
    std::cout << "Front element: " << myQueue.peek() << std::endl; // Output: 10
    std::cout << "Dequeued element: " << myQueue.dequeue() << std::endl; // Output: 10
     std::cout << "Is Queue empty? " << (myQueue.isEmpty() ? "Yes" : "No") << std::endl;

    // 5. Binary Search Tree Test
    std::cout << "\nBinary Search Tree Test:" << std::endl;
    custom_ds_algo::BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);
    std::cout << "In-order traversal: ";
    bst.printInOrder(); // Output: 2 3 4 5 6 7 8
    bst.deleteValue(5);
    std::cout << "In-order traversal after deleting 5: ";
    bst.printInOrder();
    std::cout << "Search for 4: " << (bst.search(4) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 10: " << (bst.search(10) ? "Found" : "Not Found") << std::endl;

    // 6. Sorting Algorithms Test
    std::cout << "\nSorting Algorithms Test:" << std::endl;
    std::vector<int> numbers = {5, 1, 4, 2, 8};
    std::vector<int> numbers2 = {5, 1, 4, 2, 8};
     std::vector<int> numbers3 = {5, 1, 4, 2, 8};

    custom_ds_algo::bubbleSort(numbers);
    std::cout << "Bubble Sort: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl; // Output: 1 2 4 5 8

    custom_ds_algo::selectionSort(numbers2);
    std::cout << "Selection Sort: ";
     for (int num : numbers2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    custom_ds_algo::insertionSort(numbers3);
      std::cout << "Insertion Sort: ";
     for (int num : numbers3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 7. Searching Algorithms Test
    std::cout << "\nSearching Algorithms Test:" << std::endl;
    std::vector<int> sortedNumbers = {1, 2, 4, 5, 8};
    int index1 = custom_ds_algo::linearSearch(sortedNumbers, 4);
    std::cout << "Linear Search: Index of 4: " << index1 << std::endl; // Output: 2
    int index2 = custom_ds_algo::binarySearch(sortedNumbers, 4);
    std::cout << "Binary Search: Index of 4: " << index2 << std::endl; // Output: 2
    int index3 = custom_ds_algo::binarySearch(sortedNumbers, 10);
    std::cout << "Binary Search: Index of 10: " << index3 << std::endl; // Output: -1

    return 0;
}