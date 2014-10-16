/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#include "InfectorConcreteDowncastBinding.hpp"

#include "InfectorDowncastBindingFactory.hpp"

namespace Infector {
namespace priv {

DowncastBinding *  createDowncastBinding(){
    return new ConcreteDowncastBinding;
}

void  destroyDowncastBinding( DowncastBinding * c){
    delete c;
}

} // namespace priv
} // namespace Infector
