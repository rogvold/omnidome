/* Copyright (c) 2014-2015 "Omnidome" by cr8tr
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

#include "HalfDome.h"
#include "HalfDomeWidget.h"

namespace omni {
    namespace ui {
        namespace canvas {
            HalfDome::HalfDome(QWidget *_parent) : CanvasParameters(_parent) {
                setup();
            }

            HalfDome::HalfDome(omni::canvas::Interface *_canvas, QWidget *_parent) :
                CanvasParameters(_canvas, _parent) {
                setup();
            }

            HalfDome::~HalfDome() {}

            void HalfDome::updateCanvasParameters() {
                auto *_halfdome = static_cast<omni::canvas::HalfDome *>(canvas());
                _halfdome->setDiameter(getParamAsFloat("Diameter"));
            }

            void HalfDome::setup() {
                if (!canvas()) return;

                this->locked([&]() {
                    auto* _diameter = addOffsetWidget("Diameter",5.0,0.5,20.0);

                    /// Retrieve parameters for HalfDome canvas
                    auto* _halfdome = static_cast<omni::canvas::HalfDome*>(canvas());
                    _diameter->setValue(_halfdome->diameter());
                });
            }
        }
    }
}
