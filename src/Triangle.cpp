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

#include "Triangle.h"
#include <cstdlib>

using namespace boost::test_tools;
using namespace Eigen;

void Triangle::init()
{
    A = (cross(p[0], p[1]) + cross(p[1], p[2]) +
            cross(p[2], p[0])).norm() / 2;
    n.setCartesian(cross(p[0] - p[2], p[1] - p[2]));
    d = -dot(p[2], n.cartesian());

    double coeffs[4][4] = {
        p[0].x(), p[1].x(), p[2].x(), 0,
        p[0].y(), p[1].y(), p[2].y(), 0,
        p[0].z(), p[1].z(), p[2].z(), 0,
        1,        1,        1,        0
    };
    coefficents.readRows(&coeffs[0][0]);
}

double Triangle::area() const
{
    return A;
}

LocalGeometry Triangle::local(const Vector3d &point) const
{
    Vector3d b = baricentric(point);

    return LocalGeometry(m, n,
            b.x() * uv[0][0] + b.y() * uv[1][0] + b.z() * uv[2][0],
            b.x() * uv[0][1] + b.y() * uv[1][1] + b.z() * uv[2][1]);
}

bool Triangle::isInGeometry(const Vector3d &point) const
{
    if (!inPlane(point))
        return false;

    Vector3d b = baricentric(point);

    return (0 <= b.x() && b.x() <= 1 && 0 <= b.y() && b.y() <= 1 &&
        0 <= b.z() && b.z() <= 1);
}

void Triangle::distribution(Vector3d outs[], unsigned int start,
        unsigned int stop, unsigned int jitx, unsigned int jity) const
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

                double b[2];
                b[0] = sqrt(d1);
                b[1] = d2 * b[0];

                outs[i] = cartesian(Vector3d(1 - b[0], b[0] - b[1], b[1]));
            }
        }
}

bool Triangle::intersection(const Ray &ray, double &distance) const
{
    Vector3d b;

    distance = int_intersection(ray, b);

    return distance >= 0;
}

bool Triangle::intersection(const Ray &ray, double &distance,
        LocalGeometry &localGeometry) const
{
    Vector3d b;

    distance = int_intersection(ray, b);

    if (distance < 0)
        return false;

    localGeometry.setMaterial(*m);
    localGeometry.setNormal(n);
    localGeometry.setU(b.x() * uv[0][0] + b.y() * uv[1][0] +
            b.z() * uv[2][0]);
    localGeometry.setV(b.x() * uv[0][1] + b.y() * uv[1][1] +
            b.z() * uv[2][1]);

    return true;
}
