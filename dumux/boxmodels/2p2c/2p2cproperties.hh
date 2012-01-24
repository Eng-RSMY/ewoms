// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// vi: set et ts=4 sw=4 sts=4:
/*****************************************************************************
 *   Copyright (C) 2008-2010 by Andreas Lauser                               *
 *   Copyright (C) 2008-2009 by Melanie Darcis                               *
 *   Copyright (C) 2008-2009 by Klaus Mosthaf                                *
 *   Copyright (C) 2008-2009 by Bernd Flemisch                               *
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
 * \ingroup TwoPTwoCModel
 */
/*!
 * \file
 *
 * \brief Defines the properties required for the 2p2c BOX model.
 */
#ifndef DUMUX_2P2C_PROPERTIES_HH
#define DUMUX_2P2C_PROPERTIES_HH

#include <dumux/boxmodels/common/boxproperties.hh>
#include <dumux/boxmodels/vtk/boxvtkmultiphasemodule.hh>
#include <dumux/boxmodels/vtk/boxvtktemperaturemodule.hh>
#include <dumux/boxmodels/vtk/boxvtkcompositionmodule.hh>

namespace Dumux
{

namespace Properties
{
//////////////////////////////////////////////////////////////////
// Type tags
//////////////////////////////////////////////////////////////////

//! The type tag for the isothermal single phase problems
NEW_TYPE_TAG(BoxTwoPTwoC, INHERITS_FROM(BoxModel, VtkMultiPhase, VtkComposition, VtkTemperature));

//////////////////////////////////////////////////////////////////
// Property tags
//////////////////////////////////////////////////////////////////

NEW_PROP_TAG(NumPhases);   //!< Number of fluid phases in the system
NEW_PROP_TAG(NumComponents); //!< Number of fluid components in the system
NEW_PROP_TAG(TwoPTwoCVerbosity); //!< The verbosity of the model (0 -> do not print anything, 2 -> spam stdout a lot)
NEW_PROP_TAG(TwoPTwoCIndices); //!< Enumerations for the 2p2c models
NEW_PROP_TAG(Indices); //!< Enumerations used by the model
NEW_PROP_TAG(Formulation);   //!< The formulation of the model
NEW_PROP_TAG(FluidSystem); //!< Provides the thermodynamic relations

NEW_PROP_TAG(MaterialLaw);   //!< The material law which ought to be used
NEW_PROP_TAG(MaterialLawParams); //!< The parameters of the material law

NEW_PROP_TAG(HeatConductionLaw);   //!< The heat conduction law which ought to be used
NEW_PROP_TAG(HeatConductionLawParams); //!< The parameters of the heat conduction law

NEW_PROP_TAG(EnableGravity); //!< Specifies whether gravity is considered in the problem
NEW_PROP_TAG(EnableSmoothUpwinding); //!< Specifies whether the smooth upwinding method should be used
}
}

#endif
