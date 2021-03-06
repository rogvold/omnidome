/* Copyright (c) 2014-2016 "Omnidome" by Michael Winkelmann
 * Dome Mapping Projection Software (http://omnido.me).
 * Omnidome was created by Michael Winkelmann aka Wilston Oreo (@WilstonOreo)
 *
 * This file is part of Omnidome.
 *
 * Omnidome is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef OMNI_MEDIA_IMAGE_H_
#define OMNI_MEDIA_IMAGE_H_

#include <QImage>
#include <omni/media/Interface.h>

namespace omni {
  namespace media {
    class Image : public media::Interface {
      Image(QImage const& _image) :
        image_(_image) {}
      ~Image() {}

      QImage const& image() const;
      QImage& image() const;

    public:

      QImage image_;
    }
  }
}

#endif /* OMNI_MEDIA_IMAGE_H_ */
