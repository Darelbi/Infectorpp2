/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "../InfectorExport.hpp"

namespace Infector {
namespace priv {

class Container;

Container * INFECTOR_API createContainer();

void INFECTOR_API destroyContainer( Container * c);

} // namespace priv
} // namespace Infector
