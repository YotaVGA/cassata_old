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

#ifndef BOX_H
#define BOX_H

#include <eigen/vector.h>

class Box
{
    protected:
        Eigen::Vector3d a, b;

    public:
        inline Box() : a(), b() {}
        inline Box(const Eigen::Vector3d &start,
                const Eigen::Vector3d &stop) : a(start), b(stop) {}
        inline Box(const Eigen::Vector3d &point) : a(point), b(point) {}

        inline const Eigen::Vector3d &start() const
        {
            return a;
        }

        inline const Eigen::Vector3d &stop() const
        {
            return b;
        }

        inline void setStart(const Eigen::Vector3d &start)
        {
            a = start;
        }

        inline void setStop(const Eigen::Vector3d &stop)
        {
            b = stop;
        }

        inline bool isInBox(const Eigen::Vector3d &point) const
        {
            if (a.x() >= point.x() || a.y() >= point.y() ||
                    a.z() >= point.z())
                return false;

            if (b.x() < point.x() || b.y() < point.y() || b.z() < point.z())
                return false;

            return true;
        }

        inline void enlargeBox(const Eigen::Vector3d &point)
        {
            a.x() = std::min(a.x(), point.x());
            a.y() = std::min(a.y(), point.y());
            a.z() = std::min(a.z(), point.z());

            b.x() = std::max(b.x(), point.x());
            b.y() = std::max(b.y(), point.y());
            b.z() = std::max(b.z(), point.z());
        }

        inline void enlargeBox(const Box &box)
        {
            enlargeBox(box.start());
            enlargeBox(box.stop());
        }
};

#endif
