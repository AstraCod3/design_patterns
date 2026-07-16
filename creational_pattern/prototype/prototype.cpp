#include <iostream>
#include <vector>

// Abstract base class - This is our prototype which contains a "clone" method
class BasePrototype {
	public:
		BasePrototype() : data(0) { };
		BasePrototype(int _p) : data(_p) { };
		virtual			~BasePrototype() { };
        virtual      	BasePrototype* clone() = 0;
		virtual void 	brew() = 0;
        int          	data = 0;
};

// Concrete implementations of the prototype - in practice, these would be "complex" objects that cost a lot to instantiate
class Prototype_First : public BasePrototype {
	public:
		Prototype_First() { /* std::cout << "Prototype_First()\n";*/ };
		Prototype_First(int _p) : BasePrototype(_p) { /*std::cout << "Prototype_First(_p)\n";*/ };
		virtual ~Prototype_First() { };
        BasePrototype* clone() { return new Prototype_First(*this); }
        void           brew()  { std::cout << "Brewing prototype first!\n"; }
};

class Prototype_Second : public BasePrototype {
	public:
		Prototype_Second() { };
		Prototype_Second(int _p) : BasePrototype(_p) { };
		virtual ~Prototype_Second() { };
        BasePrototype* clone() { return new Prototype_Second(*this); }
		void           brew()  { std::cout << "Brewing prototype second!\n"; }
};

class Prototype_Third : public BasePrototype {
	public:
		Prototype_Third() { };
		Prototype_Third(int _p) : BasePrototype(_p) { };
		virtual ~Prototype_Third () { };
		BasePrototype* clone() { return new Prototype_Third(*this) ; }
		void           brew()  { std::cout << "Brewing prototype third!\n"; }
};

// Helper, management class which can abstract the creation of objects via their type.
class PrototypeManager {
	public:
        PrototypeManager() {
            // The management class contains already instantiated objects so that new objects requested are simply cloned!
            /*obj_prototype[] = {
              static_cast<BasePrototype*>(new Prototype_First),
              new Prototype_Second,
              new Prototype_Third
            };*/
            obj_prototype[0] = static_cast<BasePrototype*>(new Prototype_First);
            obj_prototype[1] = static_cast<BasePrototype*>(new Prototype_Second);
            obj_prototype[2] = static_cast<BasePrototype*>(new Prototype_Third);
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
		BasePrototype* createMachine( int machineType ) { return obj_prototype[machineType]->clone(); }
        
        void print_addr() {
            for ( int i = 0; i < 3; i++) {
                if ( obj_prototype[i] )
                    std::cout << "obj_prototype[" << i << "] addr : " << obj_prototype[i] << std::endl;
            }
        }

	private:
		BasePrototype* obj_prototype[3];
};


int main() {
    std::cout << "\n\nstart prototype ... \n\n";
	// Each call to the "createMachine" method clones the right BasePrototype object
    
    PrototypeManager protoManage;
    protoManage.print_addr();
	std::cout << "\n";

    std::vector<BasePrototype*> myMachines(3);
	
    BasePrototype* proto_obj_first = protoManage.createMachine(0);
    BasePrototype* proto_obj_second = protoManage.createMachine(1);
	BasePrototype* proto_obj_third = protoManage.createMachine(2);

	myMachines[0] = proto_obj_first;
	myMachines[1] = proto_obj_second;
	myMachines[2] = proto_obj_third;

    std::cout << "proto_first addr:   " << proto_obj_first << "\n";
    std::cout << "myMachines[0] addr: " << myMachines[0] << "\n";
	std::cout << "\n";
    
    for (int i = 0; i < myMachines.size(); i++)
	    myMachines[i]->brew();
	std::cout << "\n";

    std::cout << "proto_first->data : " << static_cast<Prototype_First*>(proto_obj_first)->data << "\n";  
    static_cast<Prototype_First*>(proto_obj_first)->data = 30;  
    std::cout << "proto_first->data : " << static_cast<Prototype_First*>(proto_obj_first)->data << "\n";
	std::cout << "\n";

    
    // Easily create a copy! 
    BasePrototype* clonedMachine = proto_obj_first->clone();
    std::cout << "clonedMachine addr: " << clonedMachine << "\n";
    std::cout << "clonedMachine->data : " << static_cast<Prototype_First*>(clonedMachine)->data << "\n"; 
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
