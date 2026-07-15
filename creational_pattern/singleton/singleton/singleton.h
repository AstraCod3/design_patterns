#ifndef SINGLETON_H
#define SINGLETON_H

#include <mutex>
#include <atomic>
#include <memory>

namespace ns_singleton {
	/* unique synchro for different type */
    template<typename T>
    class synchro {
        public:
            synchro() { }
            ~synchro() { }
            std::mutex mtx;
    };

    template<typename T>
    class singleton {
        private:
            singleton() {
                //std::unique_lock<std::mutex> lock(mtx);
                std::cout << "\t Costructor singleton()\n";
            }
            virtual ~singleton() {
                //std::unique_lock<std::mutex> lock(mtx);
                std::cout << "\t Destructor ~singleton()\n";
            }
            //  Deleted copy constructor
            singleton( const singleton &other ) = delete;
            //  Deleted copy assignment
            singleton& operator = ( const singleton&) = delete;
            //  Deleted move constructor
            singleton( singleton &&other ) = delete;
            //  Deleted move assignment
            singleton& operator = ( singleton&& ) = delete;
            static synchro<T> sync;

        public:
            static void unlockInstance () { sync.mtx.unlock(); }
            static void lockInstance () { sync.mtx.lock(); }
            static T& getInstance() {
                static T instance;
                return instance;
            }
    };
    template<typename T> synchro<T> singleton<T>::sync;
} /* namespace n_singleton */
#endif // SINGLETON_H
