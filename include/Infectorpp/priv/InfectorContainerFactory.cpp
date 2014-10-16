/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/#include "InfectorContainerFactory.hpp"

#include "InfectorConcreteContainer.hpp"
#include "InfectorBindingFactory.hpp"
#include "InfectorDowncastBindingFactory.hpp"

namespace Infector {
namespace priv {

Container * createContainer(){
    return new ConcreteContainer( &createBinding, &destroyBinding,
                                  &createDowncastBinding, &destroyDowncastBinding);
}

void destroyContainer( Container * c){
    delete c;
}

} // namespace priv
} // namespace Infector
