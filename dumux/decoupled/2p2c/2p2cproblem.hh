/*****************************************************************************
 *   Copyright (C) 2010 by Benjamin Faigle, Markus Wolff                     *
 *   Institute of Hydraulic Engineering                                      *
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
 * \file
 * \brief Base class for sequential 2p2c compositional problems
 */
#ifndef DUMUX_IMPETPROBLEM_2P2C_HH
#define DUMUX_IMPETPROBLEM_2P2C_HH

#include "boundaryconditions2p2c.hh"
#include <dumux/decoupled/2p/impes/impesproblem2p.hh>
#include <dumux/decoupled/2p2c/variableclass2p2c.hh>
#include <dumux/decoupled/2p2c/2p2cproperties.hh>


namespace Dumux
{
/*!
 * \ingroup IMPEC
 * \ingroup IMPECproblems
 * \brief  Base class for all compositional 2-phase problems which use an impet algorithm
 *
 * Differs from .../2p/impes/impesproblem2p.hh in the includes
 * (usage of the compositional properties and variableclass) and
 * empty functions for the boundary formulation. Because of the latter,
 * only the functions of the currently used formulation has to be specified
 * in the specific problem.
 */
template<class TypeTag>
class IMPETProblem2P2C : public IMPESProblem2P<TypeTag>
{
    typedef IMPESProblem2P<TypeTag> ParentType;
    typedef typename GET_PROP_TYPE(TypeTag, PTAG(Problem)) Implementation;

    typedef typename GET_PROP_TYPE(TypeTag, PTAG(TimeManager)) TimeManager;

    typedef typename GET_PROP_TYPE(TypeTag, PTAG(GridView)) GridView;
    typedef typename GridView::Grid                         Grid;
    typedef typename GET_PROP_TYPE(TypeTag, PTAG(Scalar))   Scalar;

    typedef typename GridView::Traits::template Codim<0>::Entity Element;

    // material properties
    typedef typename GET_PROP_TYPE(TypeTag, PTAG(SpatialParameters))    SpatialParameters;


    enum {
        dim = Grid::dimension,
        dimWorld = Grid::dimensionworld
    };

    typedef Dune::FieldVector<Scalar, dimWorld>      GlobalPosition;

public:
    /*!
     * \brief The constructor
     *
     * \param gridView The grid view
     * \param verbose Output flag for the time manager.
     */
    IMPETProblem2P2C(TimeManager &timeManager, const GridView &gridView)
        : ParentType(timeManager, gridView)
    { }
    /*!
     * \brief The constructor
     *
     * \param gridView The grid view
     * \param spatialParameters SpatialParameters instantiation
     * \param verbose Output flag for the time manager.
     */
    IMPETProblem2P2C(TimeManager &timeManager, const GridView &gridView, SpatialParameters &spatialParameters)
        : ParentType(timeManager, gridView, spatialParameters)
    { }

    /*!
     * \brief The constructor
     *
     * \param gridView The grid view
     * \param verbose Output flag for the time manager.
     */
    IMPETProblem2P2C(const GridView &gridView, bool verbose = true)
    DUNE_DEPRECATED // use IMPETProblem2P2C(TimeManager&, const GridView &)
        : ParentType(gridView, verbose)
    { }
    /*!
     * \brief The constructor
     *
     * \param gridView The grid view
     * \param spatialParameters SpatialParameters instantiation
     * \param verbose Output flag for the time manager.
     */
    IMPETProblem2P2C(const GridView &gridView, SpatialParameters &spatialParameters, bool verbose = true)
    DUNE_DEPRECATED // use IMPETProblem2P2C(TimeManager&, const GridView &)
        : ParentType(gridView, spatialParameters, verbose)
    { }

    virtual ~IMPETProblem2P2C()
    { }
    /*!
     * \name Problem parameters
     */
    // \{
    //! Saturation initial condition (dimensionless)
    /*! The problem is initialized with the following saturation. Both
     * phases are assumed to contain an equilibrium concentration of the
     * correspondingly other component.
     * \param element The element.
     */
    Scalar initSat(const Element& element) const
    {
        return asImp_().initSatAtPos(element.geometry().center());
    }
    //! Saturation initial condition (dimensionless) at given position
    /*! Has to be provided if initSat() is not used in the specific problem.
     *  \param globalPos The global position.
     */
    Scalar initSatAtPos(const GlobalPosition& globalPos) const
    {
        DUNE_THROW(Dune::NotImplemented, "please specify initial saturation in the problem"
                                            " using an initSatAtPos() method!");
        return NAN;
    }

    //! Concentration initial condition (dimensionless)
    /*! The problem is initialized with the following concentration.
     */
    Scalar initConcentration(const Element& element) const
    {
        return asImp_().initConcentrationAtPos(element.geometry().center());
    }
    //! Concentration initial condition (dimensionless)
    /*! Has to be provided if initConcentration() is not used in the specific problem.
     *  \param globalPos The global position.
     */
    Scalar initConcentrationAtPos(const GlobalPosition& globalPos) const
    {
        DUNE_THROW(Dune::NotImplemented, "please specify initial Concentration in the problem"
                                            " using an initConcentrationAtPos() method!");
        return NAN;
    }
    // \}
    /*!
     * \name Deprecated Problem parameters
     */

    //! Saturation initial condition (dimensionless)
    /*! The problem is initialized with the following saturation. Both
     * phases are assumed to contain an equilibrium concentration of the
     * correspondingly other component.
     */
    Scalar initSat(const GlobalPosition& globalPos, const Element& element) const
    DUNE_DEPRECATED // use initSat(const Element& element)
    {
        DUNE_THROW(Dune::NotImplemented, "please specify initial saturation in the problem!");
        return NAN;
    }
    //! Concentration initial condition (dimensionless)
    /*! The problem is initialized with the following concentration.
     */
    Scalar initConcentration(const GlobalPosition& globalPos, const Element& element) const
    DUNE_DEPRECATED // use initConcentration(const Element& element)
    {
        DUNE_THROW(Dune::NotImplemented, "please specify initial Concentration in the problem!");
        return NAN;
    }
    // \}

private:
    //! Returns the implementation of the problem (i.e. static polymorphism)
    Implementation &asImp_()
    { return *static_cast<Implementation *>(this); }

    //! \copydoc Dumux::IMPETProblem::asImp_()
    const Implementation &asImp_() const
    { return *static_cast<const Implementation *>(this); }
};

}

#endif
