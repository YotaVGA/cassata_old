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

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Image.h"

template <class Type = Image::RGBA, class Counter = long int> class Integrator
{
    protected:
        Type v;
        Counter c;

    public:
        Integrator() : v(), c() {}

        inline void sample(Type val)
        {
            v += val;
            c++;
        }

        inline Type value() const
        {
            return c ? v / c : v;
        }

        inline const Type &total() const
        {
            return v;
        }

        inline Type &total()
        {
            return v;
        }

        inline Counter &counter()
        {
            return c;
        }

        inline const Counter &counter() const
        {
            return c;
        }
};

#endif
