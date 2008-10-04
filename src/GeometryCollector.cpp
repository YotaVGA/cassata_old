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
    /* Internal jittering */
    unsigned int jxp = 1;
    unsigned int jyp = 1;

    /* Geometry jittering */
    unsigned int jx = jitx;
    unsigned int jy = jity;

    /* Generation of values for jittering */
    if (g.size() <= 1)
        jyp = 0;
    else
    {
        for (unsigned int i = 2, t; i * i <= jitx; i++)
            if (!(t = (jitx % i)))
            {
                jx = t;
                jxp = i;
            }

        for (unsigned int i = 2, t; i * i <= jity; i++)
            if (!(t = (jity % i)))
            {
                jy = t;
                jyp = i;
            }
    }

    /* Make the internal jittering value */
    unsigned int jp = jxp + jyp;

    /* Internal jittering step */
    double wstep = w / jp;

    /* Starting and termination values */
    unsigned int n = (stop - start) + 1;
    unsigned int s = start % (jitx * jity);
    unsigned int j = s / (jx * jy);
    unsigned int k = s % (jx * jy);

    /* Internal jittering geometry ids */
    unsigned int ge1, ge2 = 0;

    /* Values used in the jittering geometry ids search */
    double minw;
    double maxw = wstep * j;
    unsigned int size = g.size() - 1;
    unsigned int ge2_max = size;

    /* Find the starting geometry */
    if (j == jp - 1)
        ge2 = ge2_max;
    else
        while(ge2 < ge2_max)
        {
            unsigned int idx = (ge2_max - ge2) / 2;
            double idxw = g.at(idx).cumulative_weight;
            
            if (idxw > maxw)
                ge2_max = idx;
            else
                ge2 = idx;
        }

    /* Geometry sampling */
    for (unsigned int i = 0; n; )
    {
        /* For each internal jittering step */
        for (; j < jp; j++)
        {
            /* Variables used in the geometry search */
            ge1 = ge2;
            minw = maxw;
            maxw = minw * (j + 1);

            /* Find the geometry for this jittering step */
            if (j == jp - 1)
                ge2 = ge2_max;
            else
                while(ge2 < ge2_max)
                {
                    unsigned int idx = (ge2_max - ge2) / 2;
                    double idxw = g.at(idx).cumulative_weight;
                    
                    if (idxw >= maxw)
                        ge2_max = idx;
                    else
                        ge2 = idx;
                }
            ge2++;

            /* Jittering on the specific geometry */
            for (; k < jx * jy && n; k++, n--, i++)
            {
                unsigned int r = rand() % (ge2 - ge1 + 1) + ge1;
                g.at(r).geometry->distribution(&outs[i], k, min(jx * jy, n), jx, jy);
            }
            k = 0;
        }
        j = 0;
        ge2 = 0;
        maxw = 0;
    }
}

double GeometryCollector::area() const
{
    return A;
}
