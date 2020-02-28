//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "DwarfElephantTestApp.h"
#include "DwarfElephantApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<DwarfElephantTestApp>()
{
  InputParameters params = validParams<DwarfElephantApp>();
  return params;
}

DwarfElephantTestApp::DwarfElephantTestApp(InputParameters parameters) : MooseApp(parameters)
{
  DwarfElephantTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

DwarfElephantTestApp::~DwarfElephantTestApp() {}

void
DwarfElephantTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  DwarfElephantApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"DwarfElephantTestApp"});
    Registry::registerActionsTo(af, {"DwarfElephantTestApp"});
  }
}

void
DwarfElephantTestApp::registerApps()
{
  registerApp(DwarfElephantApp);
  registerApp(DwarfElephantTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
DwarfElephantTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  DwarfElephantTestApp::registerAll(f, af, s);
}
extern "C" void
DwarfElephantTestApp__registerApps()
{
  DwarfElephantTestApp::registerApps();
}
