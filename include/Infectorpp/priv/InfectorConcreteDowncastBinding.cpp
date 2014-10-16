/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#include "InfectorConcreteDowncastBinding.hpp"

namespace Infector {
namespace priv {

ConcreteDowncastBinding::ConcreteDowncastBinding():downcasts(){

}

void ConcreteDowncastBinding::bind( DowncastSignature downcaster,
                                    TypeInfoP interface){
    if(get(interface)!=nullptr)
        throw std::invalid_argument("Interface already bound.\n");

    downcasts.insert( std::pair< TypeIndex, DowncastSignature>
                    ( TypeIndex(*interface), downcaster));
}

void ConcreteDowncastBinding::remove( TypeInfoP interface){
    auto it = downcasts.find( TypeIndex(*interface) );
    if(it!=downcasts.end())
        downcasts.erase( it);
}

DowncastSignature ConcreteDowncastBinding::get( TypeInfoP interface){
    auto it = downcasts.find( TypeIndex(*interface));
    return it!=downcasts.end()? it->second : nullptr;
}

} // namespace priv
} // namespace Infector
