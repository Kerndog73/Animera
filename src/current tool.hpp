//
//  current tool.hpp
//  Pixel 2
//
//  Created by Indi Kernick on 24/2/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef current_tool_hpp
#define current_tool_hpp

#include "tool.hpp"

class CurrentTool {
public:
  void changeTool(Tool *);
  void changeCell(Cell *);
  ToolChanges mouseDown(const ToolMouseEvent &);
  ToolChanges mouseMove(const ToolMouseEvent &);
  ToolChanges mouseUp(const ToolMouseEvent &);

private:
  Tool *tool = nullptr;
  Cell *cell = nullptr;
  QPoint lastPos = {-1, -1};
  ButtonType button = ButtonType::none;
  bool enabled = false;
  
  void attach();
  void detach();
};

#endif
