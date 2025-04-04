#include <iostream>
#include <stdexcept>
#include <utility>
#include <type_traits>

template <typename T>
class Optional {
public:
    Optional() noexcept : has_value_(false) {}

    Optional(const T& value) {
        new (&storage_) T(value);
        has_value_ = true;
    }

    Optional(T&& value) {
        new (&storage_) T(std::move(value));
        has_value_ = true;
    }

    Optional(const Optional& other) {
        if (other.has_value_) {
            new (&storage_) T(other.get_value());
            has_value_ = true;
        } else {
            has_value_ = false;
        }
    }

    Optional(Optional&& other) noexcept {
        if (other.has_value_) {
            new (&storage_) T(std::move(other.get_value()));
            has_value_ = true;
            other.reset();
        } else {
            has_value_ = false;
        }
    }

    Optional& operator=(const Optional& other) {
        if (this != &other) {
            reset();
            if (other.has_value_) {
                new (&storage_) T(other.get_value());
                has_value_ = true;
            }
        }
        return *this;
    }

    Optional& operator=(Optional&& other) noexcept {
        if (this != &other) {
            reset();
            if (other.has_value_) {
                new (&storage_) T(std::move(other.get_value()));
                has_value_ = true;
                other.reset();
            }
        }
        return *this;
    }

    ~Optional() {
        reset();
    }

    bool has_value() const noexcept {
        return has_value_;
    }

    T& get_value() {
        if (!has_value_) throw std::runtime_error("No value present");
        return *reinterpret_cast<T*>(&storage_);
    }

    const T& get_value() const {
        if (!has_value_) throw std::runtime_error("No value present");
        return *reinterpret_cast<const T*>(&storage_);
    }

    void reset() {
        if (has_value_) {
            get_value().~T();
            has_value_ = false;
        }
    }

    void emplace(T value) {
        reset();
        new (&storage_) T(std::move(value));
        has_value_ = true;
    }

    void swap(Optional& other) noexcept {
        if (this == &other) return;

        if (has_value_ && other.has_value_) {
            std::swap(get_value(), other.get_value());
        } else if (has_value_) {
            other.emplace(std::move(get_value()));
            reset();
        } else if (other.has_value_) {
            emplace(std::move(other.get_value()));
            other.reset();
        }
    }

private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage_;
    bool has_value_;
};

int main() {
    Optional<int> opt1;
    Optional<int> opt2(42);

    std::cout << (opt1.has_value() ? "opt1 has value" : "opt1 does not have value") << std::endl;
    std::cout << (opt2.has_value() ? "opt2 has value: " + std::to_string(opt2.get_value()) : "opt2 does not have value") << std::endl;

    try {
        std::cout << "opt1 value: " << opt1.get_value() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    opt1.emplace(100);
    std::cout << "opt1 after emplace: " << opt1.get_value() << std::endl;

    opt1.swap(opt2);
    std::cout << "After swap:" << std::endl;
    std::cout << "opt1: " << (opt1.has_value() ? std::to_string(opt1.get_value()) : "no value") << std::endl;
    std::cout << "opt2: " << (opt2.has_value() ? std::to_string(opt2.get_value()) : "no value") << std::endl;

    opt1.reset();
    opt2.reset();
    std::cout << "opt1 after reset: " << (opt1.has_value() ? std::to_string(opt1.get_value()) : "no value") << std::endl;
    std::cout << "opt2 after reset: " << (opt2.has_value() ? std::to_string(opt2.get_value()) : "no value") << std::endl;

    return 0;
}
