/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "InfectorBinding.hpp"

#include <unordered_map>
namespace Infector {
namespace priv {

class ConcreteBinding: public virtual Binding {

    using TypeMap = std::unordered_map< TypeIndex, TypeInfoP>;

    TypeMap bindings;

public:

    /** Bind a concrete class to its interface. */
    virtual void bind( TypeInfoP concrete,
                       TypeInfoP interface) override;

    /** Remove binding of a concrete class to its interface. */
    virtual void remove( TypeInfoP interface) override;

    /** Get concrete type of a class through its interface. */
    virtual TypeInfoP get( TypeInfoP interface) override;


    /**========================================
                       DETAILS:
    ===========================================*/
    ConcreteBinding();
    virtual ~ConcreteBinding() = default;
};

} // namespace priv
} // namespace Infector
