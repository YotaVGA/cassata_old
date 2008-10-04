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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <eigen/linearsolver.h>
#include <eigen/projective.h>
#include <boost/test/floating_point_comparison.hpp>
#include "Geometry.h"

class Triangle : public Geometry
{
    protected:
        Eigen::Vector3d p[3];
        double uv[3][2];
        Eigen::Matrix4d coefficents;

        double A, d;
        Angle n;

        void init();

        inline Eigen::Vector3d baricentric(const Eigen::Vector3d &v) const
        {
            Eigen::Vector4d t;

            Eigen::affToProj(v, &t);

            return Eigen::Vector3d(
                    Eigen::LinearSolver4d(coefficents, t).someSolution().
                    array());
        }

        inline Eigen::Vector3d cartesian(const Eigen::Vector3d &v) const
        {
            return p[0] * v.x() + p[1] * v.y() + p[2] * v.z();
        }

        inline double int_intersection(const Ray &ray,
                Eigen::Vector3d &b) const
        {
            double nv = dot(n.cartesian(), ray.angle().cartesian());

            /* Ray and triangle are parallels */
            if (boost::test_tools::check_is_small(nv, 1e-30))
                return -1;

            /* t = -(d + n * o) / (n * v) */
            double t = -(d + dot(n.cartesian(), ray.origin())) / nv;

            /* Out of the ray */
            if (t < ray.t1() || t > ray.t2())
                return -1;

            b = baricentric(ray.origin() + ray.angle().cartesian() * t);

            double bx = b.x();
            double by = b.y();
            double bz = b.z();

            /* Not in triangle */
            if ((bx < 0 || bx > 1) || (by < 0 || by > 1) ||
                    (bz < 0 || bz > 1))
                return -1;

            return t;
        }

    public:
        inline Triangle(const Material &m) : Geometry(m)
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                p[i] = 0;
                uv[i][0] = 0;
                uv[i][1] = 0;
            }

            init();
        }

        inline Triangle(const Material &m, const Eigen::Vector3d points[3]) :
            Geometry(m)
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                p[i] = points[i];
                uv[i][0] = 0;
                uv[i][1] = 0;
            }

            init();
        }

        Triangle(const Material &m, const Eigen::Vector3d points[3],
                const double uvs[3][2]) : Geometry(m)
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                p[i] = points[i];
                uv[i][0] = uvs[i][0];
                uv[i][1] = uvs[i][1];
            }

            init();
        }

        inline const Eigen::Vector3d &point(unsigned int i) const
        {
            return p[i];
        }

        inline double u(unsigned int i) const
        {
            return uv[i][0];
        }

        inline double v(unsigned int i) const
        {
            return uv[i][1];
        }

        virtual double area() const;

        virtual LocalGeometry local(const Eigen::Vector3d &point) const;

        inline bool inPlane(const Eigen::Vector3d &point) const
        {
            return boost::test_tools::check_is_small(dot(n.cartesian(),
                        point) + d, 1e-30);
        }
        
        virtual bool isInGeometry(const Eigen::Vector3d &point) const;

        virtual void distribution(Eigen::Vector3d outs[], unsigned int start,
            unsigned int stop, unsigned int jitx, unsigned int jity) const;

        virtual bool intersection(const Ray &ray, double &distance) const;
        virtual bool intersection(const Ray &ray, double &distance,
                LocalGeometry &localGeometry) const;
};

#endif
