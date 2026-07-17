/**
 * @file singleton.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 */

#include <iostream>
#include <vector>

#include "../prototype/prototype.hpp"

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
