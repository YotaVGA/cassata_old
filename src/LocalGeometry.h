/* Copyright ® 2008 Fulvio Satta
 *
 * If you want contact me, send an email to Yota_VGA@users.sf.net
 *
 * This file is part of Cassata
 *
 * Cassata is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Cassata is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef LOCAL_GEOMETRY_H
#define LOCAL_GEOMETRY_H

#include "Material.h"

class Material;
class LocalGeometry
{
    protected:
        const Material *m;
        Angle n;
        double m_u, m_v;

    public:
        inline LocalGeometry(const Material *material = NULL) :
            m(material) {}

        inline LocalGeometry(const Material *material, Angle normal,
                double u = 0, double v = 0) : m(material), n(normal), m_u(u),
                m_v(v) {}

        inline const Material &material() const
        {
            return *m;
        }

        inline void setMaterial(const Material &material)
        {
            m = &material;
        }

        inline const Angle &normal() const
        {
            return n;
        }

        inline void setNormal(const Angle &normal)
        {
            n = normal;
        }

        inline double u() const
        {
            return m_u;
        }

        inline void setU(double u)
        {
            m_u = u;
        }

        inline double v() const
        {
            return m_v;
        }

        inline void setV(double v)
        {
            m_v = v;
        }
};

#endif
