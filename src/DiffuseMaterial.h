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

#ifndef DIFFUSE_MATERIAL_H
#define DIFFUSE_MATERIAL_H

#include "Material.h"
#include "Gaussian.h"

class DiffuseMaterial : public Material
{
    protected:
        Gaussian bsdfc, edfc;
        double hbsdfc, hedfc;

    public:
        DiffuseMaterial(Gaussian ro, double e_ro, Gaussian e, double e_e) :
            bsdfc(ro), edfc(e), hbsdfc(e_ro), hedfc(e_e) {}

        virtual double BSDF(double lambda, const LocalGeometry &local,
                const Angle &in, const Angle &out) const = 0;

        virtual double EDF(double lambda, const LocalGeometry &local,
                const Angle &out) const;

        virtual bool isEmitter() const;

        virtual void distribution(Angle outs[], const LocalGeometry &local,
                unsigned int start, unsigned int stop,
                unsigned int jitx, unsigned int jity) const;
};

#endif
