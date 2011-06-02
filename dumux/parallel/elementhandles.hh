/*****************************************************************************
 *   Copyright (C) 2011 by Andreas Lauser                                    *
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
 * 
 * \brief Provides data handles for parallel communication which 
 *        operate on elements
 */
#ifndef DUMUX_CELL_HANDLES_HH
#define DUMUX_CELL_HANDLES_HH
 
#include <dune/grid/common/datahandleif.hh>

namespace Dumux
{
/*!
 * \brief Data handle for parallel communication which sums up all
 *        values are attached to elements
 */
template <class FieldType, class Container, class ElementMapper>
class ElementHandleAssign
    : public Dune::CommDataHandleIF< ElementHandleAssign<FieldType, Container, ElementMapper>,
                                     FieldType >
{
public:
    ElementHandleAssign(Container &container,
                    const ElementMapper &mapper)
        : mapper_(mapper)
        , container_(container)
    { };

    bool contains(int dim, int codim) const
    {
        // only communicate elements
        return codim == 0;
    }

    bool fixedsize(int dim, int codim) const
    {
        // for each Element we communicate a single field vector which
        // has a fixed size
        return true;
    }

    template<class EntityType>
    size_t size (const EntityType &e) const
    {
        // communicate a field type per entity
        return 1;
    }

    template<class MessageBufferImp, class EntityType>
    void gather(MessageBufferImp &buff, const EntityType &e) const
    {
        int elementIdx = mapper_.map(e);
        buff.write(container_[elementIdx]);
    }

    template<class MessageBufferImp, class EntityType>
    void scatter(MessageBufferImp &buff, const EntityType &e, size_t n)
    {
        int elementIdx = mapper_.map(e);

        FieldType tmp;
        buff.read(tmp);
        container_[elementIdx] = tmp;
    }

private:
    const ElementMapper &mapper_;
    Container &container_;
};

/*!
 * \brief Data handle for parallel communication which sums up all
 *        values are attached to elements
 */
template <class FieldType, class Container, class ElementMapper>
class ElementHandleSum
    : public Dune::CommDataHandleIF< ElementHandleSum<FieldType, Container, ElementMapper>,
                                     FieldType >
{
public:
    ElementHandleSum(Container &container,
                    const ElementMapper &mapper)
        : mapper_(mapper)
        , container_(container)
    { };

    bool contains(int dim, int codim) const
    {
        // only communicate elements
        return codim == 0;
    }

    bool fixedsize(int dim, int codim) const
    {
        // for each Element we communicate a single field vector which
        // has a fixed size
        return true;
    }

    template<class EntityType>
    size_t size (const EntityType &e) const
    { 
        // communicate a field type per entity
        return 1;
    }

    template<class MessageBufferImp, class EntityType>
    void gather(MessageBufferImp &buff, const EntityType &e) const
    {
        int elementIdx = mapper_.map(e);
        buff.write(container_[elementIdx]);
    }

    template<class MessageBufferImp, class EntityType>
    void scatter(MessageBufferImp &buff, const EntityType &e, size_t n)
    {
        int elementIdx = mapper_.map(e);

        FieldType tmp;
        buff.read(tmp);
        container_[elementIdx] += tmp;
    }

private:
    const ElementMapper &mapper_;
    Container &container_;
};

/*!
 * \brief Data handle for parallel communication which takes the
 *        maximum of all values that are attached to elements
 */
template <class FieldType, class Container, class ElementMapper>
class ElementHandleMax
    : public Dune::CommDataHandleIF< ElementHandleMax<FieldType, Container, ElementMapper>,
                                     FieldType >
{
public:
    ElementHandleMax(Container &container,
                    const ElementMapper &mapper)
        : mapper_(mapper)
        , container_(container)
    { };

    bool contains(int dim, int codim) const
    {
        // only communicate elements
        return codim == 0;
    }

    bool fixedsize(int dim, int codim) const
    {
        // for each Element we communicate a single field vector which
        // has a fixed size
        return true;
    }

    template<class EntityType>
    size_t size (const EntityType &e) const
    { 
        // communicate a field type per entity
        return 1;
    }

    template<class MessageBufferImp, class EntityType>
    void gather(MessageBufferImp &buff, const EntityType &e) const
    {
        int elementIdx = mapper_.map(e);
        buff.write(container_[elementIdx]);
    }

    template<class MessageBufferImp, class EntityType>
    void scatter(MessageBufferImp &buff, const EntityType &e, size_t n)
    {
        int elementIdx = mapper_.map(e);

        FieldType tmp;
        buff.read(tmp);
        container_[elementIdx] = std::max(container_[elementIdx], tmp);
    }

private:
    const ElementMapper &mapper_;
    Container &container_;
};


/*!
 * \brief Provides data handle for parallel communication which takes
 *        the minimum of all values that are attached to elements
 */
template <class FieldType, class Container, class ElementMapper>
class ElementHandleMin
    : public Dune::CommDataHandleIF< ElementHandleMin<FieldType, Container, ElementMapper>,
                                     FieldType >
{
public:
    ElementHandleMin(Container &container,
                    const ElementMapper &mapper)
        : mapper_(mapper)
        , container_(container)
    { };

    bool contains(int dim, int codim) const
    {
        // only communicate elements
        return codim == 0;
    }

    bool fixedsize(int dim, int codim) const
    {
        // for each Element we communicate a single field vector which
        // has a fixed size
        return true;
    }

    template<class EntityType>
    size_t size (const EntityType &e) const
    { 
        // communicate a field type per entity
        return 1;
    }

    template<class MessageBufferImp, class EntityType>
    void gather(MessageBufferImp &buff, const EntityType &e) const
    {
        int elementIdx = mapper_.map(e);
        buff.write(container_[elementIdx]);
    }

    template<class MessageBufferImp, class EntityType>
    void scatter(MessageBufferImp &buff, const EntityType &e, size_t n)
    {
        int elementIdx = mapper_.map(e);

        FieldType tmp;
        buff.read(tmp);
        container_[elementIdx] = std::min(container_[elementIdx], tmp);
    }

private:
    const ElementMapper &mapper_;
    Container &container_;
};

}

#endif