#include <iostream>
#include <cstring>

class MyString
{
private:
    char* data;
    size_t size;
public:
    MyString() : data(nullptr), size(0) {}

    MyString(const char* str) {
        size = std::strlen(str);
        data = new char[size + 1];
        std::strcpy(data, str);
    }

    MyString(const MyString& other) {
        size = other.size;
        data = new char[size + 1];
        std::strcpy(data, other.data);
    }

    MyString& operator = (const MyString& other) {
        if (this == &other) return *this;

        delete[] data;
        size = other.size;
        data = new char[size + 1];
        std::strcpy(data, other.data);

        return *this;
    }

    MyString(MyString&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    MyString& operator = (MyString&& other) noexcept {
        if (this == &other) return *this;

        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        
        return *this;
    }

    ~MyString() {
        delete[] data;
    }

    size_t length() const {
        return size;
    }

    MyString operator+(const MyString& other) const {
        MyString newStr;
        newStr.size = size + other.size;
        newStr.data = new char[newStr.size + 1];
        std::strcpy(newStr.data, data);
        std::strcat(newStr.data, other.data);

        return newStr;
    }

    char& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range: ");
        return data[index];
    }

    const char& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void print() const {
        if (data) {
            std::cout << data;
        }
    }
};

int main()
{
    MyString str1("Hello, ");
    MyString str2("world!");

    MyString str3 = str1 + str2;
    str3.print();

    std::cout << "\nLength: " << str3.length() << std::endl;

    try {
        std::cout << str3[100] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}
