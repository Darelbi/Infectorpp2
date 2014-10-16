/*******************************************************************************
   Copyright (C) 2014 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once

namespace Infector {
namespace priv {

class DowncastBinding;

DowncastBinding *  createDowncastBinding();

void  destroyDowncastBinding( DowncastBinding * c);

} // namespace priv
} // namespace Infector
