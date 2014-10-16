/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once#include "InfectorTypes.hpp"

namespace Infector {
namespace priv {

class Container{

public:

    /** Bind a concrete type to multiple types. */
    virtual void bindAs( TypeInfoP concrete,
                         TypeInfoP * interfaces,
                         DowncastSignature * downcasts,
                         std::size_t size) = 0;

    /** allow calling destructor of derived classes from base pointer.*/
    virtual ~Container() = default;
};

} // namespace priv
} // namespace Infector
