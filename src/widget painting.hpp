//
//  widget painting.hpp
//  Pixel 2
//
//  Created by Indi Kernick on 29/4/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef widget_painting_hpp
#define widget_painting_hpp

#include "config.hpp"
#include <QtGui/qpixmap.h>

QPixmap bakeColoredBitmaps(const QString &, const QString &, QColor, QColor);
QPixmap bakeColoredBitmaps(const QBitmap &, const QBitmap &, QColor, QColor);
void paintBorder(QPainter &, WidgetRect, QColor);

#endif
