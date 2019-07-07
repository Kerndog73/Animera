//
//  editor widget.hpp
//  Pixel 2
//
//  Created by Indi Kernick on 10/3/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef editor_widget_hpp
#define editor_widget_hpp

#include "tool.hpp"
#include "cell.hpp"
#include "palette.hpp"
#include "scroll bar widget.hpp"

class EditorImage;

class EditorWidget final : public ScrollAreaWidget {
  Q_OBJECT

public:
  explicit EditorWidget(QWidget *);

Q_SIGNALS:
  void mouseLeave(QImage *);
  void mouseDown(QPoint, ButtonType, QImage *);
  void mouseMove(QPoint, QImage *);
  void mouseUp(QPoint, ButtonType, QImage *);
  void keyPress(Qt::Key, QImage *);

public Q_SLOTS:
  void composite();
  void compositeOverlay();
  void compositePalette();
  void setFrame(const Frame &);
  void setPalette(PaletteCSpan);
  void initCanvas(Format, QSize);

private:
  EditorImage *view;
  Frame frame;
  PaletteCSpan palette;
  QSize size;
  Format format;

  void resizeEvent(QResizeEvent *) override;
};

#endif
