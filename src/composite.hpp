//
//  composite.hpp
//  Pixel 2
//
//  Created by Indi Kernick on 18/2/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#ifndef composite_hpp
#define composite_hpp

#include "cell.hpp"

QImage compositeFrame(const Palette &, const Frame &);
void compositeOverlay(QImage &, const QImage &);

#endif
