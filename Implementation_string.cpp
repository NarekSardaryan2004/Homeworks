#include <iostream>
#include <cstring>
#include <stdexcept>

class MyString {
private:
    static const size_t SSO_BUFFER_SIZE = 15;
    size_t size;
    union {
        char sso_data[SSO_BUFFER_SIZE + 1];
        struct {
            char* heap_data;
            size_t capacity;
        };
    };
    
    bool is_sso() const {
        return size <= SSO_BUFFER_SIZE;
    }

    void switch_to_heap(size_t new_capacity) {
        capacity = new_capacity;
        heap_data = new char[capacity + 1];
        std::strcpy(heap_data, sso_data);
    }

public:
    MyString() : size(0) {
        sso_data[0] = '\0';
    }

    MyString(const char* str) {
        size = std::strlen(str);
        if (size <= SSO_BUFFER_SIZE) {
            std::strcpy(sso_data, str);
        } else {
            capacity = size;
            heap_data = new char[capacity + 1];
            std::strcpy(heap_data, str);
        }
    }

    MyString(const MyString& other) {
        size = other.size;
        if (other.is_sso()) {
            std::strcpy(sso_data, other.sso_data);
        } else {
            capacity = other.capacity;
            heap_data = new char[capacity + 1];
            std::strcpy(heap_data, other.heap_data);
        }
    }

    MyString& operator=(const MyString& other) {
        if (this == &other) return *this;

        if (!is_sso()) {
            delete[] heap_data;
        }
        
        size = other.size;
        if (other.is_sso()) {
            std::strcpy(sso_data, other.sso_data);
        } else {
            capacity = other.capacity;
            heap_data = new char[capacity + 1];
            std::strcpy(heap_data, other.heap_data);
        }

        return *this;
    }

    MyString(MyString&& other) noexcept {
        size = other.size;
        if (other.is_sso()) {
            std::strcpy(sso_data, other.sso_data);
        } else {
            heap_data = other.heap_data;
            capacity = other.capacity;
            other.heap_data = nullptr;
            other.size = 0;
        }
    }

    MyString& operator=(MyString&& other) noexcept {
        if (this == &other) return *this;

        if (!is_sso()) {
            delete[] heap_data;
        }

        size = other.size;
        if (other.is_sso()) {
            std::strcpy(sso_data, other.sso_data);
        } else {
            heap_data = other.heap_data;
            capacity = other.capacity;
            other.heap_data = nullptr;
            other.size = 0;
        }

        return *this;
    }

    ~MyString() {
        if (!is_sso()) {
            delete[] heap_data;
        }
    }

    size_t length() const {
        return size;
    }

    void push(char ch) {
        if (is_sso() && size < SSO_BUFFER_SIZE) {
            sso_data[size++] = ch;
            sso_data[size] = '\0';
        } else {
            if (is_sso()) {
                switch_to_heap(size * 2);
            } else if (size + 1 >= capacity) {
                capacity *= 2;
                char* new_data = new char[capacity + 1];
                std::strcpy(new_data, heap_data);
                delete[] heap_data;
                heap_data = new_data;
            }
            heap_data[size++] = ch;
            heap_data[size] = '\0';
        }
    }

    char& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return is_sso() ? sso_data[index] : heap_data[index];
    }

    const char& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return is_sso() ? sso_data[index] : heap_data[index];
    }

    void print() const {
        std::cout << (is_sso() ? sso_data : heap_data);
    }
};

int main() {
    MyString str1("Hello");
    str1.print();
    std::cout << " (length: " << str1.length() << ")\n";

    str1.push('!');
    str1.print();
    std::cout << " (length: " << str1.length() << ")\n";

    MyString str2("This is a long string that exceeds SSO buffer size.");
    str2.print();
    std::cout << " (length: " << str2.length() << ")\n";

    return 0;
}
