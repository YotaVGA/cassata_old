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

#ifndef PINHOLECAMERA_H
#define PINHOLECAMERA_H

#include <eigen/projective.h>
#include "Camera.h"
#include "PointGeometry.h"
#include "BlackMaterial.h"
#include "Gaussian.h"

class PinholeCamera : public Camera
{
    protected:
        const Eigen::MatrixP3d *matrix, *invmatrix;
        Eigen::Vector3d p;
        PointGeometry g;
        const BlackMaterial vm;
        Gaussian R, G, B;

    public:
        PinholeCamera(const std::string &filename, unsigned int w,
                unsigned int h, const Eigen::MatrixP3d &m,
                const Eigen::MatrixP3d &invmatrix) :
                                                   Camera(filename, w, h),
                                                   matrix(&m),
                                                   invmatrix(&invmatrix),
                                                   p(m * Eigen::Vector3d(0,
                                                               0, 0)),
                                                   g(vm, p), R(575, 85),
                                                   G(535, 100), B(445, 50)
        {}

        virtual void distribution(Ray outs[], unsigned int x, unsigned int y,
                unsigned int start, unsigned int stop, unsigned int jitx,
                unsigned int jity) const;

        virtual void wavelenghtDistribution(double outs[], const Ray &ray,
                unsigned int start, unsigned int stop,
                unsigned int jit) const;

        virtual double energy(const Ray out, double lambda,
                unsigned int channel);

        virtual double probability(const Ray out, double lambda,
                unsigned int channel);

        virtual unsigned int pixelX(const Ray &ray) const;
        virtual unsigned int pixelY(const Ray &ray) const;

        virtual Geometry &geometry();
        virtual const Geometry &geometry() const;
};

#endif

