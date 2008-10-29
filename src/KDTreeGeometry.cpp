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

#include <vector>
#include "KDTreeGeometry.h"

using namespace std;

void KDTreeGeometry::endGeometries()
{
    /* Actually without infinite geometries */
    double cost = g.size();
    if (!lev)
        ng = g.size();
    leaf = true;

    if (lev > 8 + 1.5 * log(ng))
        return;

    Box tb1, tb2;

    double invsurface = 1 / gbox.surface();

    for (unsigned int i = 0; i < 3; i++)
    {
        Box b1 = gbox;
        Box b2 = gbox;

        double a = gbox.start()[i];
        double b = gbox.stop()[i];

        unsigned long int steps = 2 * g.size();

        double inc = (b - a) / steps;

        for (unsigned long int j = 0; j < steps; j++)
        {
            double middle = a + inc * j;
            b1.stop()[i] = middle;
            b2.start()[i] = middle;
            double tcost = 0.1;

            double p1 = b1.surface() * invsurface;
            double p2 = b2.surface() * invsurface;

            double w1 = 0, w2 = 0;

            for (vector<WeightedGeometry>::const_iterator k = g.begin();
                    k != g.end() && tcost < cost; k++)
            {
                if (k->geometry->isInBox(b1))
                    tcost += p1;
                if (k->geometry->isInBox(b2))
                    tcost += p2;
            }

            if (tcost < cost)
            {
                leaf = false;
                tb1 = b1;
                tb2 = b2;
            }
        }
    }

    if (!leaf)
    {
        KDTreeGeometry *g1 = new KDTreeGeometry(lev + 1, ng);
        KDTreeGeometry *g2 = new KDTreeGeometry(lev + 1, ng);

        double w1 = 0, w2 = 0;

        while (g.size())
        {
            bool inserted = false;

            if (g.back().geometry->isInBox(tb1))
            {
                inserted = true;
                w1 += g.back().weight;
                g1->addGeometry(*g.back().geometry, g.back().weight);
            }
            if (g.back().geometry->isInBox(tb2))
            {
                double tw = inserted ? 0 : g.back().weight;
                w2 += tw;
                g2->addGeometry(*g.back().geometry, tw);
            }

            g.pop_back();
        }

        g1->endGeometries();
        g2->endGeometries();

        addGeometry(*g1, w1);
        addGeometry(*g2, w2);
    }
}

bool KDTreeGeometry::isInGeometry(const Eigen::Vector3d &point) const
{
    /* STUB */
    return GeometryCollector::isInGeometry(point);
}

LocalGeometry KDTreeGeometry::local(const Eigen::Vector3d &point) const
{
    /* STUB */
    return GeometryCollector::local(point);
}

bool KDTreeGeometry::isInBox(const Box &box) const
{
    /* STUB */
    return GeometryCollector::isInBox(box);
}

bool KDTreeGeometry::intersection(const Ray &ray, double &distance) const
{
    /* STUB */
    return GeometryCollector::intersection(ray, distance);
}

bool KDTreeGeometry::intersection(const Ray &ray, double &distance,
        LocalGeometry &localGeometry) const
{
    /* STUB */
    return GeometryCollector::intersection(ray, distance, localGeometry);
}

KDTreeGeometry::~KDTreeGeometry()
{
    if (!leaf)
        for (vector<WeightedGeometry>::const_iterator i = g.begin();
                i != g.end(); i++)
            delete i->geometry;
}
