/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/#include "InfectorConcreteContainer.hpp"

#include "InfectorBinding.hpp"
#include "InfectorDowncastBinding.hpp"

#include <exception>

namespace Infector {
namespace priv {

ConcreteContainer::ConcreteContainer(
                        createBinding bind_factory,
                        destroyBinding bind_destroyer,
                        createDowncast downcast_factory,
                        destroyDowncast downcast_destroyer )
       : // magic
            Interfaces( bind_factory(), bind_destroyer),
            Downcasts( downcast_factory(), downcast_destroyer) {  }

void ConcreteContainer::bindAs
(               TypeInfoP concrete,
                TypeInfoP * interfaces,
                DowncastSignature * downcasts,
                std::size_t size){

    std::size_t i = 0; //SEPARATE HANDLING FOR INTERFACES AND DOWNCASTS?
                       //NOT NEEDED:
                       //1) If already bound. both are bound
                       //2) If bound fails both are removed
    try{
        for(; i<size; i++){
            Interfaces->bind( concrete,interfaces[i]);
            Downcasts->bind( downcasts[i], interfaces[i]);
        }
    }
    catch (std::exception& ex){
        //binding successfull till (i-1)th element then partial for i-th element
        bindAsRollback(interfaces,i);
        throw ex;
    }
}

void ConcreteContainer::bindAsRollback
(               TypeInfoP * interfaces,
                std::size_t max){

    for(std::size_t i = 0; i<=max; i++){
        Interfaces->remove( interfaces[i]);
        Downcasts->remove( interfaces[i]);
    }
}

} // namespace priv
} // namespace Infector
