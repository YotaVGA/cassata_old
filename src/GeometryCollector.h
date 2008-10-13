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

#ifndef GEOMETRYCOLLECTOR_H
#define GEOMETRYCOLLECTOR_H

#include "BlackMaterial.h"
#include "Geometry.h"
#include <vector>

class GeometryCollector : public Geometry
{
    protected:
        struct WeightedGeometry
        {
            Geometry *geometry;
            double weight;
            double cumulative_weight;
            
            inline bool operator<(const WeightedGeometry &b) const
            {
                return cumulative_weight < b.cumulative_weight;
            }
        };

        std::vector<WeightedGeometry> g;

        double A;
        double w;

    public:
        inline GeometryCollector() : Geometry(BlackMaterial()), A(0) {}

        virtual void addGeometry(Geometry &geometry, double weight = -1);
        virtual void endGeometries();

        virtual bool isInGeometry(const Eigen::Vector3d &point) const;

        virtual LocalGeometry local(const Eigen::Vector3d &point) const;

        virtual bool isInBox(const Box &box) const;

        virtual bool intersection(const Ray &ray, double &distance) const;
        virtual bool intersection(const Ray &ray, double &distance,
                LocalGeometry &localGeometry) const;

        virtual void distribution(Eigen::Vector3d outs[], unsigned int start,
                unsigned int stop, unsigned int jitx,
                unsigned int jity) const;
        virtual void distribution(Eigen::Vector3d outs[],
                LocalGeometry localOuts[], unsigned int start,
                unsigned int stop, unsigned int jitx, unsigned int jity) const;

        virtual double area() const;
};

#endif
