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

static double rayFactor(Vector3d &point, LocalGeometry& local)
{
    return 1;
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

                for (unsigned int j = 0; j < wavelenght_samples; j++)
                {
                    double values[4] = {0, 0, 0, 0};
                    double factor = 0;

                    Vector3d point;
                    LocalGeometry local;

                    if (g->intersection(camera_rays[i], point, local))
                    {
                        values[3] = 1;

                        factor = 1;

                        for (unsigned int k = 0; k < 3; k++)
                        {
                            values[k] = c->energy(camera_rays[i],
                                    wavelenght_camera[j], k) /
                                c->probability(camera_rays[i],
                                        wavelenght_camera[j], k) * factor *
                                rayFactor(point, local);
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
