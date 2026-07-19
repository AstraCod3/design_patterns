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


#include <iostream>
#include <list>
#include <string>
#include <future>
#include <chrono>

#include "../behavioral_pattern/observer.hpp"

/**
 * @namespace ns_example
 * @brief Domain-specific namespace containing thread-safe implementations.
 */
namespace ns_example {

    /**
     * @brief Global mutex dedicated purely to thread-safe console output operations.
     */
    static std::mutex io_mutex;

    /**
     * @class vehicle
     * @brief Thread-safe concrete implementation of a Subject.
     */
    class vehicle : public ns_observer::subject_base {

        private:

        std::list<ns_observer::observer_base*> list_observer_;
        std::string message_;
        int speed_ = 0;

        /** @brief Mutex protecting access to the internal observers list and vehicle state. */
        mutable std::mutex list_mutex;

        public:

        virtual ~vehicle() {
            std::lock_guard<std::mutex> io_lock(io_mutex);
            std::cout << "[vehicle] Destroyed.\n";
        }

        /**
         * @brief Adds an observer to the list safely under a lock guard.
         */
        void attach(ns_observer::observer_base *observer) override {
            std::lock_guard<std::mutex> lock(list_mutex);
            list_observer_.push_back(observer);
        }

        /**
         * @brief Removes an observer from the list safely under a lock guard.
         */
        void detach(ns_observer::observer_base *observer) override {
            std::lock_guard<std::mutex> lock(list_mutex);
            list_observer_.remove(observer);
        }

        /**
         * @brief Asynchronously broadcasts state updates while ensuring structure thread safety.
         */
        void notify() override {
            std::vector<std::future<void>> async_tasks;
            std::string current_msg;
            std::vector<ns_observer::observer_base*> observers_snapshot;

            // Scope block to minimize lock contention: we quickly copy the pointer list
            {
                std::lock_guard<std::mutex> lock(list_mutex);
                current_msg = this->message_;
                observers_snapshot.assign(list_observer_.begin(), list_observer_.end());
            }
            // The list_mutex is released here, so attach/detach won't block during thread execution

            for (auto observer : observers_snapshot) {
                async_tasks.push_back(std::async(std::launch::async, [observer, current_msg]() {
                    observer->update(current_msg);
                }));
            }
            // Explicitly out of scope: tasks join sequentially here
        }

        void accelerate(int amount) {
            {
                std::lock_guard<std::mutex> lock(list_mutex);
                speed_ += amount;
                message_ = "Vehicle speed changed to " + std::to_string(speed_) + " km/h";
            }

            {
                std::lock_guard<std::mutex> io_lock(io_mutex);
                std::cout << "\n[vehicle] Event triggered!\n";
            }
            notify();
        }
    };

    /**
     * @class dashboard_display
     * @brief Concrete Observer using io_mutex to eliminate stdout data races.
     */
    class dashboard_display : public ns_observer::observer_base {
        public:
        void update(const std::string &message_from_subject) override {
            std::lock_guard<std::mutex> io_lock(io_mutex);
            std::cout << "[dashboard_display UI] Instantly received: " << message_from_subject << "\n";
        }
    };

    /**
     * @class data_logger
     * @brief Concrete Observer utilizing io_mutex for synchronized disk-emulated output.
     */
    class data_logger : public ns_observer::observer_base {
        public:
        void update(const std::string &message_from_subject) override {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::lock_guard<std::mutex> io_lock(io_mutex);
            std::cout << "[data_logger] Safely logged to disk: " << message_from_subject << "\n";
        }
    };

    int run_simulation() ;
    int run_simulation() {
        vehicle car;
        dashboard_display ui;
        data_logger logger;

        car.attach(&ui);
        car.attach(&logger);

        car.accelerate(40);
        car.accelerate(70);

        return 0;
    }

} // namespace ns_example

int main() {
    std::cout << "-----------------------------------------\n";
    std::cout << "Example Observer ...\n";
    return ns_example::run_simulation();
    std::cout << "...done!\n";
}
