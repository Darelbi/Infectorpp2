/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include <typeinfo>#include <typeindex>

namespace Infector {
namespace priv {

    using TypeInfoP = const std::type_info *;
    using TypeIndex = std::type_index;

    /** Utility function for performing safe cast to derived class when
        Derived class is not known by library. Design of library should
        guaranteed that pointer passed in this function is Base*, while
        should also guarantee that this function is called when the pointer
        will be casted to Derived*. */
    template< typename Base, typename Derived>
    void * downcast( void * p){
        Base * base = static_cast<Base*>(p);
        Derived * derived = static_cast<Derived*>(base);
        return static_cast<void *>(derived);
    }

    /** Nicer to look at than "void*(*)(void*) */
    using DowncastSignature  = void*(*)(void*);

} // namespace priv
} // namespace Infector
