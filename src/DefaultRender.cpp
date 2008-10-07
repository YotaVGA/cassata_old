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

#include "DefaultRender.h"

using namespace Eigen;

void DefaultRender::direct(unsigned int n, double outs[], double lambdas[],
        Ray &ray, Vector3d &point, LocalGeometry &local)
{
    const unsigned int ray_shadows = 1;

    Vector3d lightPoints[ray_shadows * ray_shadows];
    LocalGeometry lightLocals[ray_shadows * ray_shadows];

    l->distribution(lightPoints, lightLocals, 0, ray_shadows * ray_shadows,
            ray_shadows, ray_shadows);
    double div = 1. / (ray_shadows * ray_shadows);

    for (unsigned int i = 0; i < ray_shadows * ray_shadows; i++)
    {
        Vector3d dirv = lightPoints[i] - point;
        Vector3d idirv = -dirv;
        Angle dir = Angle(dirv);
        Angle idir = Angle(idirv);
        double K = dot(lightLocals[i].normal().cartesian(), idirv) *
            dot(local.normal().cartesian(), dirv) / dirv.norm2() * div;

        for (unsigned int j = 0; j < n; j++)
        {
            outs[j] += local.material().BSDF(lambdas[j], local, ray.angle(),
                    dir) *
                lightLocals[i].material().EDF(lambdas[j], lightLocals[i],
                        idir) * K;
        }
    }
}

void DefaultRender::indirect(unsigned int n, double outs[], double lambdas[],
        Ray &ray, Vector3d &point, LocalGeometry &local)
{
    /* STUB */
}

void DefaultRender::rayFactor(unsigned int n, double outs[], double lambdas[],
        Ray &ray, Vector3d &point, LocalGeometry &local)
{
    direct(n, outs, lambdas, ray, point, local);
    indirect(n, outs, lambdas, ray, point, local);
}

void DefaultRender::rendering()
{
    unsigned int camera_samples = 1 * 1;
    unsigned int camera_jittering[2] = {1, 1};
    unsigned int wavelenght_samples = 1;
    unsigned int wavelenght_jittering = 1;

    for (unsigned int y = 0; y < c->h(); c->writeLine(), y++)
        for (unsigned int x = 0; x < c->w(); c->finalizePixel(x, y), x++)
        {
            Ray camera_rays[camera_samples];
            c->distribution(camera_rays, x, y, 0, camera_samples - 1,
                    camera_jittering[0], camera_jittering[1]);

            for (unsigned int i = 0; i < camera_samples; i++)
            {
                double wavelenght_camera[wavelenght_samples];
                c->wavelenghtDistribution(wavelenght_camera, camera_rays[i],
                        0, wavelenght_samples - 1, wavelenght_jittering);

                double factor[wavelenght_samples];
                double values[4] = {0, 0, 0, 0};

                for (unsigned int j = 0; j < wavelenght_samples; j++)
                {
                    factor[j] = 0;
                }

                Vector3d point;
                LocalGeometry local;

                if (g->intersection(camera_rays[i], point, local))
                {
                    values[3] = 1;

                    rayFactor(wavelenght_samples, factor, wavelenght_camera,
                            camera_rays[i], point, local);
                    for (unsigned int j = 0; j < wavelenght_samples; j++)
                    {
                        factor[j] += local.material().EDF(wavelenght_camera[j],
                            local, Angle(-camera_rays[i].origin()));

                        for (unsigned int k = 0; k < 3; k++)
                        {
                            values[k] = c->energy(camera_rays[i],
                                    wavelenght_camera[j], k) /
                                c->probability(camera_rays[i],
                                        wavelenght_camera[j], k) * factor[j];
                        }

                        c->integrator(x, y).sample(Image::RGBA(values[0],
                                    values[1], values[2], values[3]));
                    }
                }
            }

            c->integrator(x, y).total().a *= double(c->integrator(x, y).counter()) /
                (camera_samples * wavelenght_samples);
        }
}
