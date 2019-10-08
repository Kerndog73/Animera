//
//  flood fill tool.hpp
//  Animera
//
//  Created by Indi Kernick on 14/7/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef flood_fill_tool_hpp
#define flood_fill_tool_hpp

#include "tool.hpp"

class FloodFillTool final : public Tool {
public:
  void detachCell(DetachReason) override;
  void mouseLeave(const ToolLeaveEvent &) override;
  void mouseDown(const ToolMouseEvent &) override;
  void mouseMove(const ToolMouseEvent &) override;
};

#endif
