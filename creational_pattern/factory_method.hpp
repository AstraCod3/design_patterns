/**
 * @file factory_method.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 * @brief Factory method is a creational design pattern
 *  which solves the problem of creating product_base objects
 *  without specifying their concrete classes.
 *
 *   The Factory Method defines a method, 
 *    which should be used for creating objects
 *    instead of using a direct constructor call (new operator).
 *   Subclasses can override this method to change the class of objects that will be created.
 */

/**
 * @namespace ns_factory_method
 * @brief
 */
namespace ns_factory_method {

    /**
     * @class product_base
     * @brief The product_base interface declares the operations that all concrete product_bases must implement.
     */
    class product_base {
        public:

        /**
         * @brief Costructor
         */
        virtual ~product_base() {}

        /**
         * @brief Costructor
         */
        virtual std::string operation() const = 0;
    };

    /**
     * @class creator_base
     * @brief The creator_base class declares the factory method that is supposed to return an
     *         object of a product_base class. The creator_base's subclasses usually provide the
     *         implementation of this method.
     *
     *  Note that the creator_base may also provide some default implementation of the factory method.
     */
    class creator_base {

        public:

        /**
         * @brief
         */
        virtual ~creator_base(){};

        /**
         * @brief
         */
        virtual product_base* factory_method() const = 0;

        /**
         * @brief Also note that, despite its name, the creator_base's primary responsibility is
         *         not creating product_bases. Usually, it contains some core business logic that
         *         relies on product_base objects, returned by the factory method. Subclasses can
         *         indirectly change that business logic by overriding the factory method and
         *         returning a different type of product_base from it.
         */
        std::string some_operation() const {
            // Call the factory method to create a product_base object.
            product_base* product_base = this->factory_method();
            // Now, use the product_base.
            std::string result = "creator_base: The same creator_base's code has just worked with " + product_base->operation();
            delete product_base;
            return result;
        }
    };

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


} // ns_factory_method