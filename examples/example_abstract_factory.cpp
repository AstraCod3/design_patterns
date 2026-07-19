/**
 * @file abstract_factory.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 *
 * @note : Abstract Factory is a creational design pattern,
 *           which solves the problem of creating entire product families without specifying their concrete classes.
 *
 *         Abstract Factory defines an interface for creating all distinct products
 *           but leaves the actual product creation to concrete factory classes. Each factory type corresponds to a certain product variety.
 * 
 *         The client code calls the creation methods of a factory
 *           object instead of creating products directly with a constructor call (new operator).
 *           Since a factory corresponds to a single product variant, all its products will be compatible.
 *
 *         Client code works with factories and products only through their abstract interfaces.
 *           This lets the client code work with any product variants,
 *           created by the factory object. You just create a new concrete factory class and pass it to the client code.
 *
 * The client code works with factories and products only through abstract
 * types: abstract_factory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */

#include <iostream>
#include "../creational_pattern/abstract_factory.hpp"

/**
 * @namespace ns_example_abstract_factory
 */
namespace ns_example_abstract_factory {

    /**
     * @brief
     */
    void client_code( const ns_abstract_factory::abstract_factory &factory ) ;
    void client_code( const ns_abstract_factory::abstract_factory &factory ) {
        const ns_abstract_factory::abstract_product_a *product_a = factory.create_product_a();
        const ns_abstract_factory::abstract_product_b *product_b = factory.create_product_b();
        std::cout << product_a->usefull_function_a() << "\n";
        std::cout << product_b->usefull_function_b() << "\n";
        std::cout << product_b->another_usefull_function_b(*product_a) << "\n";
        delete product_a;
        delete product_b;
    }

} // ns_example_abstract_factory

/**
 * @brief
 */
int main() {
    std::cout << "-----------------------------------------\n";
    std::cout << "Example Abstract Factory ...\n";
    std::cout << "Client: Testing client code with the first factory type:\n";
    ns_abstract_factory::concrete_factory_1 *f1 = new ns_abstract_factory::concrete_factory_1();
    ns_example_abstract_factory::client_code( *f1 );
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ns_abstract_factory::concrete_factory_1 *f2 = new ns_abstract_factory::concrete_factory_1();
    ns_example_abstract_factory::client_code( *f2 );
    delete f2;

    std::cout << "...done!\n";
    return EXIT_SUCCESS;
}
