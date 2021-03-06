﻿//
//  current tool.cpp
//  Animera
//
//  Created by Indiana Kernick on 24/2/19.
//  Copyright © 2019 Indiana Kernick. All rights reserved.
//

#include "current tool.hpp"

void CurrentTool::setTool(Tool *newTool) {
  assert(newTool);
  detach();
  tool = newTool;
  attach();
}

void CurrentTool::setCel(CelImage *newCel) {
  assert(newCel);
  detach();
  cel = newCel;
  attach();
}

void CurrentTool::mouseEnter(const QPoint ePos) {
  assert(tool);
  if (button == ButtonType::none) {
    if (lastPos == QPoint{-1, -1}) {
      lastPos = ePos;
      tool->mouseMove({lastPos, lastPos, ButtonType::none});
    } else {
      tool->mouseMove({ePos, lastPos, ButtonType::none});
      lastPos = ePos;
    }
  }
}

void CurrentTool::mouseEnter() {
  assert(tool);
  if (button == ButtonType::none) {
    tool->mouseMove({lastPos, lastPos, ButtonType::none});
  }
}

void CurrentTool::mouseLeave() {
  assert(tool);
  if (button == ButtonType::none) {
    tool->mouseLeave({lastPos, ButtonType::none});
  }
}

void CurrentTool::mouseDown(const QPoint ePos, const ButtonType eButton) {
  assert(tool);
  if (button == ButtonType::none) {
    if (ePos != lastPos) {
      // I'm pretty sure this never happens but now we can safely assume so
      tool->mouseMove({ePos, lastPos, ButtonType::none});
    }
    lastPos = ePos;
    button = eButton;
    tool->mouseDown({ePos, eButton});
  }
}

void CurrentTool::mouseMove(const QPoint ePos) {
  assert(tool);
  if (ePos != lastPos) {
    tool->mouseMove({ePos, lastPos, button});
    lastPos = ePos;
  }
}

void CurrentTool::mouseUp(const QPoint ePos, const ButtonType eButton) {
  assert(tool);
  if (eButton == button) {
    if (ePos != lastPos) {
      // I'm pretty sure this never happens but now we can safely assume so
      tool->mouseMove({ePos, lastPos, button});
    }
    lastPos = ePos;
    button = ButtonType::none;
    tool->mouseUp({ePos, eButton});
  }
}

void CurrentTool::keyPress(const Qt::Key eKey) {
  assert(tool);
  tool->keyPress({eKey});
}

void CurrentTool::attach() {
  if (cel) tool->attachCelImage();
}

void CurrentTool::detach() {
  if (cel) tool->detachCelImage();
}
