/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "InfectorTypes.hpp"

namespace Infector {
namespace priv {

class DowncastBinding{
public:

    /** Bind a a downcast function to its interface. */
    virtual void bind( DowncastSignature downcaster,
                       TypeInfoP interface) = 0;

    /** Remove binding of given interface. */
    virtual void remove( TypeInfoP interface) = 0;

    /** Get downcast function for a given interface. */
    virtual DowncastSignature get( TypeInfoP interface) = 0;

    /** allow calling destructor of derived classes from base pointer.*/
    virtual ~DowncastBinding() = default;
};

} // namespace priv
} // namespace Infector
