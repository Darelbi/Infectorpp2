/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "InfectorContainer.hpp"

#include <memory>
namespace Infector {
namespace priv {

class Binding;
class DowncastBinding;

class ConcreteContainer: public virtual Container{

    using createBinding     = Binding*(*)();
    using destroyBinding    = void(*)(Binding*);
    using BindingPointer    = std::unique_ptr<Binding,
                                              destroyBinding>;

    using createDowncast    = DowncastBinding*(*)();
    using destroyDowncast   = void(*)(DowncastBinding*);
    using DowncastPointer   = std::unique_ptr<DowncastBinding,
                                              destroyDowncast>;

public:

    /** Used to create Bindings. */
    ConcreteContainer( createBinding bind_factory,
                       destroyBinding bind_destroyer,
                       createDowncast downcast_factory,
                       destroyDowncast downcast_destroyer);

    /** Bind a concrete type to multiple types. */
    virtual void bindAs( TypeInfoP concrete,
                         TypeInfoP * interfaces,
                         DowncastSignature * downcasts,
                         std::size_t size) override;

    /**========================================
                       DETAILS:
    ===========================================*/

    /** allow calling destructor of derived classes from base pointer.*/
    virtual ~ConcreteContainer() = default;

private:

    void bindAsRollback( TypeInfoP * interfaces,
                         std::size_t i);

    BindingPointer              Interfaces;
    DowncastPointer             Downcasts;
};

} // namespace priv
} // namespace Infector
