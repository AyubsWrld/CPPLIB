#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include<type_traits>
#include <vector>


template<class T>
struct Mallocator
{
    typedef T value_type;
 
    Mallocator() = default; // explicit default constructor. 
 
    template<class U>
    constexpr Mallocator(const Mallocator <U>&) noexcept {} // constexpr user defined copy constructor
 
    [[nodiscard]] T* allocate(std::size_t n) 
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_array_new_length();
 
        if (auto p = static_cast<T*>(std::malloc(n * sizeof(T))))
        {
            report(p, n);
            return p;
        }
 
        throw std::bad_alloc();
    }
 
    void deallocate(T* p, std::size_t n) noexcept
    {
        report(p, n, 0);
        std::free(p);
    }

private:
    void report(T* p, std::size_t n, bool alloc = true) const
    {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
                  << " bytes at " << std::hex << std::showbase
                  << reinterpret_cast<void*>(p) << std::dec << '\n';
    }

};
 
template<class T, class U>
bool operator==(const Mallocator <T>&, const Mallocator <U>&) { return true; }
 
template<class T, class U>
bool operator!=(const Mallocator <T>&, const Mallocator <U>&) { return false; }

template<typename T>
struct V{ using value_type = T; };

template<typename T, typename U>
bool operator==(const V<T>&, const V<U>&){ return false; }


template <typename T>
void a([[maybe_unused]] int b) requires(!std::is_same_v<T,int(std::is_same<long,float>::*)(double)&&>) {}

template <typename T>
void a([[maybe_unused]] int b) {}

int main()
{
  std::vector<int, Mallocator<int>> V(8) ;

  int(std::is_same<float, float>::*)(double)& V;

  int* p ; 
}

