//
//  status object.hpp
//  Animera
//
//  Created by Indiana Kernick on 12/11/19.
//  Copyright © 2019 Indiana Kernick. All rights reserved.
//

#ifndef animera_status_object_hpp
#define animera_status_object_hpp

#include "cel.hpp"
#include <QtCore/qobject.h>

class StatusObject final : public QObject {
  Q_OBJECT

public:
  explicit StatusObject(QObject *);

public Q_SLOTS:
  void setScale(int);
  void setPos(CelPos);
  void setSelection(CelRect);
  void setFrameCount(FrameIdx);
  void setLayerCount(LayerIdx);

Q_SIGNALS:
  void shouldShowPerm(std::string_view);
  void shouldShowApnd(std::string_view);

private:
  int scale = 1;
  CelPos pos;
  CelRect selection;
  FrameIdx frameCount;
  LayerIdx layerCount;
  
  enum class Updated {
    scale,
    cel,
    selection,
    timeline
  };
  
  void updateStatus(Updated);
};

#endif
