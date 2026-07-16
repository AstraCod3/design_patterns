/**
 * @file singleton.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 *
 * Description : 
 * 
 * Observer Design Pattern
 * 
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 * 
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the Subject is also called the
 * Publisher and the Observer is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 *
 */

#include <iostream>
#include <list>
#include <string>

/**
 * @namespace ns_observer
 * @brief
 * @details
 */
namespace ns_observer {

    /**
     * @class IObserver
     * @brief
     * @details
     */
    class IObserver {
        public:
            virtual ~IObserver(){};
            virtual void Update(const std::string &message_from_subject) = 0;
    };

    /**
     * @class ISubject
     * @brief
     * @details
     */
    class ISubject {
        public:
            virtual ~ISubject(){};
            virtual void Attach(IObserver *observer) = 0;
            virtual void Detach(IObserver *observer) = 0;
            virtual void Notify() = 0;
    };
    
    /**
     * @class ISubject
     * @brief
     * @details
     * The Subject owns some important state and notifies observers when the state
     * changes.
     */
    class Subject : public ISubject {
        public:
            virtual ~Subject() {
                std::cout << "Goodbye, I was the Subject.\n";
        }

        /**
         * @brief The subscription management methods.
         */
        void Attach(IObserver *observer) override {
            list_observer_.push_back(observer);
        }

        /**
         * @brief The un-subscription management methods.
         */
        void Detach(IObserver *observer) override {
            list_observer_.remove(observer);
        }

        /**
         * @brief
         */
        void Notify() override {
            std::list<IObserver *>::iterator iterator = list_observer_.begin();
            HowManyObserver();
            while (iterator != list_observer_.end()) {
                // forse è preferibile che ogni operazioni di update
                // deve essere un thread, in modo tale che ogni observer
                // all'interno di update puo' prendere tutto il tempo che desidera
                // altrimenti gli observer successivi ricevono 
                // la notifica in ritardo
                (*iterator)->Update(message_);
                ++iterator;
            }
        }

        /**
         * @brief
         */
        void CreateMessage(std::string message = "Empty") {
            this->message_ = message;
            Notify();
        }

        /**
         * @brief
         */
        void HowManyObserver() {
            std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
        }

        /**
         * Usually, the subscription logic is only a fraction of what a Subject can
         * really do. Subjects commonly hold some important business logic, that
         * triggers a notification method whenever something important is about to
         * happen (or after it).
         */
        void SomeBusinessLogic() {
            this->message_ = "change message message";
            Notify();
            std::cout << "I'm about to do some thing important\n";
        }

        private:

            /**
             * @brief
             */
            std::list<IObserver *> list_observer_;

            /**
             * @brief
             */
            std::string message_;
    };

    class Observer : public IObserver {

        public:

        /**
         * @brief
         */
     //Observer(Subject &subject) : subject_(subject) {
        Observer(ISubject &subject) : subject_(subject) {
            this->subject_.Attach(this);
            std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
            this->number_ = Observer::static_number_;
        }

        /**
         * @brief
         */
      virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
      }

      void Update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        //PrintInfo();
        std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
      }
      void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
      }
    //  void PrintInfo() {
    //    std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
    //  }

     private:
      std::string message_from_subject_;
      //Subject &subject_;
     // meglio il padre ISubject per essere
     // astratti altrimenti si deve spcificare la 
     // classe figlia
      ISubject &subject_;
      static int static_number_;
      int number_;
    };

    } // ns_observer
