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

#ifndef RAY_H
#define RAY_H

#include "Angle.h"
#include <limits>

class Ray
{
    protected:
        Eigen::Vector3d o;
        Angle a;
        double m_t1, m_t2;

    public:
        inline Ray(double t1 = 0,
                double t2 = std::numeric_limits<double>::infinity()) :
            m_t1(t1), m_t2(t2) {}

        inline Ray(const Eigen::Vector3d &origin, const Angle &angle,
                double t1 = 0,
                double t2 = std::numeric_limits<double>::infinity()) :
            o(origin), a(angle), m_t1(t1), m_t2(t2) {}

        inline Eigen::Vector3d origin() const
        {
            return o;
        }

        inline void setOrigin(const Eigen::Vector3d &origin)
        {
            o = origin;
        }

        inline Angle angle() const
        {
            return a;
        }

        inline void setAngle(const Angle &angle)
        {
            a = angle;
        }

        inline double t1() const
        {
            return m_t1;
        }

        inline void setT1(double t1)
        {
            m_t1 = t1;
        }

        inline double t2() const
        {
            return m_t2;
        }

        inline void setT2(double t2)
        {
            m_t2 = t2;
        }
};

#endif
