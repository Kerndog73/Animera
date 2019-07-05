//
//  timeline widget.hpp
//  Pixel 2
//
//  Created by Indi Kernick on 10/3/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef timeline_widget_hpp
#define timeline_widget_hpp

#include "animation.hpp"
#include <QtWidgets/qwidget.h>

class ControlsWidget;
class LayersWidget;
class FramesWidget;
class CellsWidget;

class TimelineWidget final : public QWidget {
  Q_OBJECT
  
  friend class LayerCellsWidget;

public:
  explicit TimelineWidget(QWidget *);
  
public Q_SLOTS:
  void initCanvas(Format, QSize);
  void saveFile(const QString &) const;
  void openFile(const QString &);
  void changePalette(Palette *);
  
  void addLayer();
  void removeLayer();
  void moveLayerUp();
  void moveLayerDown();
  void toggleLayerVisible();
  
  void addFrame();
  void addNullFrame();
  void removeFrame();
  
  void clearFrame();
  void extendFrame();
  
  void requestCell();
  void toggleAnimation();
  
  void layerAbove();
  void layerBelow();
  void nextFrame();
  void prevFrame();

Q_SIGNALS:
  void posChanged(Cell *, LayerIdx, FrameIdx);
  void visibleChanged(const LayerVisible &);
  void frameChanged(const Frame &);
  void canvasInitialized(Format, QSize);
  void composite();

private:
  ControlsWidget *controls = nullptr;
  LayersWidget *layers = nullptr;
  FramesWidget *frames = nullptr;
  CellsWidget *cells = nullptr;
  Palette *palette = nullptr;
  QSize size;
  Format format;
};

#endif
