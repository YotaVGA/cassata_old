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

#include "DiffuseMaterial.h"

using namespace Eigen;

double DiffuseMaterial::BSDF(double lambda, const LocalGeometry &local,
        const Angle &in, const Angle &out) const
{
    if (dot(in.cartesian(), local.normal().cartesian()) > 0 ||
            dot(out.cartesian(), local.normal().cartesian()) > 0)
        return 0;

    return bsdfc.value(lambda) * hbsdfc;
}

double DiffuseMaterial::EDF(double lambda, const LocalGeometry &local,
        const Angle &out) const
{
    if (!hedfc || dot(out.cartesian(), local.normal().cartesian()) < 0)
        return 0;

    return edfc.value(lambda) * hedfc;
}

bool DiffuseMaterial::isEmitter() const
{
    return hedfc;
}

void DiffuseMaterial::distribution(Angle outs[], const LocalGeometry &local,
        unsigned int start, unsigned int stop,
        unsigned int jitx, unsigned int jity) const
{
    double wmp = 1.0 / jitx;
    double hmp = 1.0 / jity;

    double rmax = 1.0 / RAND_MAX;

    double rx = rmax * wmp;
    double ry = rmax * hmp;

    unsigned int nstart = start % (jitx * jity);
    unsigned int n = (stop - start) + 1;

    unsigned int cx = nstart % jitx;
    unsigned int cy = nstart / jitx;

    for (unsigned int i = 0; n; cx = 0)
        for (; cx < jitx; cx++, cy = 0)
        {
            double sx = cx * wmp;

            for (; cy < jitx && n; cy++, n--, i++)
            {
                double sy = cy * hmp;

                double d1 = rand() * rx + sx;
                double d2 = rand() * ry + sy;

                outs[i] = Angle(Vector3d(1, acos(sqrt(d2)), 2 * M_PI * d1),
                        true);
            }
        }
}
