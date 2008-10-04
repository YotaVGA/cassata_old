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

#include "Geometry.h"

using namespace Eigen;

bool Geometry::intersection(const Ray &ray) const
{
    double t;
    return intersection(ray, t);
}

bool Geometry::intersection(const Ray &ray, Vector3d &point) const
{
    double distance;
    bool r = intersection(ray, distance);
    point = ray.angle().cartesian() * distance + ray.origin();

    return r;
}

bool Geometry::intersection(const Ray &ray,
                LocalGeometry &localGeometry) const
{
    double distance;

    return intersection(ray, distance, localGeometry);
}

bool Geometry::intersection(const Ray &ray, double &distance,
        LocalGeometry &localGeometry) const
{
    bool r = intersection(ray, distance);
    localGeometry = local(ray.angle().cartesian() * distance +
            ray.origin());
    return r;
}

bool Geometry::intersection(const Ray &ray, Vector3d &point,
        LocalGeometry &localGeometry) const
{
    bool r = intersection(ray, point);
    localGeometry = local(point);
    return r;
}
