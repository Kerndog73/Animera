//
//  tool.cpp
//  Pixel 2
//
//  Created by Indi Kernick on 18/2/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#include "tool.hpp"

Tool::~Tool() = default;

ToolChanges Tool::keyPress(const ToolKeyEvent &event) {
  return ToolChanges::none;
}
