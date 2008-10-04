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

#ifndef IMAGE_H
#define IMAGE_H
#include <memory> //Per auto_ptr
#include <boost/smart_ptr.hpp> //Per scoped_array
#include <string>
#include <ImfOutputFile.h>

/* Classe per leggere e scrivere un'immagine */
//TODO: Eseguire la lettura di un'immagine
class Image
{
    public:
        /* Un pixel */
        struct RGBA
        {
            float r, g, b, a;

            inline RGBA() : r(0), g(0), b(0), a(0) {}

            inline RGBA(float red, float green, float blue, float alpha) :
                r(red), g(green), b(blue), a(alpha) {}

            inline RGBA &operator+=(const RGBA &ob)
            {
                r += ob.r;
                g += ob.g;
                b += ob.b;
                a += ob.a;

                return *this;
            }

            inline RGBA operator/(double ob) const
            {
                RGBA rgba(r, g, b, a);

                rgba.r /= ob;
                rgba.g /= ob;
                rgba.b /= ob;
                rgba.a /= ob;

                return rgba;
            }
        };

    protected:
        /* Puntatori usati all'interno della classe. Scope automatico */
        boost::scoped_array<RGBA> data;
        std::auto_ptr<Imf::OutputFile> file;

        /* Dimensioni dell'immagine */
        unsigned int m_w, m_h;

    public:
        /* Azioni compibili con la classe (attualmente solo la creazione di
         * un'immagine)
         */
        enum Action {Create};

        /* Costruttore che accetta il nome del file, le dimensioni
         * dell'immagine e l'azione da compiere
         */
        Image(const std::string &filename, unsigned int w, unsigned int h,
                enum Action action);

        /* Scrive le successive n linee dopo quelle che sono state scritte
         * fino ad ora, dall'alto verso il basso
         */
        void writeLines(unsigned int n);

        /* Come writeLines ma scrive una sola linea */
        void writeLine();

        /* Prende il puntatore ad una colonna di pixel.
         * Notare che è possibile accedere alla struttura RGBA di un pixel
         * usando image[x][y].
         */
        inline RGBA *operator[](unsigned int x)
        {
            return &data[x * m_h];
        }

        /* Funzione equivalente alla precedente ma per oggetti const
         */
        inline const RGBA *operator[](unsigned int x) const
        {
            return &data[x * m_h];
        }

        inline unsigned int w() const
        {
            return m_w;
        }

        inline unsigned int h() const
        {
            return m_h;
        }
};

#endif
