/**
 * @file abstract_factory.hpp
 * @author AstraCod3
 * @date July 15, 2026
 * @version 1.0.0
 *
 * @note : Abstract Factory is a creational design pattern,
 *           which solves the problem of creating entire product families without specifying their concrete classes.
 *         Abstract Factory defines an interface for creating all distinct products
 *           but leaves the actual product creation to concrete factory classes. Each factory type corresponds to a certain product variety.
 *         The client code calls the creation methods of a factory
 *           object instead of creating products directly with a constructor call (new operator).
 *           Since a factory corresponds to a single product variant, all its products will be compatible.
 *         Client code works with factories and products only through their abstract interfaces.
 *           This lets the client code work with any product variants,
 *           created by the factory object. You just create a new concrete factory class and pass it to the client code.
 */

#include <iostream>
#include <string>

/**
 * @namespace ns_abstract_factory
 * @brief
 */
namespace ns_abstract_factory {

    /**
     * @class abstract_product_a
     * @brief Each distinct product of a product family should have a base interface.
     *        All variants of the product must implement this interface.
     */
    class abstract_product_a {

        public:

        /**
         * @brief Costruct
         */
        abstract_product_a() { } ;

        /**
         * @brief Destruct
         */
        virtual ~abstract_product_a() { } ;

        /**
         * @brief
         */
        virtual std::string usefull_function_a() const = 0 ;
    };

    /**
     * @class abstract_product_b
     * @brief Here's the the base interface of another product.
     *        All products can interact with each other,
     *          but proper interaction is possible
     *          only between products of the same concrete variant.
     */
    class abstract_product_b {

        public:

        /**
         * @brief Costruct
         */
        abstract_product_b() { } ;

        /**
         * @brief Destruct
         */
        virtual ~abstract_product_b() { } ;

        /**
         * @brief
         */
        virtual std::string usefull_function_b() const = 0 ;

        /**
        * Product B is able to do its own thing...
        * ...but it also can collaborate with the ProductA.
        *
        * The Abstract Factory makes sure that all products it creates are of the
        * same variant and thus, compatible.
        */
        virtual std::string another_usefull_function_b(const abstract_product_a &collaborator) const = 0;
    };

    /**
     * @class abstract_factory
     * @brief The Abstract Factory interface declares a set of methods that return
     *          different abstract products. These products are called a family and are
     *          related by a high-level theme or concept. Products of one family are usually
     *          able to collaborate among themselves. A family of products may have several
     *          variants, but the products of one variant are incompatible with products of
     *          another.
     */
    class abstract_factory {

        public:

        /**
         * @brief
         */
        virtual ~abstract_factory() { }

        /**
         * @brief
         */
        virtual abstract_product_a *create_product_a() const = 0;

        /**
         * @brief
         */
        virtual abstract_product_b *create_product_b() const = 0;
    };

    /**
     * @class concrete_product_a1
     * @brief Concrete Products are created by corresponding Concrete Factories.
     */
    class concrete_product_a1 : public abstract_product_a {

        public:

        /**
         * @brief
         */
        std::string usefull_function_a() const override {
            return "The result of the product A1." ;
        }
    };

    /**
     * @class concrete_product_a2
     * @brief beacuase class father is public:
     */
    class concrete_product_a2 : public abstract_product_a {

        /**
         * @brief
         */
        std::string usefull_function_a() const override {
            return "The result of the product A2." ;
        }
    };

    /**
     * @class concrete_product_b1
     * @brief Concrete Products are created by corresponding Concrete Factories.
     */
    class concrete_product_b1 : public abstract_product_b {

        public:

        /**
         * @brief
         */
        std::string usefull_function_b() const override {
            return std::string( "The result of the product B1." ) ;
        }

        /**
         * @brief The variant, Product B1, is only able to work correctly with the variant,
         *        Product A1.
         *        Nevertheless, it accepts any instance of abstract_product_a as an argument.
         */
        std::string another_usefull_function_b(const abstract_product_a &collaborator) const override {
            const std::string result = collaborator.usefull_function_a() ;
            return std::string( "The result of the B1 collaborating with ( " + result + " )" ) ;
        }
    };

    /**
     * @class concrete_product_b2
     * @brief 
     */
    class concrete_product_b2 : public abstract_product_b {

        public:

        /**
         * @brief
         */
        std::string usefull_function_b() const override {
            return std::string( "The result of the product B2." ) ;
        }

        /**
         * @brief The variant, Product B2, is only able to work correctly with the variant,
         *        Product A2. Nevertheless, it accepts any instance of abstract_product_a as an argument.
         */
        std::string another_usefull_function_b( const abstract_product_a &collaborator ) const override {
            const std::string result = collaborator.usefull_function_a();
            return std::string( "The result of the B2 collaborating with ( " + result + " )" ) ;
        }

    };

    /**
     * @class concrete_factory_1
     * @brief Concrete Factories produce a family of products that belong to a single variant.
     *        The factory guarantees that resulting products are compatible.
     *        Note that signatures of the Concrete Factory's methods return an abstract product,
     *          while inside the method a concrete product is instantiated.
     */
    class concrete_factory_1 : public abstract_factory {

        public:

        /**
         * @brief
         */
        abstract_product_a *create_product_a() const override {
            return new concrete_product_a1();
        }

        /**
         * @brief
         */
        abstract_product_b *create_product_b() const override {
            return new concrete_product_b1();
        }

    };

    /**
     * @class concrete_factory_2
     * @brief Each Concrete Factory has a corresponding product variant.
     */
    class concrete_factory_2 : public abstract_factory {

        public:

        /**
         * @brief
         */
        abstract_product_a *create_product_a() const override {
            return new concrete_product_a2();
        }

        /**
         * @brief
         */
        abstract_product_b *create_product_b() const override {
            return new concrete_product_b2(); 
        }

    };

} // ns_abstract_factory