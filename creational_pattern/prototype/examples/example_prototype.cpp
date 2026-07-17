/**
 * @file singleton.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 */

#include <iostream>
#include <vector>

#include "../prototype/prototype.hpp"

/**
 * @namespace ns_example_prototype
 */
namespace ns_example_prototype {

    /**
     * @class prototype_first
     * @brief Concrete implementations of the prototype - in practice,
     *  these would be "complex" objects that cost a lot to instantiate
     */
    class prototype_first : public ns_prototype::prototype_base {

        public:

        /**
         * @brief
         */
        prototype_first() { } ;

        /**
         * @brief
         */
        prototype_first(int _p) : ns_prototype::prototype_base(_p) { } ;

        /**
         * @brief
         */
        virtual ~prototype_first() { } ;

        /**
         * @brief
         */
        prototype_base* clone() { return new prototype_first(*this); }

        /**
         * @brief
         */
        void brew() { std::cout << "Brewing prototype first!\n"; }
    };

    class Prototype_Second : public ns_prototype::prototype_base {
        public:
            Prototype_Second() { };
            Prototype_Second(int _p) : ns_prototype::prototype_base(_p) { };
            virtual ~Prototype_Second() { };
            prototype_base* clone() { return new Prototype_Second(*this); }
            void brew() { std::cout << "Brewing prototype second!\n"; }
    };

    class Prototype_Third : public ns_prototype::prototype_base {
        public:
            Prototype_Third() { };
            Prototype_Third(int _p) : ns_prototype::prototype_base(_p) { };
            virtual ~Prototype_Third () { };
            prototype_base* clone() { return new Prototype_Third(*this) ; }
            void brew() { std::cout << "Brewing prototype third!\n"; }
    };

    // Helper, management class which can abstract the creation of objects via their type.
    class PrototypeManager {
        public:
        PrototypeManager() {
            // The management class contains already instantiated objects so that new objects requested are simply cloned!
            /*obj_prototype[] = {
            static_cast<prototype_base*>(new prototype_first),
            new Prototype_Second,
            new Prototype_Third
            };*/
            obj_prototype[0] = static_cast<ns_prototype::prototype_base*>(new prototype_first);
            obj_prototype[1] = static_cast<ns_prototype::prototype_base*>(new Prototype_Second);
            obj_prototype[2] = static_cast<ns_prototype::prototype_base*>(new Prototype_Third);
        }

            ~PrototypeManager() {
                for ( int i = 0; i < 3; i++) {
                    if ( obj_prototype[i] ) {
                        delete obj_prototype[i];
                        obj_prototype[i] = nullptr;
                        std::cout << "deleted obj_prototype[" << i << "]\n";
                    }
                }
            }

            // This helper method will ensure that new machines
            // are not created from scratch but are simply cloned instead
            ns_prototype::prototype_base* createMachine( int machineType ) { return obj_prototype[machineType]->clone(); }
            
            void print_addr() {
                for ( int i = 0; i < 3; i++) {
                    if ( obj_prototype[i] )
                        std::cout << "obj_prototype[" << i << "] addr : " << obj_prototype[i] << std::endl;
                }
            }

        private:
            ns_prototype::prototype_base* obj_prototype[3];
    };

} // ns_example_prototype

int main() {
    std::cout << "\n\nstart prototype ... \n\n";
	// Each call to the "createMachine" method clones the right BasePrototype object
    
    ns_example_prototype::PrototypeManager protoManage;
    protoManage.print_addr();
	std::cout << "\n";

    std::vector<ns_prototype::prototype_base*> myMachines(3);
	
    ns_prototype::prototype_base* proto_obj_first = protoManage.createMachine(0);
    ns_prototype::prototype_base* proto_obj_second = protoManage.createMachine(1);
	ns_prototype::prototype_base* proto_obj_third = protoManage.createMachine(2);

	myMachines[0] = proto_obj_first;
	myMachines[1] = proto_obj_second;
	myMachines[2] = proto_obj_third;

    std::cout << "proto_first addr:   " << proto_obj_first << "\n";
    std::cout << "myMachines[0] addr: " << myMachines[0] << "\n";
	std::cout << "\n";
    
    for (int i = 0; i < myMachines.size(); i++)
	    myMachines[i]->brew();
	std::cout << "\n";

    std::cout << "proto_first->data : " << static_cast<ns_example_prototype::prototype_first*>(proto_obj_first)->data << "\n";  
    static_cast<ns_example_prototype::prototype_first*>(proto_obj_first)->data = 30;  
    std::cout << "proto_first->data : " << static_cast<ns_example_prototype::prototype_first*>(proto_obj_first)->data << "\n";
	std::cout << "\n";

    
    // Easily create a copy! 
    ns_prototype::prototype_base* clonedMachine = proto_obj_first->clone();
    std::cout << "clonedMachine addr: " << clonedMachine << "\n";
    std::cout << "clonedMachine->data : " << static_cast<ns_example_prototype::prototype_first*>(clonedMachine)->data << "\n"; 
	std::cout << "\n";
	
    clonedMachine->brew();
	delete clonedMachine;
	std::cout << "\n";


	// Clean up!
	for (int i = 0; i < myMachines.size(); i++)
		delete myMachines[i];
    
    // delete static 
    std::cout << "... done!\n";
    return 0;
}
