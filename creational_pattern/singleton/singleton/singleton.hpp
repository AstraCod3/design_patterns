#ifndef SINGLETON_H
#define SINGLETON_H
//#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>

namespace ns_singleton {

    template<typename T>
    class singleton {
    private:
        singleton() { }
        virtual ~singleton() {  }
        singleton( const singleton &other ) = delete;        //  Deleted copy constructor
        singleton& operator = ( const singleton&) = delete;  //  Deleted copy assignment
        singleton( singleton &&other ) = delete;             //  Deleted move constructor
        singleton& operator = ( singleton&& ) = delete;      //  Deleted move assignment
        //static std::mutex mtx;
        std::mutex mtx;

    public:

        static void lockInstance() { mtx.lock(); }
        static void unlockInstance() { mtx.unlock(); }
        static T& getInstance() {
            std::lock_guard<std::mutex> lock(mtx);
            static T mylocalInstance;
            return mylocalInstance;
        }
    };

    //template<typename T> std::mutex singleton<T>::mtx;

} /* namespace n_singleton */

#endif


//
// 
// from TalkpAI
// 
// #include <iostream> 
// #include <memory> 
// #include <mutex> 
// 
// class Singleton { 
// 	private: 
// 		static std::unique_ptr<Singleton> instance; 
// 		static std::once_flag onceFlag; 
// 		Singleton() { std::cout << "Singleton created\n"; } 
// 	public: 
// 		Singleton(const Singleton&) = delete;
// 		Singleton& operator=(const Singleton&) = delete; 
// 		static Singleton* getInstance() { 
// 			std::call_once(onceFlag, []() { 
// 					instance.reset(new Singleton()); 
// 					}); 
// 			return instance.get(); 
// 		} 
// 		void doSomething() { std::cout << "Doing something!\n"; } 
// };
// std::unique_ptr<Singleton> Singleton::instance; 
// std::once_flag Singleton::onceFlag; 
// 
// int main() { 
// 	Singleton* s1 = Singleton::getInstance(); 
// 	s1->doSomething(); 
// 	return 0; 
// }
// 
// 
