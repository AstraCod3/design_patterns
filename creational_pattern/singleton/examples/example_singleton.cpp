/**
 * @file example_singleton.cpp
 * @brief 
 * @details
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 *
 * @note
 * @warning
 * @see 
 * @todo
 * @deprecated
 * @def
 */

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <stdexcept>      // std::logic_error

#include "../singleton/singleton.hpp"

class myclass {
    public:
        myclass() : idata(0) { /*std::cout << " Costructor myclass address idata : "<< std::hex << &idata << std::dec << "\n";*/ }
        virtual ~myclass() { /*std::cout << " Destructor my class\n";*/ }
        void increment() { 
            ++idata; 
        }
        void display_data() { std::cout << " idata : " << idata << "\n"; }
        int getiData() { return idata; }
    private:
        int idata;
        std::mutex mtx_idata;
};

void thread_func();
void thread_func() {
    for( int cnt = 0; cnt < 1000; cnt++) {
        ns_singleton::singleton<myclass>::getInstance()->increment();
    }
}

int main() {
    std::cout << "start singleton ...\n";
    std::vector<std::thread> vth;
    const int NUM_THREADS = 40;
    for( int i = 0; i < NUM_THREADS; i++) {
        std::thread thr_increment( thread_func );
        vth.emplace_back( std::move(thr_increment) );
    }

    std::cout << " num. of threads : " << vth.size() << "\n";
    for(auto & th : vth) {
        if ( th.joinable() )
            th.join();
    }

    ns_singleton::singleton<myclass>::getInstance()->display_data(); 
    std::cout << "... done!\n";
    return EXIT_SUCCESS;
}
