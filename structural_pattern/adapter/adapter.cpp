/**
 * @file singleton.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 * 
 *  output:
 * 
 *  Client: I can work just fine with the target objects:
 *  target: The default target's behavior.
 * 
 *  Client: The adaptee class has a weird interface. See, I don't understand it:
 *  adaptee: .eetpadA eht fo roivaheb laicepS
 * 
 *  Client: But I can work with it via the adapter:
 *  adapter: (TRANSLATED) Special behavior of the adaptee.
 * 
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @namespace ns_adapter
 */
namespace ns_adapter {

    /**
     * @class target
     * @brief The target defines the domain-specific interface used by the client code.
     */
    class target {

        public:

        /**
         * @brief
         */
        virtual ~target() = default;

        /**
         * @brief
         */
        virtual std::string request() const {
            return "target: The default target's behavior.";
        }
    };

    /**
     * @class adaptee
     * @brief The adaptee contains some useful behavior, but its interface is incompatible
     *          with the existing client code. The adaptee needs some adaptation before the
     *          client code can use it.
     */
    class adaptee {

        public:

        /**
         * @brief
         */
        std::string specific_request() const {
            return ".eetpadA eht fo roivaheb laicepS";
        }
    };

} //namespace ns_adapter

/**
 * @namespace ns_example_adapter
 */
namespace ns_example_adapter {

    /**
     * @class adapter
     * @brief The adapter makes the adaptee's interface compatible with the target's interface using multiple inheritance.
     */
    class adapter : public ns_adapter::target, public ns_adapter::adaptee {

        public:

        /**
         * @brief
         */
        adapter() { }

        /**
         * @brief
         */
        std::string request() const override {
            std::string to_reverse = specific_request();
            std::reverse(to_reverse.begin(), to_reverse.end());
            return "adapter: (TRANSLATED) " + to_reverse;
        }
    };

    /**
     * @brief The client code supports all classes that follow the target interface.
     */
    void client_code( const ns_adapter::target *target ) {
        std::cout << target->request(); 
    }

} // ns_example_adapter 


/**
 * @brief
 */
int main() {
    std::cout << "Client: I can work just fine with the target objects:\n";
    ns_adapter::target *target = new ns_adapter::target;
    ns_example_adapter::client_code( target );
    std::cout << "\n\n";
    ns_adapter::adaptee *adaptee = new ns_adapter::adaptee;
    std::cout << "Client: The adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "adaptee: " << adaptee->Specificrequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the adapter:\n";
    ns_example_adapter::adapter *adapter = new ns_example_adapter::adapter;
    client_code( adapter );
    std::cout << "\n";
    delete target;
    delete adaptee;
    delete adapter;
    return EXIT_SUCCESS;
}