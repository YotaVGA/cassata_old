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

#include <algorithm>
#include "GeometryCollector.h"

using namespace std;
using namespace Eigen;

void GeometryCollector::addGeometry(Geometry &geometry, double weight)
{
    double dwg = weight < 0 ? geometry.area() : weight;
    WeightedGeometry wg = {&geometry, dwg, dwg + w};

    g.push_back(wg);

    A += geometry.area();
    w += dwg;
}

bool GeometryCollector::isInGeometry(const Vector3d &point) const
{
    for (vector<WeightedGeometry>::const_iterator i = g.begin(); i != g.end();
            i++)
        if (i->geometry->isInGeometry(point))
            return true;

    return false;
}

LocalGeometry GeometryCollector::local(const Vector3d &point) const
{
    for (vector<WeightedGeometry>::const_iterator i = g.begin(); i != g.end();
            i++)
        if (i->geometry->isInGeometry(point))
            return i->geometry->local(point);

    return LocalGeometry(m);
}

bool GeometryCollector::intersection(const Ray &ray, double &distance) const
{
    for (vector<WeightedGeometry>::const_iterator i = g.begin(); i != g.end();
            i++)
        if (i->geometry->intersection(ray, distance))
            return true;

    return false;
}

bool GeometryCollector::intersection(const Ray &ray) const
{
    for (vector<WeightedGeometry>::const_iterator i = g.begin(); i != g.end();
            i++)
        if (i->geometry->intersection(ray))
            return true;

    return false;
}

bool GeometryCollector::intersection(const Ray &ray, Vector3d &point) const
{
    for (vector<WeightedGeometry>::const_iterator i = g.begin(); i != g.end();
            i++)
        if (i->geometry->intersection(ray, point))
            return true;

    return false;
}

bool GeometryCollector::intersection(const Ray &ray,
        LocalGeometry &localGeometry) const
{
    for (vector<WeightedGeometry>::const_iterator i = g.begin(); i != g.end();
            i++)
        if (i->geometry->intersection(ray, localGeometry))
            return true;

    return false;
}

bool GeometryCollector::intersection(const Ray &ray, double &distance,
        LocalGeometry &localGeometry) const
{
    for (vector<WeightedGeometry>::const_iterator i = g.begin(); i != g.end();
            i++)
        if (i->geometry->intersection(ray, distance, localGeometry))
            return true;

    return false;
}

bool GeometryCollector::intersection(const Ray &ray, Vector3d &point,
        LocalGeometry &localGeometry) const
{
    for (vector<WeightedGeometry>::const_iterator i = g.begin(); i != g.end();
            i++)
        if (i->geometry->intersection(ray, point, localGeometry))
            return true;

    return false;
}

void GeometryCollector::distribution(Vector3d outs[], unsigned int start,
        unsigned int stop, unsigned int jitx, unsigned int jity) const
{
    /* Jittering temporanely removed, see git commit
     * bf7c48019ea6565e0e57397e8786641b76511dc3 for the last version of this
     * function with an unworking solution
     */

    double K = A / RAND_MAX;

    for (unsigned int jx = 0; jx < jitx; jx++)
        for (unsigned int jy = 0; jy < jity; jy++)
        {
            double r = rand() * K;
            WeightedGeometry w;
            w.cumulative_weight = r;

            vector<WeightedGeometry>::const_iterator i =
                upper_bound(g.begin(), g.end(), w);

            i->geometry->distribution(&outs[jx * jity + jy],
                    jx * jity + jy, jx * jity + jy, jitx, jity);
        }
}

double GeometryCollector::area() const
{
    return A;
}
