/**
 * @file example_singleton.cpp
 * @brief 
 * @details
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 *
 * @note
 *
 *  $ valgrind --tool=helgrind --history-level=approx --log-file=out_helgrind_approx.txt -s ./singleton
 *  $ valgrind --tool=drd --log-file=out_drd.txt -s ./singleton
 *  $ valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./singleton
 *
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
//#include "singleton.hpp"

namespace ns_singleton {

    template<typename T>
    class singleton {
    private:
        singleton() {}
        virtual ~singleton() {}
        singleton(const singleton& other) = delete;        //  Deleted copy constructor
        singleton& operator = (const singleton&) = delete;  //  Deleted copy assignment
        singleton(singleton&& other) = delete;             //  Deleted move constructor
        singleton& operator = (singleton&&) = delete;      //  Deleted move assignment
        static std::mutex mtx;
        //std::mutex mtx;

    public:

        static void lockInstance() { mtx.lock(); }
        static void unlockInstance() { mtx.unlock(); }
        static T& getInstance() {
            std::lock_guard<std::mutex> lock(mtx);
            static T mylocalInstance;
            return mylocalInstance;
        }
    };

    template<typename T> std::mutex singleton<T>::mtx;

} /* namespace n_singleton */


class myclass {
    public:
        myclass() : idata(0) { /*std::cout << " Costructor myclass address idata : "<< std::hex << &idata << std::dec << "\n";*/ }
        virtual ~myclass() { /*std::cout << " Destructor my class\n";*/ }
        void increment() { 
            ns_singleton::singleton<myclass>::lockInstance();
            ++idata; 
            ns_singleton::singleton<myclass>::unlockInstance();
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
        //ns_singleton::singleton<myclass>::lockInstance();
        ns_singleton::singleton<myclass>::getInstance().increment();
        // ns_singleton::singleton<myclass>::getInstancePtr()->increment();
        //ns_singleton::singleton<myclass>::unlockInstance();
    }
}

int main() {
    std::cout << "start singleton ...\n";
    std::vector<std::thread> vth;
    const int NUM_THREADS = 444;
    for( int i = 0; i < NUM_THREADS; i++) {
        std::thread thr_increment( thread_func );
        vth.emplace_back( std::move(thr_increment) );
    }

    std::cout << " num. of threads : " << vth.size() << "\n";
    for(auto & th : vth) {
        if ( th.joinable() )
            th.join();
    }

    ns_singleton::singleton<myclass>::getInstance().display_data(); 
    std::cout << "... done!\n";
    return EXIT_SUCCESS;
}
