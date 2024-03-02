#include <iostream>
#include <memory>

/* ===== Vector ===== */

template <typename T>
class TVector {
    T* data;
    size_t size, capacity;

   public:
    TVector();
    TVector(size_t initSize);
    TVector(const TVector& other);
    TVector(TVector&& other);
    ~TVector();

    bool isEmpty();
    void Resize(size_t newSize);
    void PushBack(const T& newElement);
    void popBack();

    T* Data() const;
    size_t Size() const;
    size_t Capacity() const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

   private:
    static T* Allocate(size_t newCapacity);
    void Reallocate(size_t newCapacity);
    void Destroy(T* object);
};

template <typename T>
size_t TVector<T>::Size() const {
    return size;
}

template <typename T>
size_t TVector<T>::Capacity() const {
    return capacity;
}

template <typename T>
T* TVector<T>::Data() const {
    return data;
}

template <typename T>
T* TVector<T>::Allocate(size_t newCapacity) {
    try {
        return new T[newCapacity];
    } catch (std::bad_alloc) {
        std::cerr << "Memory allocation error\n";
        throw std::bad_alloc();
    }
}

template <typename T>
void TVector<T>::Reallocate(size_t newCapacity) {
    T* temp = Allocate(newCapacity);
    std::copy(data, data + size, temp);
    capacity = newCapacity;
    delete[] data;
    data = temp;
}

template <typename T>
void TVector<T>::Destroy(T* object) {
    object->~T();
}

template <typename T>
TVector<T>::TVector() : size(0), capacity(0), data(nullptr) {}

template <typename T>
TVector<T>::TVector(size_t initSize) : size(initSize), capacity(initSize) {
    data = Allocate(capacity);
}

template <typename T>
TVector<T>::TVector(const TVector& other)
    : size(other.Size()), capacity(other.Capacity()) {
    data = Allocate(capacity);
    std::copy(other.Data(), other.Data() + size, data);
}

template <typename T>
TVector<T>::TVector(TVector&& other)
    : size(other.Size()), capacity(other.Capacity()), data(other.Data()) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
TVector<T>::~TVector() {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}

template <typename T>
bool TVector<T>::isEmpty() {
    return size == 0;
}

template <typename T>
void TVector<T>::Resize(size_t newSize) {
    if (newSize <= capacity) {
        size = newSize;
    } else {
        size_t newCapacity = capacity > size_t(1) ? capacity : size_t(1);
        while (newCapacity < newSize) {
            newCapacity *= 4;
        }
        Reallocate(newCapacity);
        size = newSize;
    }
}

template <typename T>
void TVector<T>::PushBack(const T& newElement) {
    Resize(Size() + 1);
    (*this)[Size() - 1] = newElement;
}

template <typename T>
void TVector<T>::popBack() {
    if (isEmpty()) {
        throw std::out_of_range("Trying to pop_back from an empty vector");
    }
    --size;
}

template <typename T>
T& TVector<T>::operator[](size_t index) {
    if (index >= Size()) {
        throw std::out_of_range("Vector index out if range");
    }
    return data[index];
}

template <typename T>
const T& TVector<T>::operator[](size_t index) const {
    if (index >= Size()) {
        throw std::out_of_range("Vector index out if range");
    }
    return data[index];
}

/* ===== Vector end ===== */

/* ===== main ===== */

struct TPair {
    uint16_t key;
    uint64_t value;
};

// int Sort(TVector<TPair> data) {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(0);

//     const size_t counterSize = UINT16_MAX + 1;
//     TVector<size_t> counter(counterSize);
//     for (size_t i = 0; i < counterSize; ++i) {
//         counter[i] = 0;
//     }

//     // TVector<TPair> data;
//     // TPair pair;
//     // while (std::cin >> pair.key >> pair.value) {
//     //     ++counter[pair.key];
//     //     data.PushBack(pair);
//     // }

//     for (int i = 0; i < data.Size(); ++i) {
//         ++counter[data[i].key];
//     }

//     for (size_t i = 1; i < counter.Size(); ++i) {
//         counter[i] = counter[i - 1] + counter[i];
//     }

//     TVector<TPair> result(data.Size());
//     for (size_t i = data.Size(); i-- > 0; ) {
//         uint16_t key = data[i].key;
//         result[counter[key] - 1] = data[i];
//         --counter[key];
//     }

//     // for (size_t i = 0; i < result.Size(); ++i) {
//     //     std::cout << result[i].key << '\t' << result[i].value << '\n';
//     // }

//     return 0;
// }

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    const size_t counterSize = UINT16_MAX + 1;
    TVector<size_t> counter(counterSize);
    for (size_t i = 0; i < counterSize; ++i) {
        counter[i] = 0;
    }

    TVector<TPair> data;
    TPair pair;
    while (std::cin >> pair.key >> pair.value) {
        ++counter[pair.key];
        data.PushBack(pair);
    }

    for (size_t i = 1; i < counter.Size(); ++i) {
        counter[i] = counter[i - 1] + counter[i];
    }

    TVector<TPair> result(data.Size());
    for (size_t i = data.Size(); i-- > 0;) {
        uint16_t key = data[i].key;
        result[counter[key] - 1] = data[i];
        --counter[key];
    }

    for (size_t i = 0; i < result.Size(); ++i) {
        std::cout << result[i].key << '\t' << result[i].value << '\n';
    }

    return 0;
}

/* ===== main end ===== */
