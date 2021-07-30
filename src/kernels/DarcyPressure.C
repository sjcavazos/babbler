#include "DarcyPressure.h"

registerMooseObject("babblerApp", DarcyPressure);
// Every MOOSE object includes a set of custom parameters within a single InputParameters object (shown below)

InputParameters // InputParameters IS AN OBJECT WITHIN THE DARCY PRESSURE APPLICATION
DarcyPressure::validParams() // the parameters are defined within the validParams() method
{
  InputParameters params = ADKernelGrad::validParams(); // declaring params as a variable
  params.addClassDescription("Compute the diffusion term for Darcy pressure ($p$) equation: "
                             "$-\\nabla \\cdot \\frac{\\mathbf{K}}{\\mu} \\nabla p = 0$");
// the .addClassDescription should be the first item appended to params

// add a required parameter. If this is not provided, the input file MOOSE will error
  params.addRequiredParam<Real>("permeability", "The isotropic permeability ($K$) of the medium.");

// add an optional parameter and set its default value
  params.addParam<Real>(
      "viscosity",
      7.98e-04,
      "The dynamic viscosity ($\\mu$) of the fluid, the default value is that of water at 30 "
      "degrees Celcius (7.98e-04 Pa-s).");

  return params;
}
/**
 *  note that DarcyPressure, validParams, and ADKernelGrad are all called from the header file. Thus,
 *  ADKernelGrad::validParams simply calls the objects defined in the #include "DarcyPressure.h"
 *  classname::identifier, where an identifier is just the name of a variable
**/

// THE CONSTRUCTOR DEFINITION
DarcyPressure::DarcyPressure(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    // Get the parameters from the input file
    _permeability(getParam<Real>("permeability")),
    _viscosity(getParam<Real>("viscosity"))


    // Set the coefficients for the pressure kernel
    //_permeability(0.8451e-09),
    //_viscosity(7.98e-04)
{
}

ADRealVectorValue
DarcyPressure::precomputeQpResidual()
{
  return (_permeability / _viscosity) * _grad_u[_qp];
}