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

#ifndef ANGLE_H
#define ANGLE_H

#include "eigen/matrix.h"
#include <cmath>

class Angle
{
    protected:
        Eigen::Vector3d s, c;
        bool spher, cart;
        bool norm;

        inline void toSpher()
        {
            double S;
            
            s.x() = c.norm();
            S = sqrt(c.x() * c.x() + c.y() * c.y());
            s.y() = acos(c.z() / s.x());

            if (S)
            {
                s.z() = asin(c.y() / S);
                if (s.x() < 0)
                    s.z() = M_PI - s.z();
            }
            else
                s.z() = 0;

            spher = true;
        }

        inline void toCart()
        {
            c.x() = s.x() * sin(s.y()) * cos(s.z());
            c.y() = s.x() * sin(s.y()) * sin(s.z());
            c.z() = s.x() * cos(s.y());

            cart = true;
        }

    public:
        inline Angle(bool normalize = true) : spher(false), cart(true),
                norm(normalize) {}

        inline Angle(const Eigen::Vector3d &v, bool sp = false,
                bool normalize = true) : spher(sp), cart(!sp), norm(normalize)
        {
            if (sp)
            {
                s = v;
                if (norm)
                    s.x() = 1;
            }
            else
            {
                c = v;
                if (norm)
                    c.normalize();
            }
        }

        inline void setSpherical(const Eigen::Vector3d &v)
        {
            s = v;

            if (norm)
                s.x() = 1;

            spher = true;
            cart = false;
        }

        inline void setCartesian(const Eigen::Vector3d &v)
        {
            c = v;

            if (norm)
                c.normalize();

            spher = false;
            cart = true;
        }

        inline Eigen::Vector3d spherical()
        {
            if (!spher)
                toSpher();

            return s;
        }

        inline Eigen::Vector3d spherical() const
        {
            Angle t;

            if (spher)
                return s;

            t = Angle(c);

            return t.s;
        }

        inline Eigen::Vector3d cartesian()
        {
            if (!cart)
                toCart();

            return c;
        }

        inline Eigen::Vector3d cartesian() const
        {
            Angle t;

            if (cart)
                return c;

            t = Angle(c, true);

            return t.c;
        }

        inline void setNormalized(bool normalize)
        {
            norm = normalize;
        }

        inline bool isNormalized() const
        {
            return norm;
        }
};

#endif
