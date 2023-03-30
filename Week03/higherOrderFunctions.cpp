#include <iostream>
#include <cassert>
#include <cstddef>

template<typename T, typename U>
U* map(const T* arr, std::size_t size, U (*f)(const T&)){
    U* result = new U[size];
    for (std::size_t i = 0; i < size; i++)
    {
        result[i]=f(arr[i]);
    }
    return result;
}

template<typename T>
T multiply(const T& mul){
    return mul*2;
}

template<typename T>
T reduce(const T* arr, const std::size_t size,
         const T& neutralElem, T (*f)(const T&, const T&)) {
    T temp = neutralElem;
    for(std::size_t i = 0; i < size; ++i) {
        temp = f(temp, arr[i]);
    }
    return temp;
}
int sum(const int& a, const int& b) {
    return a + b;
}

template<typename T, typename U>
using Function_t = U (*)(T);

template<typename T, typename U>
Function_t<T, U> maximize(Function_t<T, U> * funcs, std::size_t size,const T& elem) {
    if (size == 0) {
        return nullptr;
    }
    U maxResult = funcs[0](elem);
    Function_t<T, U> maxFunction = funcs[0];
    
    for (std::size_t i = 1; i < size; ++i) {
        U currentResult = funcs[i](elem);
        if(currentResult > maxResult) {
            maxResult = currentResult;
            maxFunction = funcs[i];
        }
    }
    return maxFunction;
}

int main() {
    Function_t<int, int> functions[] = {
        [](int t) -> int {return 2 * t;},
        [](int t) -> int {return t * t;},
        [](int t) -> int {return t + 1;}
    };
    
    Function_t<int, int> f = maximize<int, int>(functions, 3, 5);
    assert(f == functions[1]);
    
    int arr[]={1,2,5,10};
    // int* result = map<int,int>(arr, 4, multiply<int>);
    int result = reduce(arr, 4, 0, sum);
    // std::cout << result << "\n";
    // for (std::size_t i = 0; i < 4; i++)
    // {
    //     std::cout << result[i] << " ";   
    // }
    
}
