// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// vi: set et ts=4 sw=4 sts=4:
/*****************************************************************************
 *   Copyright (C) 2009 by Karin Erbertseder                                 *
 *   Copyright (C) 2009 by Andreas Lauser                                    *
 *   Copyright (C) 2008 by Bernd Flemisch                                    *
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
/*!
 * \ingroup Properties
 * \ingroup BoxProperties
 * \ingroup OnePTwoCBoxModel
 * \file
 *
 * \brief Defines the properties required for the single-phase,
 *        two-component BOX model.
 */

#ifndef DUMUX_1P2C_PROPERTIES_HH
#define DUMUX_1P2C_PROPERTIES_HH

#include<dumux/boxmodels/common/boxproperties.hh>
#include <dumux/boxmodels/vtk/boxvtkmultiphasemodule.hh>
#include <dumux/boxmodels/vtk/boxvtktemperaturemodule.hh>
#include <dumux/boxmodels/vtk/boxvtkcompositionmodule.hh>

namespace Dumux
{
// \{
namespace Properties
{

//////////////////////////////////////////////////////////////////
// Type tags
//////////////////////////////////////////////////////////////////

//! The type tag for the isothermal single-phase, two-component problems
NEW_TYPE_TAG(BoxOnePTwoC, INHERITS_FROM(BoxModel, VtkMultiPhase, VtkComposition, VtkTemperature));

//////////////////////////////////////////////////////////////////
// Property tags
//////////////////////////////////////////////////////////////////

NEW_PROP_TAG(NumPhases);   //!< Number of fluid phases in the system
NEW_PROP_TAG(NumComponents);   //!< Number of fluid components in the system
NEW_PROP_TAG(OnePTwoCIndices); //!< Enumerations for the 1p2c models
NEW_PROP_TAG(SpatialParameters); //!< The type of the spatial parameters
NEW_PROP_TAG(HeatConductionLaw); //!< The material law for heat conduction
NEW_PROP_TAG(HeatConductionLawParams); //!< The parameters of the material law for heat conduction
NEW_PROP_TAG(FluidSystem); //!< Type of the multi-component relations
NEW_PROP_TAG(UpwindWeight);   //!< The default value of the upwind weight
NEW_PROP_TAG(EnableGravity); //!< Returns whether gravity is considered in the problem
}
// \}
}

#endif

