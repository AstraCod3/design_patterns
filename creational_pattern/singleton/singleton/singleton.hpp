/**
 * @file singleton.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 *
 * @details This header provides a generic, thread-safe Singleton wrapper using 
 * an advanced RAII-based Proxy pattern combined with dynamic Heap allocation via 
 * std::shared_ptr. It ensures complete isolation of the underlying resource while 
 * abstracting all synchronization mechanics away from the managed class.
 * 
 * @note **Key Architectural Highlights:**
 * @note 1. **Zero-Invasive Resource Management**: The managed class `T` requires 
 *          no internal mutexes or thread-safety logic. It can remain pure and single-threaded.
 * @note 2. **Expression-Scoped RAII Locking**: Mutual exclusion is tied directly to the 
 *          evaluation scope of a single C++ expression. The lock is acquired when 
 *          `getInstance()` is called and automatically released at the trailing semicolon `;`.
 * @note 3. **Modern Heap Lifecycle**: Leverages `std::shared_ptr` to achieve automated 
 *          and leak-free memory reclamation from the Heap upon application termination.
 * @note 4. **Double-Checked Locking Optimization**: Maximizes concurrent performance 
 *          by preventing core thread contention once the shared resource has been initialized.
 * 
 * @code
 *    LOCK ACTIVATED HERE -----------------------┐
 *                                               v
 * ns_singleton::singleton<myclass>::get_instance()->do_something();
 *                                                                 ^
 *    LOCK RELEASED HERE ------------------------------------------┘
 * @endcode
 */

#pragma once
#include <mutex>
#include <memory>

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
     * @brief A generic, thread-safe Singleton template wrapper managing dynamic Heap memory.
     * 
     * @details This class wraps any standard C++ class type `T` and converts it into a global,
     * thread-safe Singleton instance. **Unlike standard static local variables that reside in 
     * the static data segment, this implementation explicitly utilizes std::shared_ptr to allocate 
     * the instance inside the Heap.** This prevents heavy objects from bloating the static memory allocation 
     * or risking stack overflow scenarios, while maintaining deterministic RAII-driven memory reclamation.
     * Users interact with type `T` exclusively through a transactional `LockedProxy`.
     * 
     * @tparam T The type of the class to be managed as a Singleton instance.
     */
    template<typename T>
    class singleton {

    private:

        /** @brief Private constructor to prevent direct instantiation. */
        singleton() { }

        /** @brief Private virtual destructor to prevent explicit destruction. */
        virtual ~singleton() {  }

        // Disable copy and move semantics to enforce the Singleton constraint
        singleton( const singleton &other ) = delete;        ///< Deleted copy constructor
        singleton& operator = ( const singleton&) = delete;  ///< Deleted copy assignment
        singleton( singleton &&other ) = delete;             ///< Deleted move constructor
        singleton& operator = ( singleton&& ) = delete;      ///< Deleted move assignment

        static std::mutex mmtx;                           ///< Global static mutex protecting the initialization phase

        /** 
         * @brief Smart pointer managing the instance on the Heap.
         * 
         * @note **Heap Allocation Strategy:** We intentionally use std::shared_ptr to force the 
         * Object lifecycle onto the Heap rather than the Stack or the static BSS data segment. 
         * This ensures memory is only allocated on demand during runtime and safely reclaimed 
         * upon program termination.
         */
        static std::shared_ptr<T> mlocal_instance;

    public:
        /**
         * @class locked_proxy
         * @brief Internal Proxy class for thread-safe access to the Singleton instance.
         * 
         * @details It implements the RAII (Resource Acquisition Is Initialization) pattern. It acquires 
         * the mutex lock in its constructor and automatically releases it in its destructor. It also 
         * stores a local copy of the shared pointer to safeguard the resource lifetime during method execution.
         */
        class locked_proxy {
        private:
            std::unique_lock<std::mutex> mlock; ///< Manages the ownership of the mutex lock
            std::shared_ptr<T> minstance;       ///< Holds a local copy of the smart pointer to keep the underlying object alive

        public:
            /**
             * @brief Constructor for the locked_proxy.
             * 
             * @note [Phase 1: Lock Acquisition] This temporary object is allocated. 
             * The constructor accepts the Singleton's static mutex and IMMEDIATELY executes 
             * the lock. From this millisecond onward, no other thread can access the resource.
             * 
             * @param m The static mutex of the Singleton.
             * @param inst The shared_ptr instance managing the allocated Heap resource.
             */
            locked_proxy(std::mutex& m, std::shared_ptr<T> inst) : mlock(m), minstance(inst) {}
            
            /**
             * @brief Member access operator (Arrow Operator).
             * 
             * @note [Phase 2: Resource Access] The compiler intercepts the use of '->' 
             * on this non-pointer class object and invokes this method. It returns the raw 
             * pointer to the protected instance, enabling the execution of the target method.
             * 
             * @return T* Raw pointer to the actual instance managed by the shared_ptr.
             */
            T* operator->() { return minstance.get(); }

            /**
             * @brief Destructor for the locked_proxy.
             * 
             * @note [Phase 3: Lock Release] Upon reaching the semicolon ';' at the end of the 
             * current line of code, this temporary locked_proxy object goes out of scope and is 
             * destroyed. Consequently, the internal std::unique_lock member is destroyed, 
             * triggering an automatic unlock of the underlying mutex.
             */
            ~locked_proxy() = default;
        };


        /**
         * @brief Returns a safe Proxy object to access the Singleton instance.
         * 
         * @details Implements an optimized Double-Checked Locking Pattern (DCLP). 
         * If the instance does not exist, it triggers a thread-safe allocation directly 
         * on the Heap via std::make_shared.
         * 
         * @return LockedProxy A temporary RAII object holding the active mutex lock.
         */
        /**
         * @brief Returns a safe Proxy object to access the Singleton instance.
         * 
         * @details Implements an optimized Double-Checked Locking Pattern (DCLP) to ensure 
         * high-performance concurrent reads while avoiding thread races during initialization.
         * Guarantees memory protection across the entire life cycle of the single line of code:
         * 
         * @return locked_proxy A temporary RAII object holding the active mutex lock.
         */
        [[nodiscard]] static locked_proxy get_instance() {
            // First Check: Executed outside the lock to prevent thread serialization once initialized
            if (mlocal_instance == nullptr) {
                std::lock_guard<std::mutex> lock(mmtx);
                // Second Check: Executed inside the lock to protect the atomic object allocation phase
                if (mlocal_instance == nullptr) {
                    mlocal_instance = std::make_shared<T>();
                }
            }
            return locked_proxy(mmtx, mlocal_instance);
        }
    };

    // Initialization of template static members
    template<typename T> std::mutex singleton<T>::mmtx;
    template<typename T> std::shared_ptr<T> singleton<T>::mlocal_instance = nullptr;

} // namespace ns_singleton
