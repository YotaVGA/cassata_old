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

#ifndef CAMERA_H
#define CAMERA_H

#include "Image.h"
#include "Geometry.h"
#include "Material.h"
#include "Ray.h"
#include "Integrator.h"
#include <boost/smart_ptr.hpp> //Per scoped_array

class Camera : public Image
{
    protected:
        boost::scoped_array<Integrator<> > integrators;

    public:
        Camera(const std::string &filename, unsigned int w, unsigned int h) :
            Image(filename, w, h, Create),
            integrators(new Integrator<>[w*h]) {}

        virtual void distribution(Ray outs[], unsigned int x, unsigned int y,
                unsigned int start, unsigned int stop, unsigned int jitx,
                unsigned int jity) const = 0;

        inline void distribution(Ray outs[], unsigned int x, unsigned int y,
                unsigned int stop) const
        {
            distribution(outs, x, y, 0, stop, 1, 1);
        }

        inline void distribution(Ray outs[], unsigned int x, unsigned int y,
                unsigned int jitx, unsigned int jity) const
        {
            distribution(outs, x, y, 0, jitx * jity, jitx, jity);
        }

        virtual void wavelenghtDistribution(double outs[], const Ray &ray,
                unsigned int start, unsigned int stop,
                unsigned int jit) const = 0;

        inline void wavelenghtDistribution(double outs[], const Ray &ray,
                unsigned int stop, unsigned int jit) const
        {
            wavelenghtDistribution(outs, ray, 0, stop, jit);
        }

        inline void wavelenghtDistribution(double outs[], const Ray &ray,
                unsigned int jit) const
        {
            wavelenghtDistribution(outs, ray, 0, jit, jit);
        }

        inline Integrator<> &integrator(unsigned int x, unsigned int y)
        {
            return integrators[x + y * m_w];
        }

        /* Funzione equivalente alla precedente ma per oggetti const
         */
        inline const Integrator<> &integrator(unsigned int x,
                unsigned int y) const
        {
            return integrators[x + y * m_w];
        }

        inline void finalizePixel(unsigned int x, unsigned int y)
        {
            (*this)[x][y] = integrator(x, y).value();
        }

        virtual double energy(const Ray out, double lambda,
                unsigned int channel) = 0;

        virtual double probability(const Ray out, double lambda,
                unsigned int channel) = 0;

        virtual unsigned int pixelX(const Ray &ray) const = 0;
        virtual unsigned int pixelY(const Ray &ray) const = 0;

        virtual Geometry &geometry() = 0;
        virtual const Geometry &geometry() const = 0;
};

#endif
