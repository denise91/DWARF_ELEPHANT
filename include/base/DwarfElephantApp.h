#pragma once

#include "MooseApp.h"

class DwarfElephantApp;

template <>
InputParameters validParams<DwarfElephantApp>();

class DwarfElephantApp : public MooseApp
{
public:
  DwarfElephantApp(InputParameters parameters);

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);
};
