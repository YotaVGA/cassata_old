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

#include "PinholeCamera.h"
#include <cstdlib>
#include <cmath>
#include <boost/test/floating_point_comparison.hpp>

using namespace std;
using namespace boost::test_tools;
using namespace Eigen;

void PinholeCamera::distribution(Ray outs[], unsigned int x, unsigned int y,
        unsigned int start, unsigned int stop, unsigned int jitx,
        unsigned int jity) const
{
    double wp = 1.0 / m_w;
    double hp = 1.0 / m_h;

    double wmp = wp / jitx;
    double hmp = hp / jity;

    double px = x * wp - 0.5;
    double py = y * hp - 0.5;

    double rmax = 1.0 / RAND_MAX;

    double rx = rmax * wmp;
    double ry = rmax * hmp;

    unsigned int nstart = start % (jitx * jity);
    unsigned int n = (stop - start) + 1;

    unsigned int cx = nstart % jitx;
    unsigned int cy = nstart / jitx;

    for (unsigned int i = 0; n; x = 0, cx = 0)
        for (; cx < jitx; cx++, y = 0, cy = 0)
        {
            double sx = cx * wmp;

            for (; cy < jitx && n; cy++, n--, i++)
            {
                double sy = cy * hmp;

                double dx = rand() * rx + sx;
                double dy = rand() * ry + sy;
                Vector3d dir = *matrix * Vector3d(px + dx, py + dy, 1) - p;
                outs[i] = Ray(p, Angle(dir));
            }
        }
}

void PinholeCamera::wavelenghtDistribution(double outs[], const Ray &ray,
        unsigned int start, unsigned int stop, unsigned int jit) const
{
    unsigned int nstart = start % jit;
    unsigned int n = stop - start + 1;

    double r = 3.0 / RAND_MAX;
    double js = 1.0 / jit;

    for (unsigned int j = nstart, i = 0; n; j = 0)
        for (; j < jit && n; n--, i++, j++)
        {
            double P = rand() * r;
            const Gaussian *C;

            if (P < 1)
                C = &R;
            else if (P < 2)
                C = &G;
            else
                C = &B;

            outs[i] = C->get((P - floor(P)) * js + js * j);
        }
}

double PinholeCamera::energy(const Ray out, double lambda,
        unsigned int channel)
{
    Gaussian *C;
    switch(channel)
    {
        case 0:
            C = &R;
            break;

        case 1:
            C = &G;
            break;

        case 2:
            C = &B;
            break;

        default:
            ;
    }

    double v1 = C->value(lambda);
    return v1;
}

double PinholeCamera::probability(const Ray out, double lambda,
        unsigned int channel)
{
    double v1 = R.value(lambda);
    double v2 = G.value(lambda);
    double v3 = B.value(lambda);
    return (v1 + v2 + v3) / 3;
}

unsigned int PinholeCamera::pixelX(const Ray &ray) const
{
    double par = dot((ray.origin() - p).normalized(), ray.angle().cartesian());

    /* Se la retta non passa per la camera nessun pixel */
    if (!check_is_small(par, 1e-30))
        return m_w;

    Vector3d pixel = *invmatrix * (p -ray.angle().cartesian());
    pixel *= m_w / pixel.z();

    if (pixel.x() < 0 || pixel.x() >= m_w)
        return m_w;

    return static_cast<unsigned int>(ceil(pixel.x()));
}

unsigned int PinholeCamera::pixelY(const Ray &ray) const
{
    double par = dot((ray.origin() - p).normalized(), ray.angle().cartesian());

    /* Se la retta non passa per la camera nessun pixel */
    if (abs(par) > numeric_limits<double>::epsilon() * abs(par) * 16)
        return m_h;

    Vector3d pixel = *invmatrix * (p -ray.angle().cartesian());
    pixel *= m_h / pixel.z();

    if (pixel.y() < 0 || pixel.y() >= m_h)
        return m_h;

    return static_cast<unsigned int>(ceil(pixel.y()));
}

Geometry &PinholeCamera::geometry()
{
    return g;
}

const Geometry &PinholeCamera::geometry() const
{
    return g;
}
