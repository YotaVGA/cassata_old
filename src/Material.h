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

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Angle.h"
#include "LocalGeometry.h"

class Material
{
    public:
        virtual double BSDF(double lambda, const LocalGeometry &local,
                const Angle &in, const Angle &out) const = 0;

        virtual double EDF(double lambda, const LocalGeometry &local,
                const Angle &out) const;

        virtual bool isEmitter() const;

        virtual void distribution(Angle outs[], const LocalGeometry &local,
                const Angle &in, unsigned int start, unsigned int stop,
                unsigned int jitx, unsigned int jity) const;

        inline void distribution(Angle outs[], const LocalGeometry &local,
                const Angle &in, unsigned int stop) const
        {
            distribution(outs, local, in, 0, stop, 1, 1);
        }

        inline void distribution(Angle outs[], const LocalGeometry &local,
                const Angle &in, unsigned int jitx, unsigned int jity) const
        {
            distribution(outs, local, in, 0, jitx * jity, jitx, jity);
        }

        virtual void distribution(Angle outs[], const LocalGeometry &local,
                unsigned int start, unsigned int stop,
                unsigned int jitx, unsigned int jity) const;

        inline void distribution(Angle outs[], const LocalGeometry &local,
                unsigned int stop) const
        {
            distribution(outs, local, 0, stop, 1, 1);
        }

        inline void distribution(Angle outs[], const LocalGeometry &local,
                unsigned int jitx, unsigned int jity) const
        {
            distribution(outs, local, 0, jitx * jity, jitx, jity);
        }
};

#endif
