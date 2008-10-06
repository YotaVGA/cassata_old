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
#include "BlackMaterial.h"
#include "PointGeometry.h"
#include "DefaultRender.h"
#include "Triangle.h"
#include "GeometryCollector.h"
#include "DiffuseMaterial.h"

using namespace Eigen;

int main(int argc, char *argv[])
{
    MatrixP3d matrix;
    matrix.loadIdentity();
    Camera *camera = new PinholeCamera("ba.exr", 800, 600, matrix, matrix);
    Material *material = new BlackMaterial();
    Geometry *geometry = new PointGeometry(*material, Vector3d(0, 0, 0));
    Material *blueMaterial = new DiffuseMaterial(Gaussian(445, 20), 0.5,
             Gaussian(0, 0), 0);

    double uv1[3][2] = {{0, 0},
                        {0, 1},
                        {1, 1}};
    Vector3d p1[3] = {Vector3d(-0.5, -1, 4.5),
                      Vector3d(-0.5,  0, 3),
                      Vector3d( 0.5,  0, 3)};
    Triangle t1(*blueMaterial, p1, uv1);

    double uv2[3][2] = {{0, 0},
                        {1, 1},
                        {1, 0}};
    Vector3d p2[3] = {Vector3d(-0.5, -1, 4.5),
                      Vector3d( 0.5,  0, 3),
                      Vector3d( 0.5, -1, 4.5)};
    Triangle t2(*blueMaterial, p2, uv2);

    GeometryCollector gc;

    gc.addGeometry(t1);
    gc.addGeometry(t2);

    DefaultRender(*camera, gc, *geometry).rendering();

    delete blueMaterial;
    delete geometry;
    delete material;
    delete camera;

    return 0;
}
