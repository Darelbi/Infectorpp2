/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "InfectorDowncastBinding.hpp"

#include <unordered_map>

namespace Infector {
namespace priv {

class ConcreteDowncastBinding: public virtual DowncastBinding{

    using DowncastMap = std::unordered_map< TypeIndex, DowncastSignature>;

    DowncastMap downcasts;

public:

    /** Bind a a downcast function to its interface. */
    virtual void bind( DowncastSignature downcaster,
                       TypeInfoP interface) override;

    /** Remove binding of given interface. */
    virtual void remove( TypeInfoP interface) override;

    /** Get downcast function for a given interface. */
    virtual DowncastSignature get( TypeInfoP interface) override;


    /**========================================
                       DETAILS:
    ===========================================*/
    ConcreteDowncastBinding();
    virtual ~ConcreteDowncastBinding() = default;
};

} // namespace priv
} // namespace Infector
