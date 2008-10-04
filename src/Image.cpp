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

#include <cstring> //Per memset
#include <ImfChannelList.h>
#include "Image.h"

using namespace Imf;
using namespace boost;
using namespace std;

Image::Image(const string &filename, unsigned int w, unsigned int h,
        enum Action action) : data(new RGBA[w * h]), m_w(w), m_h(h)
{
    /* Creo un header */
    Header header(w, h);
    /* Gli inserisco i canali */
    header.channels().insert("R", Channel(FLOAT));
    header.channels().insert("G", Channel(FLOAT));
    header.channels().insert("B", Channel(FLOAT));
    header.channels().insert("A", Channel(FLOAT));

    /* Creo il file */
    file = auto_ptr<OutputFile>(new OutputFile(filename.c_str(),
                header));

    /* Creo un framebuffer */
    FrameBuffer framebuffer;

    /* Assegno al framebuffer gli slice dei dati corrispondenti ai vari
     * colori
     */
    framebuffer.insert("R", Slice(FLOAT, (char *)&data[0].r,
                sizeof(struct RGBA) * h, sizeof(struct RGBA)));
    framebuffer.insert("G", Slice(FLOAT, (char *)&data[0].g,
                sizeof(struct RGBA) * h, sizeof(struct RGBA)));
    framebuffer.insert("B", Slice(FLOAT, (char *)&data[0].b,
                sizeof(struct RGBA) * h, sizeof(struct RGBA)));
    framebuffer.insert("A", Slice(FLOAT, (char *)&data[0].a,
                sizeof(struct RGBA) * h, sizeof(struct RGBA)));

    /* Azzero il contenuto dell'immagine (nero puro e completamente
     * trasparente
     */
    memset(data.get(), 0, sizeof(RGBA) * w * h);

    /* setto il framebuffer nel file */
    file->setFrameBuffer(framebuffer);
}

void Image::writeLines(unsigned int n)
{
    /* Scrivo n linee */
    file->writePixels(n);
}

void Image::writeLine()
{
    /* Scrivo una linea */
    writeLines(1);
}
