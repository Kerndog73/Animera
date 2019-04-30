//
//  color slider widget.hpp
//  Pixel 2
//
//  Created by Indi Kernick on 29/4/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef color_slider_widget_hpp
#define color_slider_widget_hpp

#include "color convert.hpp"
#include <QtWidgets/qwidget.h>

template <typename Derived>
class ColorSliderWidget : public QWidget {
public:
  explicit ColorSliderWidget(QWidget *);

protected:
  QImage graph;

private:
  QPixmap bar;
  bool mouseDown = false;
  
  void initBar();
  void renderGraph(QPainter &);
  void renderBar(QPainter &);
  
  void paintEvent(QPaintEvent *) override;
  
  void setColor(QMouseEvent *);
  
  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

class HueSliderWidget final : public ColorSliderWidget<HueSliderWidget> {
  Q_OBJECT
  
  friend class ColorSliderWidget<HueSliderWidget>;

public:
  explicit HueSliderWidget(QWidget *);

Q_SIGNALS:
  void hueChanged(int);

public Q_SLOTS:
  void changeHue(int);
  void changeSV(int, int);
  void changeHSV(HSV);
  
private:
  HSV color;
  
  void plotGraph();
  void renderBackground(QPainter &);
  
  int getPixel();
  void setColor(int);
};

class AlphaSliderWidget final : public ColorSliderWidget<AlphaSliderWidget> {
  Q_OBJECT
  
  friend class ColorSliderWidget<AlphaSliderWidget>;
  
public:
  explicit AlphaSliderWidget(QWidget *);
  
Q_SIGNALS:
  void alphaChanged(int);

public Q_SLOTS:
  void changeAlpha(int);
  void changeHue(int);
  void changeSV(int, int);
  void changeHSV(HSV);
  
private:
  HSV color;
  int alpha;
  
  void plotGraph();
  void renderBackground(QPainter &);
  
  int getPixel();
  void setColor(int);
};

#endif