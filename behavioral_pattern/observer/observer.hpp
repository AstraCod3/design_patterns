/**
 * @file singleton.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 *
 * Description : 
 * 
 * observer Design Pattern
 * 
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 * 
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the subject is also called the
 * Publisher and the observer is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 *
 */


/**
 * @namespace ns_observer
 * @brief Container for the Observer Design Pattern interfaces and implementations.
 *
 * This namespace isolates the observer and subject abstract contracts to prevent
 * naming collisions with other subsystems in the application architecture.
 */
namespace ns_observer {

    /**
     * @class observer_base
     * @brief Abstract base class representing the Observer interface.
     * 
     * Objects implementing this interface can register with a subject to receive updates.
     */
    class observer_base {

        public:

        /**
         * @brief Virtual destructor.
         */
        virtual ~observer_base() {}

        /**
         * @brief Receive update notifications from the subject.
         * @param message_from_subject The state message sent by the subject.
         */
        virtual void update(const std::string &message_from_subject) = 0;
    };

    /**
     * @class subject_base
     * @brief Abstract base class representing the Subject interface.
     * 
     * Defines the contract for managing subscriptions and notifying observers.
     */
    class subject_base {

        public:

        /**
         * @brief Virtual destructor.
         */
        virtual ~subject_base() {}

        /**
         * @brief Subscribe an observer to the subject.
         * @param observer Pointer to the observer to attach.
         */
        virtual void attach(observer_base *observer) = 0;

        /**
         * @brief Unsubscribe an observer from the subject.
         * @param observer Pointer to the observer to detach.
         */
        virtual void detach(observer_base *observer) = 0;

        /**
         * @brief Broadcast an update event to all registered observers.
         */
        virtual void notify() = 0;
    };

} // ns_observer
