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

#include <cstdlib>
#include <ctime>
#include "PinholeCamera.h"
#include "BlackMaterial.h"
#include "PointGeometry.h"
#include "DefaultRender.h"
#include "Triangle.h"
#include "GeometryCollector.h"
#include "DiffuseMaterial.h"
#include "MaterialSum.h"

using namespace Eigen;

int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));

    MatrixP3d matrix;
    matrix.loadIdentity();
    Camera *camera = new PinholeCamera("ba.exr", 800, 600, matrix, matrix);
    Material *material = new BlackMaterial();
    Geometry *geometry = new PointGeometry(*material, Vector3d(0, 0, 0));
    Material *blueMaterial = new DiffuseMaterial(Gaussian(445, 20), 1,
             Gaussian(0, 0), 0);
    Material *greenMaterial = new DiffuseMaterial(Gaussian(535, 20), 1,
             Gaussian(0, 0), 0);
    Material *redEmission = new DiffuseMaterial(Gaussian(0, 0), 0,
            Gaussian(575, 85), 1);
    Material *greenEmission = new DiffuseMaterial(Gaussian(0, 0), 0,
            Gaussian(535, 100), 1);
    Material *blueEmission = new DiffuseMaterial(Gaussian(0, 0), 0,
            Gaussian(445, 50), 1);
    Material *emissionMaterials[] = {redEmission, greenEmission,
        blueEmission};
    Material *emitter = new MaterialSum(3, emissionMaterials);

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

    double uv3[3][2] = {{1, 1},
                        {1, 0},
                        {0, 0}};
    Vector3d p3[3] = {Vector3d( 0.5, -1.5, 4),
                      Vector3d( 0.5, -1.5, 3.5),
                      Vector3d(-0.5, -1.5, 3.5)};
    Triangle t3(*emitter, p3, uv3);

    double uv4[3][2] = {{1, 1},
                        {0, 0},
                        {0, 1}};
    Vector3d p4[3] = {Vector3d( 0.5, -1.5, 4),
                      Vector3d(-0.5, -1.5, 3.5),
                      Vector3d(-0.5, -1.5, 4)};
    Triangle t4(*emitter, p4, uv4);

    double uv5[3][2] = {{0, 0},
                        {0, 1},
                        {1, 1}};
    Vector3d p5[3] = {Vector3d( 1.5,  1.5, 5),
                      Vector3d( 1.5, -1.5, 5),
                      Vector3d(-1.5, -1.5, 5)};
    Triangle t5(*greenMaterial, p5, uv5);

    double uv6[3][2] = {{0, 0},
                        {1, 1},
                        {1, 0}};
    Vector3d p6[3] = {Vector3d( 1.5,  1.5, 5),
                      Vector3d(-1.5, -1.5, 5),
                      Vector3d(-1.5,  1.5, 5)};
    Triangle t6(*greenMaterial, p6, uv6);

    double uv7[3][2] = {{0, 0},
                        {0, 1},
                        {1, 1}};
    Vector3d p7[3] = {Vector3d(1.5,  1.5, -0.1),
                      Vector3d(1.5, -1.5, -0.1),
                      Vector3d(1.5, -1.5, 5)};
    Triangle t7(*greenMaterial, p7, uv7);

    double uv8[3][2] = {{0, 0},
                        {1, 1},
                        {1, 0}};
    Vector3d p8[3] = {Vector3d(1.5,  1.5, -0.1),
                      Vector3d(1.5, -1.5, 5),
                      Vector3d(1.5,  1.5, 5)};
    Triangle t8(*greenMaterial, p8, uv8);

    double uv9[3][2] = {{0, 0},
                        {0, 1},
                        {1, 1}};
    Vector3d p9[3] = {Vector3d(-1.5,  1.5,  5),
                      Vector3d(-1.5, -1.5,  5),
                      Vector3d(-1.5, -1.5, -0.1)};
    Triangle t9(*greenMaterial, p9, uv9);

    double uv10[3][2] = {{0, 0},
                         {1, 1},
                         {1, 0}};
    Vector3d p10[3] = {Vector3d(-1.5,  1.5,  5),
                       Vector3d(-1.5, -1.5, -0.1),
                       Vector3d(-1.5,  1.5, -0.1)};
    Triangle t10(*greenMaterial, p10, uv10);

    double uv11[3][2] = {{0, 0},
                         {0, 1},
                         {1, 1}};
    Vector3d p11[3] = {Vector3d(-1.5, 1.5,  5),
                       Vector3d(-1.5, 1.5, -0.1),
                       Vector3d( 1.5, 1.5, -0.1)};
    Triangle t11(*greenMaterial, p11, uv11);

    double uv12[3][2] = {{0, 0},
                         {1, 1},
                         {1, 0}};
    Vector3d p12[3] = {Vector3d(-1.5, 1.5,  5),
                       Vector3d( 1.5, 1.5, -0.1),
                       Vector3d( 1.5, 1.5,  5)};
    Triangle t12(*greenMaterial, p12, uv12);

    double uv13[3][2] = {{0, 0},
                         {0, 1},
                         {1, 1}};
    Vector3d p13[3] = {Vector3d(-0.5, -1.5,  4),
                       Vector3d(-0.5, -1.5,  3.5),
                       Vector3d(-1.5, -1.5, -0.1)};
    Triangle t13(*greenMaterial, p13, uv13);

    double uv14[3][2] = {{0, 0},
                         {1, 1},
                         {1, 0}};
    Vector3d p14[3] = {Vector3d(-0.5, -1.5,  4),
                       Vector3d(-1.5, -1.5, -0.1),
                       Vector3d(-1.5, -1.5,  5)};
    Triangle t14(*greenMaterial, p14, uv14);

    double uv15[3][2] = {{0, 0},
                         {0, 1},
                         {1, 1}};
    Vector3d p15[3] = {Vector3d(1.5, -1.5,  5),
                       Vector3d(1.5, -1.5, -0.1),
                       Vector3d(0.5, -1.5,  3.5)};
    Triangle t15(*greenMaterial, p15, uv15);

    double uv16[3][2] = {{0, 0},
                         {1, 1},
                         {1, 0}};
    Vector3d p16[3] = {Vector3d(1.5, -1.5, 5),
                       Vector3d(0.5, -1.5, 3.5),
                       Vector3d(0.5, -1.5, 4)};
    Triangle t16(*greenMaterial, p16, uv16);

    double uv17[3][2] = {{0, 0},
                         {0, 1},
                         {1, 1}};
    Vector3d p17[3] = {Vector3d( 1.5, -1.5, 5),
                       Vector3d( 0.5, -1.5, 4),
                       Vector3d(-0.5, -1.5, 4)};
    Triangle t17(*greenMaterial, p17, uv17);

    double uv18[3][2] = {{0, 0},
                         {1, 1},
                         {1, 0}};
    Vector3d p18[3] = {Vector3d( 1.5, -1.5, 5),
                       Vector3d(-0.5, -1.5, 4),
                       Vector3d(-1.5, -1.5, 5)};
    Triangle t18(*greenMaterial, p18, uv18);

    double uv19[3][2] = {{0, 0},
                         {0, 1},
                         {1, 1}};
    Vector3d p19[3] = {Vector3d(-1.5, -1.5, -0.1),
                       Vector3d(-0.5, -1.5,  3.5),
                       Vector3d( 0.5, -1.5,  3.5)};
    Triangle t19(*greenMaterial, p19, uv19);

    double uv20[3][2] = {{0, 0},
                         {1, 1},
                         {1, 0}};
    Vector3d p20[3] = {Vector3d(-1.5, -1.5, -0.1),
                       Vector3d( 0.5, -1.5,  3.5),
                       Vector3d( 1.5, -1.5, -0.1)};
    Triangle t20(*greenMaterial, p20, uv20);

    double uv21[3][2] = {{0, 0},
                         {0, 1},
                         {1, 1}};
    Vector3d p21[3] = {Vector3d(-1.5, -1.5, -0.1),
                       Vector3d( 1.5, -1.5, -0.1),
                       Vector3d( 1.5,  1.5, -0.1)};
    Triangle t21(*greenMaterial, p21, uv21);

    double uv22[3][2] = {{0, 0},
                         {1, 1},
                         {1, 0}};
    Vector3d p22[3] = {Vector3d(-1.5,  1.5, -0.1),
                       Vector3d(-1.5, -1.5, -0.1),
                       Vector3d( 1.5,  1.5, -0.1)};
    Triangle t22(*greenMaterial, p22, uv22);

    GeometryCollector gc;

    gc.addGeometry(t1);
    gc.addGeometry(t2);
    gc.addGeometry(t3);
    gc.addGeometry(t4);
    gc.addGeometry(t5);
    gc.addGeometry(t6);
    gc.addGeometry(t7);
    gc.addGeometry(t8);
    gc.addGeometry(t9);
    gc.addGeometry(t10);
    gc.addGeometry(t11);
    gc.addGeometry(t12);
    gc.addGeometry(t13);
    gc.addGeometry(t14);
    gc.addGeometry(t15);
    gc.addGeometry(t16);
    gc.addGeometry(t17);
    gc.addGeometry(t18);
    gc.addGeometry(t19);
    gc.addGeometry(t20);
    gc.addGeometry(t21);
    gc.addGeometry(t22);

    gc.endGeometries();

    GeometryCollector egc;

    egc.addGeometry(t3);
    egc.addGeometry(t4);

    egc.endGeometries();

    DefaultRender(*camera, gc, egc).rendering();

    delete redEmission;
    delete greenEmission;
    delete blueEmission;
    delete emitter;
    delete greenMaterial;
    delete blueMaterial;
    delete geometry;
    delete material;
    delete camera;

    return 0;
}
