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

#include "Canvas.h"

#include "ui_omni_ui_Canvas.h"

#include <QVBoxLayout>
#include <QVariant>

#include <omni/Session.h>
#include <omni/canvas/Interface.h>

namespace omni {
    namespace ui {
        Canvas::Canvas(QWidget *_parent) :
            DockWidget(ui_,_parent)
        {
            this->setup(ui_);

            // Add canvas types from Factory
            for (auto& _idCanvasClass : omni::canvas::Factory::classes())
            {
                QString _id = _idCanvasClass.first.str();
                ui_->boxCanvasSelect->addItem(QIcon(QString(":/canvas/") + _id +
                                                    QString(
                                                        ".png")), _id,
                                              QVariant(_id));
            }

            connect(ui_->boxCanvasSelect, SIGNAL(currentIndexChanged(QString)), this,
                    SLOT(selectCanvasType(QString)));
        }

        Canvas::~Canvas()
        {}

        void Canvas::dataToFrontend()
        {
            if (!dataModel()->canvas())
            {
                dataModel()->setCanvas("HalfDome");
                selectCanvasType("HalfDome");
            }
            // Search combobox for available canvas types
            int _index = 0;

            for (int i = 0; i < ui_->boxCanvasSelect->count(); ++i)
            {
                QString _id = ui_->boxCanvasSelect->itemData(i).toString();

                if (_id == dataModel()->canvas()->getTypeId().str())
                {
                    _index = i;
                }
            }

            ui_->boxCanvasSelect->setCurrentIndex(_index);
            showParameterWidget();
        }

        void Canvas::showParameterWidget() {
            if (!dataModel()) return;

            auto* _canvas = dataModel()->canvas();
            if (!_canvas) return;

            paramWidget_ = _canvas->widget();
            if (paramWidget_) {
                // Configure layout
                widget()->layout()->addWidget(paramWidget_);

                // Update parameter when canvas has changed
                connect(paramWidget_,SIGNAL(parametersUpdated()),this,SIGNAL(dataModelChanged()));
                paramWidget_->show();
            }
            emit canvasTypeChanged();
            emit dataModelChanged();

            ///   Remove widget on next mapping type change
            if (paramWidget_) {
                connect(this,SIGNAL(canvasTypeChanged()),paramWidget_,SLOT(deleteLater()));
            }
        }

        bool Canvas::frontendToData() {
            return false;
        }

        void Canvas::selectCanvasType(QString _id)
        {
            if (!dataModel() || this->isLocked()) return;

            dataModel()->setCanvas(_id);
            if (paramWidget_) {
                widget()->layout()->removeWidget(paramWidget_);
            }

            showParameterWidget();
        }
    }
}
