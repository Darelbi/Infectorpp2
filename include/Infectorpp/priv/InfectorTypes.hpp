/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include <typeinfo>


namespace Infector {
namespace priv {

    using TypeInfoP = const std::type_info *;

    /** Convert from concrete class to abstract class. */
    template< typename Concrete, typename Interface> //Derived to Base
    void * upcast( void * concrete_ptr){
        Concrete * implem = static_cast<Concrete*>(concrete_ptr);
        Interface * interface = static_cast<Interface*>(implem); //trivial cast
        return static_cast<void *>(interface); //now to void*
    }

    /** Nicer to look at than "returnType(*)(Args)" function pointer */
    using UpcastSignature  = void*(*)(void*);

} // namespace priv
} // namespace Infector
