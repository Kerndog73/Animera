﻿//
//  cel span painter.cpp
//  Animera
//
//  Created by Indiana Kernick on 11/7/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#include "cel span painter.hpp"

#include <QtGui/qpainter.h>
#include "config colors.hpp"
#include "config geometry.hpp"
#include "widget painting.hpp"

CelSpanPainter::CelSpanPainter() {
  celPix = bakeColoredBitmap(":/Timeline/cel.png", cel_icon_color);
  beginLinkPix = bakeColoredBitmap(":/Timeline/begin linked cel.png", cel_icon_color);
  endLinkPix = bakeColoredBitmap(":/Timeline/end linked cel.png", cel_icon_color);
}

void CelSpanPainter::start(const int xOff, const int yOff) {
  x = xOff + cel_icon_pad;
  y = yOff;
}

void CelSpanPainter::start() {
  start(0, 0);
}

void CelSpanPainter::advance(const FrameIdx len) {
  x += +len * cel_width;
}

void CelSpanPainter::span(QPainter &painter, const FrameIdx len) const {
  if (len == FrameIdx{1}) {
    painter.drawPixmap(x, y + cel_icon_pad, celPix);
  } else if (len > FrameIdx{1}) {
    const int between = +(len - FrameIdx{2}) * cel_width;
    int xPos = x;
    painter.drawPixmap(xPos, y + cel_icon_pad, beginLinkPix);
    xPos += cel_width;
    painter.fillRect(
      xPos - cel_icon_pad - cel_border_offset, y + cel_icon_pad,
      between + cel_icon_pad + cel_border_offset, cel_icon_size,
      cel_icon_color
    );
    xPos += between;
    painter.drawPixmap(xPos, y + cel_icon_pad, endLinkPix);
  } else Q_UNREACHABLE();
}

void CelSpanPainter::border(QPainter &painter) const {
  painter.fillRect(
    x - cel_border_offset, y,
    glob_border_width, cel_height,
    glob_border_color
  );
}

int CelSpanPainter::posX() const {
  return x;
}

int CelSpanPainter::posY() const {
  return y;
}
