/**
 * @file prototype.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 */

#include <iostream>
#include <vector>

namespace ns_prototype {

    /**
     * @class prototype_base
     * @brief Abstract base class - This is our prototype which contains a "clone" method
     */
    class prototype_base {

        public:

        /**
         * @brief Costructor
         */
        prototype_base() : data(0) { };

        /**
         * @brief Costructor
         */
        prototype_base(int _p) : data(_p) { };

        /**
         * @brief Destructor
         */
        virtual ~prototype_base() { };

        /**
         * @brief
         */
        virtual prototype_base* clone() = 0;

        /**
         * @brief
         */
        virtual void brew() = 0;

        /**
         * @brief
         */
        int data = 0;
    };

    /**
     * @class prototype_first
     * @brief Concrete implementations of the prototype - in practice,
     *  these would be "complex" objects that cost a lot to instantiate
     */
    class prototype_first : public prototype_base {

        public:

        /**
         * @brief
         */
        prototype_first() { } ;

        /**
         * @brief
         */
        prototype_first(int _p) : prototype_base(_p) { } ;

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

class Prototype_Second : public prototype_base {
	public:
		Prototype_Second() { };
		Prototype_Second(int _p) : prototype_base(_p) { };
		virtual ~Prototype_Second() { };
        prototype_base* clone() { return new Prototype_Second(*this); }
		void           brew()  { std::cout << "Brewing prototype second!\n"; }
};

class Prototype_Third : public prototype_base {
	public:
		Prototype_Third() { };
		Prototype_Third(int _p) : prototype_base(_p) { };
		virtual ~Prototype_Third () { };
		prototype_base* clone() { return new Prototype_Third(*this) ; }
		void           brew()  { std::cout << "Brewing prototype third!\n"; }
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
            obj_prototype[0] = static_cast<prototype_base*>(new prototype_first);
            obj_prototype[1] = static_cast<prototype_base*>(new Prototype_Second);
            obj_prototype[2] = static_cast<prototype_base*>(new Prototype_Third);
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
		prototype_base* createMachine( int machineType ) { return obj_prototype[machineType]->clone(); }
        
        void print_addr() {
            for ( int i = 0; i < 3; i++) {
                if ( obj_prototype[i] )
                    std::cout << "obj_prototype[" << i << "] addr : " << obj_prototype[i] << std::endl;
            }
        }

	private:
		prototype_base* obj_prototype[3];
};

} // ns_prototype