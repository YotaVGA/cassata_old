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

#include <cstdlib>
#include "MaterialSum.h"

double MaterialSum::BSDF(double lambda, const LocalGeometry &local,
        const Angle &in, const Angle &out) const
{
    double r = 0;

    for (unsigned int i = 0; i < n; i++)
        r += l[i]->BSDF(lambda, local, in, out);

    return r;
}

double MaterialSum::EDF(double lambda, const LocalGeometry &local,
        const Angle &out) const
{
    double r = 0;

    for (unsigned int i = 0; i < n; i++)
        r += l[i]->EDF(lambda, local, out);

    return r;
}

bool MaterialSum::isEmitter() const
{
    for (unsigned int i = 0; i < n; i++)
        if (r += l[i]->isEmitter())
            return true;

    return false;
}

void MaterialSum::distribution(Angle outs[], const LocalGeometry &local,
        unsigned int start, unsigned int stop,
        unsigned int jitx, unsigned int jity) const
{
    /* In this function the jittering is ininfluent (but not in the
     * sussequently called distribution functions) because all the materials
     * will receive a successive BSDF or EDF query. The gain obtained with
     * the jittering isn't so much (if any), and the jittering code is very
     * complex, so the jittering isn't take into account for now.
     */

    l[rand() % n]->distribution(outs, local, start, stop, jitx, jity);
}
