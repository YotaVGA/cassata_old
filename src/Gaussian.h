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

#ifndef GAUSSIAN_H
#define GAUSSIAN_H
#include <boost/math/special_functions/erf.hpp>

extern double sqrt2;
extern double sqrtpi;
extern double sqrt2pi;

class Gaussian
{
    protected:
        double m, s;
        const double K1, K2, K3;

    public:
        Gaussian(double mean, double dev) : m(mean), s(dev),
                K1(1 / (sqrt2pi * s)), K2(-1 / (2 * s * s)), K3(sqrt2 * s) {}

        inline double get(double r) const
        {
            return K3 * boost::math::erf_inv(2 * r - 1) + m;
        }

        inline double value(double x) const
        {
            return K1 * exp((x - m) * (x - m) * K2);
        }

        inline double height() const
        {
            return K1;
        }
};

#endif
