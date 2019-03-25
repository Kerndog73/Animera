//
//  tool select widget.hpp
//  Pixel 2
//
//  Created by Indi Kernick on 10/3/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef tool_select_widget_hpp
#define tool_select_widget_hpp

#include "current tool.hpp"
#include <QtWidgets/qscrollarea.h>

class ToolWidget;

class ToolSelectWidget final : public QScrollArea {
  Q_OBJECT

  friend class ToolWidget;

public:
  explicit ToolSelectWidget(QWidget *);

Q_SIGNALS:
  void cellModified();
  void overlayModified();
  void updateStatusBar(const std::string &);

public Q_SLOTS:
  void mouseLeave();
  void mouseDown(QPoint, ButtonType, QImage *);
  void mouseMove(QPoint, QImage *);
  void mouseUp(QPoint, ButtonType, QImage *);
  void keyPress(Qt::Key, QImage *);
  void changeCell(Cell *);
  
private:
  QWidget *box;
  std::vector<ToolWidget *> tools;
  CurrentTool currTool;
  ToolWidget *currWidget = nullptr;
  ToolColors colors;
  
  void changeTool(ToolWidget *, Tool *);
  template <typename WidgetClass>
  ToolWidget *makeToolWidget();
  
  void emitModified(ToolChanges);
};

#endif
