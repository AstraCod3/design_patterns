/**
 * @file example_factory_method.cpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 * @brief Factory method is a creational design pattern
 *         which solves the problem of creating product_base objects
 *         without specifying their concrete classes.
 *        The Factory Method defines a method, 
 *           which should be used for creating objects
 *           instead of using a direct constructor call (new operator).
 *          Subclasses can override this method to change the class of objects that will be created.
 */

#include <iostream>

#include "..\creational_pattern\factory_method\factory_method.hpp"

/**
 * @namespace ns_example_factory_method
 * @brief
 */
namespace ns_example_factory_method {

    /**
     * @class concrete_product_base_1
     * Concrete product_bases provide various implementations of the product_base interface.
     */
    class concrete_product_base_1 : public product_base {

        public:

        /**
         * @brief
         */
        std::string operation() const override { return "{Result of the concrete_product_base_1}"; }
    };

    /**
     * @class concrete_product_base_1
     * Concrete product_bases provide various implementations of the product_base interface.
     */
    class concrete_product_base_2 : public product_base {

        public:

        /**
         * @brief Costructor
         */
        std::string operation() const override { return "{Result of the concrete_product_base_2}"; }
    };

    /**
     * @class concrete_creator_base_1
     * Concrete creator_bases override the factory method in order to change the
     * resulting product_base's type.
     *
     * Note that the signature of the method still uses the abstract product_base type,
     * even though the concrete product_base is actually returned from the method. This
     * way the creator_base can stay independent of concrete product_base classes.
     */
    class concrete_creator_base_1 : public creator_base {

        public:

        /**
         * @brief
         */
        product_base* factory_method() const override { return new concrete_product_base_1(); }
    };

    /**
     * @class concrete_creator_base_2
     */
    class concrete_creator_base_2 : public creator_base {

        public:

        /**
         * @brief
         */
        product_base* factory_method() const override { return new concrete_product_base_2(); }
    };

    /**
     * @brief The client code works with an instance of a concrete creator_base, albeit through its base interface.
     *         As long as the client keeps working with the creator_base via
     *         the base interface, you can pass it any creator_base's subclass.
     */
    void client_code(const creator_base& creator_base) {
        // ...
        std::cout << "Client: I'm not aware of the creator_base's class, but it still works.\n"
                << creator_base.Someoperation() << std::endl;
        // ...
    }

}

/**
 * @brief The Application picks a creator_base's type depending on the configuration or environment.
 */
int main() {
    std::cout << "App: Launched with the concrete_creator_base_1.\n";
    ns_factory_method::creator_base* creator_base = new ns_example_factory_method::concrete_creator_base_1();
    ns_example_factory_method::client_code(*creator_base);
	delete creator_base;
	
    std::cout << std::endl;
    std::cout << "App: Launched with the concrete_creator_base_2.\n";
    ns_factory_method::creator_base* creator_base2 = new ns_example_factory_method::concrete_creator_base_2();
    ns_example_factory_method::client_code(*creator_base2);
    delete creator_base2;

    return 0;
}
