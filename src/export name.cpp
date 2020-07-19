﻿//
//  export name.cpp
//  Animera
//
//  Created by Indiana Kernick on 15/7/20.
//  Copyright © 2020 Indiana Kernick. All rights reserved.
//

#include "export name.hpp"

#include "strings.hpp"

namespace {

void appendSep(QString &str) {
  if (!str.isEmpty()) str.append(' ');
}

}

QString evaluateExportName(const ExportNameParams &params, const ExportNameState &state) {
  QString name = params.name;
  
  switch (params.layerName) {
    case LayerNameMode::automatic:
      if (state.layerCount <= LayerIdx{1}) break;
    case LayerNameMode::name:
      appendSep(name);
      name += toLatinString(state.layerName);
      break;
    case LayerNameMode::index:
      appendSep(name);
      name += QString::number(+state.layer);
      break;
    case LayerNameMode::empty:
      break;
  }
  
  switch (params.groupName) {
    case GroupNameMode::automatic:
      if (state.groupCount <= GroupIdx{1}) break;
    case GroupNameMode::name:
      appendSep(name);
      name += toLatinString(state.groupName);
      break;
    case GroupNameMode::index:
      appendSep(name);
      name += QString::number(+state.group);
      break;
    case GroupNameMode::empty:
      break;
  }
  
  switch (params.frameName) {
    case FrameNameMode::automatic:
      if (state.frameCount <= FrameIdx{1}) break;
    case FrameNameMode::relative:
      appendSep(name);
      name += QString::number(+(state.frame - state.groupBegin));
      break;
    case FrameNameMode::absolute:
      appendSep(name);
      name += QString::number(+state.frame);
      break;
    case FrameNameMode::empty:
      break;
  }
  
  return name;
}
