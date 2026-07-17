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

} // ns_prototype
