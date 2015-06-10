/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once

namespace Infector {
namespace priv {

class Binding;

Binding * createBinding();

void destroyBinding(Binding * b);

} // namespace priv
} // namespace Infector
