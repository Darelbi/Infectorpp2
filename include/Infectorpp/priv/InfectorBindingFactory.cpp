/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/#include "InfectorBindingFactory.hpp"

#include "InfectorConcreteBinding.hpp"


namespace Infector {
namespace priv {

Binding * createBinding(){
    return new ConcreteBinding;
}

void destroyBinding(Binding * b){
    delete b;
}

} // namespace priv
} // namespace Infector
