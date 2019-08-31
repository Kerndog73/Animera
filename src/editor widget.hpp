//
//  editor widget.hpp
//  Animera
//
//  Created by Indi Kernick on 10/3/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef editor_widget_hpp
#define editor_widget_hpp

#include "tool.hpp"
#include "cell.hpp"
#include "palette span.hpp"
#include "scroll bar widget.hpp"

class EditorImage;

class EditorWidget final : public ScrollAreaWidget {
  Q_OBJECT

public:
  explicit EditorWidget(QWidget *);

Q_SIGNALS:
  void overlayChanged(QImage *);
  void mouseLeave();
  void mouseDown(QPoint, ButtonType);
  void mouseMove(QPoint);
  void mouseUp(QPoint, ButtonType);
  void keyPress(Qt::Key);

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
  int startScale;

  bool event(QEvent *) override;
  void showEvent(QShowEvent *) override;
  void resizeEvent(QResizeEvent *) override;
};

#endif
