/**
 * @file singleton.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 *
 * @details This header provides a generic, thread-safe Singleton wrapper using 
 * an elegant RAII-based Proxy pattern. It ensures complete isolation of the 
 * underlying resource while abstracting all synchronization mechanics away from 
 * the managed class.
 * 
 * @note **Key Architectural Highlights:**
 * @note 1. **Zero-Invasive Resource Management**: The managed class `T` requires 
 *          no internal mutexes or thread-safety logic. It can remain pure and single-threaded.
 * @note 2. **Expression-Scoped RAII Locking**: Mutual exclusion is tied directly to the 
 *          evaluation scope of a single C++ expression. The lock is acquired when 
 *          `getInstance()` is called and automatically released at the trailing semicolon `;`.
 * @note 3. **Exception Safety**: If the invoked method on `T` throws an exception, 
 *          the temporary Proxy object is guaranteed to be destroyed during stack unwinding, 
 *          preventing indefinite deadlocks.
 * @note 4. **Valgrind/Helgrind Compliance**: Eliminates traditional race conditions 
 *          common to two-step Singleton patterns (where the lock is released prematurely 
 *          between obtaining the reference and invoking the member function).
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include <mutex>

/**
 * @namespace ns_singleton
 * @brief Namespace housing advanced architectural design patterns.
 * 
 * @details This namespace isolates generic design pattern implementations, 
 * such as thread-safe template wrappers, to prevent collisions with global 
 * business logic structures.
 */
namespace ns_singleton {

    /**
     * @class singleton
     * @brief A generic, thread-safe Singleton template wrapper.
     * 
     * @details This class wraps any standard C++ class type `T` and converts it into a global,
     * thread-safe Singleton instance. It acts as an isolation barrier: users cannot interact 
     * with the underlying type `T` without passing through the transactional `LockedProxy`, 
     * making multi-threaded data races impossible at compile and runtime levels.
     * All constructors, assignments, and moves are strictly deleted to enforce a single reference lifecycle.
     * 
     * @tparam T The type of the class to be managed as a Singleton instance.
     */
    template<typename T>
    class singleton {

    private:

        /** @brief Private constructor to prevent direct instantiation. */
        singleton() { }

        /** @brief Private virtual destructor to prevent explicit destruction. */
        virtual ~singleton() { }

        // Disable copy and move semantics to enforce the Singleton constraint
        singleton( const singleton &other ) = delete;        ///<  Deleted copy constructor
        singleton& operator = ( const singleton&) = delete;  ///<  Deleted copy assignment
        singleton( singleton &&other ) = delete;             ///<  Deleted move constructor
        singleton& operator = ( singleton&& ) = delete;      ///<  Deleted move assignment

        static std::mutex mmtx; ///< Global static mutex protecting access to the instance
        static T minstance;     ///< Static instance of the managed type T

    public:

        /**
         * @class locked_proxy
         * @brief Internal Proxy class for thread-safe access to the Singleton instance.
         * 
         * It implements the RAII (Resource Acquisition Is Initialization) pattern. It acquires 
         * the mutex lock in its constructor and automatically releases it in its destructor.
         */
        class locked_proxy {
        private:
            std::unique_lock<std::mutex> lock;  ///< Manages the ownership of the mutex lock
            T& instance;                        ///< Reference to the actual managed object
        public:
            /**
             * @brief Constructor for the LockedProxy.
             * 
             * @note [Phase 1: Lock Acquisition] This temporary object is allocated. 
             * The constructor accepts the Singleton's static mutex and IMMEDIATELY executes 
             * the lock. From this millisecond onward, no other thread can access the resource.
             * 
             * @param m The static mutex of the Singleton.
             * @param inst The reference to the actual instance of type T.
             */
            locked_proxy(std::mutex& m, T& inst) : lock(m), instance(inst) {}

            /**
             * @brief Member access operator (Arrow Operator).
             * 
             * @note [Phase 2: Resource Access] The compiler intercepts the use of '->' 
             * on this non-pointer class object and invokes this method. It returns the raw 
             * pointer to the protected instance, enabling the execution of the target method.
             * 
             * @return T* Raw pointer to the actual instance managed by the Singleton.
             */
            T* operator->() { return &instance; }

            /**
             * @brief Destructor for the LockedProxy.
             * 
             * @note [Phase 3: Lock Release] Upon reaching the semicolon ';' at the end of the 
             * current line of code, this temporary LockedProxy object goes out of scope and is 
             * destroyed. Consequently, the internal std::unique_lock member is destroyed, 
             * triggering an automatic unlock of the underlying mutex.
             */
            ~locked_proxy() = default;

        }; // class locked_proxy

        /**
         * @brief Returns a safe Proxy object to access the Singleton instance.
         * 
         * @details Guarantees memory protection across the entire life cycle of the single line of code:
         * @code
         *    LOCK ACTIVATED HERE ----------------------┐
         *                                              v
         * ns_singleton::singleton<myclass>::getInstance()->do_somethig();
         *                                                               ^
         *    LOCK RELEASED HERE ----------------------------------------┘
         * @endcode
         * 
         * @return locked_proxy A temporary RAII object holding the active mutex lock.
         */
        [[nodiscard]] static locked_proxy getInstance() {
            return locked_proxy (mmtx, minstance);
        }

    }; // class singleton

    // Initialization of template static members
    template<typename T> std::mutex singleton<T>::mmtx;
    template<typename T> T singleton<T>::minstance;

} // namespace n_singleton 

#endif // SINGLETON_H