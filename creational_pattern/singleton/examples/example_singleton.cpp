/**
 * @file example_singleton.cpp
 * @brief 
 * @details
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 */

#include <iostream>
#include <vector>
#include <thread>

#include "../singleton/singleton.hpp"

class myclass {
    public:
        myclass() : idata(0) { }
        virtual ~myclass() { }
        void increment() { 
            ++idata; 
        }
        int get_idata() { return idata; }
    private:
        int idata;
        std::mutex mtx_idata;
};

const int NUM_THREADS = 4000;
const int NUM_CALL_INCREMENT = 10000;

void thread_func();
void thread_func() {
    for( int cnt = 0; cnt < NUM_CALL_INCREMENT; cnt++) {
        ns_singleton::singleton<myclass>::get_instance()->increment();
    }
}

int main() {
    std::cout << "start singleton ...\n";
    std::vector<std::thread> vth;
    for( int i = 0; i < NUM_THREADS; i++) {
        std::thread thr_increment( thread_func );
        vth.emplace_back( std::move(thr_increment) );
    }

    std::cout << " num. of threads : " << vth.size() << "\n";
    for(auto & th : vth) {
        if ( th.joinable() )
            th.join();
    }

    int result = ns_singleton::singleton<myclass>::get_instance()->get_idata(); 
    std::cout << " expected : " << ( NUM_THREADS * NUM_CALL_INCREMENT) << "\n";
    std::cout << " result   : " << result << "\n";

    std::cout << "... done!\n";
    return EXIT_SUCCESS;
}
