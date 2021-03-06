// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// vi: set et ts=4 sw=4 sts=4:
/*
  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.

  Consult the COPYING file in the top-level source directory of this
  module for the precise wording of the license and the list of
  copyright holders.
*/
/*!
 * \file
 * \ingroup BlackOilModel
 *
 * \brief Declares the properties required by the black oil model.
 */
#ifndef EWOMS_BLACK_OIL_PROPERTIES_HH
#define EWOMS_BLACK_OIL_PROPERTIES_HH

#include <ewoms/models/common/multiphasebaseproperties.hh>

namespace Ewoms {
namespace Properties {
//! Specifies if the simulation should write output files that are
//! compatible with those produced by the commercial Eclipse simulator
NEW_PROP_TAG(EnableEclipseOutput);
//! The material law for heat conduction
NEW_PROP_TAG(HeatConductionLaw);
//! The parameters of the material law for heat conduction
NEW_PROP_TAG(HeatConductionLawParams);
//! Enable the ECL-blackoil extension for solvents. ("Second gas")
NEW_PROP_TAG(EnableSolvent);
//! Enable the ECL-blackoil extension for polymer.
NEW_PROP_TAG(EnablePolymer);
//! Enable surface volume scaling
NEW_PROP_TAG(BlackoilConserveSurfaceVolume);
}} // namespace Properties, Ewoms

#endif
