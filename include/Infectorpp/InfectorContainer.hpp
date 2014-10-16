/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "InfectorTraits.hpp"

#include "priv/InfectorContainer.hpp"
#include "priv/InfectorContainerFactory.hpp"

#include <memory>

namespace Infector {

class Container{
public:

    /** Declare a type as implementation of multiple interfaces(Contracts).
    *   This type will be injected using a "std::shared_ptr", only 1 istance of
    *   T will be created and shared within this container */
    template <typename Impl, typename... Contracts>
    void bindSingleAs();


    /**========================================
                       DETAILS:
    ===========================================*/

    Container();
    inline ~Container() = default;

private:

    using destroyContainer    = void(*)( priv::Container*);
    using ContainerPointer    = std::unique_ptr< priv::Container,
                                                 destroyContainer>;

    ContainerPointer          container;
};

inline Container::Container()
    :
    container(   priv::createContainer(),
                &priv::destroyContainer ){

}

template< typename T, typename... Contracts>
void Container::bindSingleAs(){

    isMultiBase< T, Contracts...>();

    priv::TypeInfoP         types[ sizeof...( Contracts)]
                        { &typeid( Contracts)... };

    priv::DowncastSignature downcasts[ sizeof...( Contracts)]
                        { &priv::downcast< T, Contracts>... };

    container->bindAs( &typeid(T), types, downcasts, sizeof...( Contracts));
}

} // namespace Infector
