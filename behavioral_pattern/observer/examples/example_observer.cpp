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

#include "../observer/observer.hpp"

int Observer::static_number_ = 0;

int main() {
  Subject *subject = new Subject;
  Observer *observer1 = new Observer(*subject);
  Observer *observer2 = new Observer(*subject);
  Observer *observer3 = new Observer(*subject);
  Observer *observer4;
  Observer *observer5;

  subject->CreateMessage("Hello World! :D");
  observer3->RemoveMeFromTheList();

  subject->CreateMessage("The weather is hot today! :p");
  observer4 = new Observer(*subject);

  observer2->RemoveMeFromTheList();
  observer5 = new Observer(*subject);

  subject->CreateMessage("My new car is great! ;)");
  observer5->RemoveMeFromTheList();

  observer4->RemoveMeFromTheList();
  observer1->RemoveMeFromTheList();

  delete observer5;
  delete observer4;
  delete observer3;
  delete observer2;
  delete observer1;
  delete subject;

  return 0;
}
