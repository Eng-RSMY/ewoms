// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// vi: set et ts=4 sw=4 sts=4:
/*****************************************************************************
 *   Copyright (C) 2008-2010 by Andreas Lauser                               *
 *   Institute for Modelling Hydraulic and Environmental Systems             *
 *   University of Stuttgart, Germany                                        *
 *   email: <givenname>.<name>@iws.uni-stuttgart.de                          *
 *                                                                           *
 *   This program is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *****************************************************************************/
#ifndef DUMUX_NCP_PROPERTY_DEFAULTS_HH
#define DUMUX_NCP_PROPERTY_DEFAULTS_HH

#include "ncpmodel.hh"
#include <dumux/boxmodels/common/boxmultiphaseproblem.hh>
#include "ncplocalresidual.hh"
#include "ncpfluxvariables.hh"
#include "ncpprimaryvariables.hh"
#include "ncpboundaryratevector.hh"
#include "ncpratevector.hh"
#include "ncpvolumevariables.hh"
#include "ncpnewtoncontroller.hh"
#include "ncpindices.hh"
#include "ncpproperties.hh"

#include <dumux/material/constraintsolvers/compositionfromfugacities.hh>
#include <dumux/material/heatconduction/dummyheatconductionlaw.hh>


/*!
 * \ingroup Properties
 * \ingroup BoxProperties
 * \ingroup BoxNcpModel
 * \file
 * \brief  Default properties for the compositional NCP box model.
 */
namespace Dumux
{
namespace Properties
{
//////////////////////////////////////////////////////////////////
// default property values
//////////////////////////////////////////////////////////////////

/*!
 * \brief Set the property for the number of components.
 *
 * We just forward the number from the fluid system.
 */
SET_INT_PROP(BoxNcp, NumComponents, GET_PROP_TYPE(TypeTag, FluidSystem)::numComponents);

/*!
 * \brief Set the property for the number of fluid phases.
 *
 * We just forward the number from the fluid system and use an static
 * assert to make sure it is 2.
 */
SET_INT_PROP(BoxNcp, NumPhases, GET_PROP_TYPE(TypeTag, FluidSystem)::numPhases);

/*!
 * \brief Set the property for the number of equations and primary variables.
 */
SET_INT_PROP(BoxNcp, NumEq,GET_PROP_TYPE(TypeTag, Indices)::NumPrimaryVars);

/*!
 * \brief Set the property for the material parameters by extracting
 *        it from the material law.
 */
SET_TYPE_PROP(BoxNcp, MaterialLawParams, typename GET_PROP_TYPE(TypeTag, MaterialLaw)::Params);

//! extract the type parameter objects for the heat conduction law
//! from the law itself
SET_TYPE_PROP(BoxNcp,
              HeatConductionLaw,
              Dumux::DummyHeatConductionLaw<typename GET_PROP_TYPE(TypeTag, Scalar)>);

//! extract the type parameter objects for the heat conduction law
//! from the law itself
SET_TYPE_PROP(BoxNcp,
              HeatConductionLawParams,
              typename GET_PROP_TYPE(TypeTag, HeatConductionLaw)::Params);

/*!
 * \brief Set the themodynamic constraint solver which calculates the
 *        composition of any phase given all component fugacities.
 */
SET_PROP(BoxNcp, CompositionFromFugacitiesSolver)
{
private:
    typedef typename GET_PROP_TYPE(TypeTag, Scalar) Scalar;
    typedef typename GET_PROP_TYPE(TypeTag, FluidSystem) FluidSystem;

public:
    typedef Dumux::CompositionFromFugacities<Scalar, FluidSystem> type;
};

//! Use the Ncp local jacobian operator for the compositional NCP model
SET_TYPE_PROP(BoxNcp,
              LocalResidual,
              NcpLocalResidual<TypeTag>);

//! Use the Ncp specific newton controller for the compositional NCP model
SET_TYPE_PROP(BoxNcp, NewtonController, NcpNewtonController<TypeTag>);

//! the Model property
SET_TYPE_PROP(BoxNcp, Model, NcpModel<TypeTag>);

//! The type of the base base class for actual problems
SET_TYPE_PROP(BoxNcp, BaseProblem, BoxMultiPhaseProblem<TypeTag>);

//! use an isothermal model by default
SET_BOOL_PROP(BoxNcp, EnableEnergy, false);

//! disable diffusion by default
SET_BOOL_PROP(BoxNcp, EnableDiffusion, false);

//! do not use smooth upwinding by default
SET_BOOL_PROP(BoxNcp, EnableSmoothUpwinding, false);

//! the RateVector property
SET_TYPE_PROP(BoxNcp, RateVector, NcpRateVector<TypeTag>);

//! the BoundaryRateVector property
SET_TYPE_PROP(BoxNcp, BoundaryRateVector, NcpBoundaryRateVector<TypeTag>);

//! the PrimaryVariables property
SET_TYPE_PROP(BoxNcp, PrimaryVariables, NcpPrimaryVariables<TypeTag>);

//! the VolumeVariables property
SET_TYPE_PROP(BoxNcp, VolumeVariables, NcpVolumeVariables<TypeTag>);

//! the FluxVariables property
SET_TYPE_PROP(BoxNcp, FluxVariables, NcpFluxVariables<TypeTag>);

//! truncate the newton update for the first 2 iterations of a time step
SET_INT_PROP(BoxNcp, NewtonChoppedIterations, 2);

//! The indices required by the compositional NCP model
SET_TYPE_PROP(BoxNcp, Indices, NcpIndices<TypeTag, 0>);
}
}

#endif