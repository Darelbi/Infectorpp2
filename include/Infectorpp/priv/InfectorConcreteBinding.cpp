/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#include "InfectorConcreteBinding.hpp"

#include <exception>


namespace Infector {
namespace priv {

ConcreteBinding::ConcreteBinding():bindings(){

}

void ConcreteBinding::bind( TypeInfoP concrete,
                            TypeInfoP interface){
    if(get(interface)!=nullptr)
        throw std::invalid_argument("Interface already bound.\n");

    bindings.insert( std::pair< std::type_index, TypeInfoP>
                    ( std::type_index(*interface), concrete));
}

void ConcreteBinding::remove( TypeInfoP interface){
    auto it = bindings.find( std::type_index(*interface) );
    if(it!=bindings.end())
        bindings.erase( it);
}

TypeInfoP ConcreteBinding::get( TypeInfoP interface){
    auto it = bindings.find( std::type_index(*interface));
    return it!=bindings.end()? it->second : nullptr;
}

} // namespace priv
} // namespace Infector
