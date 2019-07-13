//
//  sprite.hpp
//  Pixel 2
//
//  Created by Indi Kernick on 7/7/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef sprite_hpp
#define sprite_hpp

#include "palette.hpp"
#include "timeline.hpp"
#include <QtCore/qobject.h>

class Sprite final : public QObject {
  Q_OBJECT

public Q_SLOTS:
  void newFile(Format, QSize);
  void saveFile(const QString &) const;
  void openFile(const QString &);
  
Q_SIGNALS:
  void canvasInitialized(Format, QSize);

public:
  Timeline timeline;
  Palette palette;

private:
  Format format;
  QSize size;
};

#endif