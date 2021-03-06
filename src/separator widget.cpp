﻿//
//  separator widget.cpp
//  Animera
//
//  Created by Indiana Kernick on 25/5/19.
//  Copyright © 2019 Indiana Kernick. All rights reserved.
//

#include "separator widget.hpp"

#include <QtGui/qpainter.h>
#include "config colors.hpp"
#include "config geometry.hpp"

HoriSeparator::HoriSeparator(QWidget *parent)
  : QWidget{parent} {
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  setMinimumWidth(glob_border_width);
  setFixedHeight(glob_border_width);
  setAttribute(Qt::WA_StaticContents);
}

void HoriSeparator::paintEvent(QPaintEvent *) {
  QPainter painter{this};
  painter.setPen(Qt::NoPen);
  painter.setBrush(glob_border_color);
  painter.drawRect(0, 0, width(), glob_border_width);
}

VertSeparator::VertSeparator(QWidget *parent)
  : QWidget{parent} {
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
  setFixedWidth(glob_border_width);
  setMinimumHeight(glob_border_width);
  setAttribute(Qt::WA_StaticContents);
}

void VertSeparator::paintEvent(QPaintEvent *) {
  QPainter painter{this};
  painter.setPen(Qt::NoPen);
  painter.setBrush(glob_border_color);
  painter.drawRect(0, 0, glob_border_width, height());
}
