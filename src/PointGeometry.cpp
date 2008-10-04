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

#include "PointGeometry.h"
#include <boost/test/floating_point_comparison.hpp>

using namespace std;
using namespace boost::test_tools;
using namespace Eigen;

double PointGeometry::area() const
{
    return 0;
}

void PointGeometry::distribution(Vector3d outs[], unsigned int start,
        unsigned int stop, unsigned int jitx,
        unsigned int jity) const
{
    for (unsigned int i = start; i <= stop; i++)
        outs[i + start] = p;
}

LocalGeometry PointGeometry::local(const Vector3d &point) const
{
    return LocalGeometry(m);
}

bool PointGeometry::isInGeometry(const Vector3d &point) const
{
    return check_is_small((p - point).norm(), 1e-30);
}

bool PointGeometry::intersection(const Ray &ray, double &distance) const
{
    return false;
}
