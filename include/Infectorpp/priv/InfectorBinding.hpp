/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "InfectorTypes.hpp"

namespace Infector {
namespace priv {

class Binding{
public:

    /** Bind a concrete class to its interface. */
    virtual void bind( TypeInfoP concrete, TypeInfoP interface) = 0;

    /** Remove binding of a concrete class to its interface. */
    virtual void remove( TypeInfoP interface) = 0;

    /** Get concrete type of a class through its interface. */
    virtual TypeInfoP get( TypeInfoP interface) = 0;

    /** allow calling destructor of derived classes from base pointer.*/
    virtual ~Binding() = default;
};

} // namespace priv
} // namespace Infector
