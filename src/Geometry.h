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

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Material.h"
#include "Ray.h"

class Geometry
{
    protected:
        const Material *m;

    public:
        Geometry(const Material &material) : m(&material) {}

        const Material &material() const
        {
            return *m;
        }

        virtual double area() const = 0;

        virtual void distribution(Eigen::Vector3d outs[], unsigned int start,
                unsigned int stop, unsigned int jitx,
                unsigned int jity) const = 0;

        inline void distribution(Eigen::Vector3d outs[],
                unsigned int stop) const
        {
            distribution(outs, 0, stop, 1, 1);
        }

        inline void distribution(Eigen::Vector3d outs[], unsigned int jitx,
                unsigned int jity) const
        {
            distribution(outs, 0, jitx * jity, jitx, jity);
        }

        virtual LocalGeometry local(const Eigen::Vector3d &point) const = 0;
        virtual bool isInGeometry(const Eigen::Vector3d &point) const = 0;

        virtual bool intersection(const Ray &ray, double &distance) const = 0;
        virtual bool intersection(const Ray &ray) const;
        virtual bool intersection(const Ray &ray,
                Eigen::Vector3d &point) const;
        virtual bool intersection(const Ray &ray,
                LocalGeometry &localGeometry) const;
        virtual bool intersection(const Ray &ray, double &distance,
                LocalGeometry &localGeometry) const;
        virtual bool intersection(const Ray &ray, Eigen::Vector3d &point,
                LocalGeometry &localGeometry) const;
};

#endif
