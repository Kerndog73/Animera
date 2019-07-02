//
//  composite.cpp
//  Pixel 2
//
//  Created by Indi Kernick on 18/2/19.
//  Copyright © 2019 Indi Kernick. All rights reserved.
//

#include "composite.hpp"

#include "config.hpp"
#include "masking.hpp"
#include "formats.hpp"
#include "porter duff.hpp"
#include "surface factory.hpp"

namespace {

std::vector<Image> getImages(const Frame &frame, const LayerVisible &visible) {
  assert(frame.size() == visible.size());
  std::vector<Image> images;
  images.reserve(frame.size());
  for (size_t i = 0; i != frame.size(); ++i) {
    if (frame[i] && !frame[i]->image.data.isNull() && visible[i]) {
      images.push_back(frame[i]->image);
    }
  }
  return images;
}

void compositeColor(Surface<PixelColor> output, const std::vector<Image> &images) {
  // Layer 0 is on top of layer 1
  for (auto i = images.rbegin(); i != images.rend(); ++i) {
    porterDuff(
      mode_src_over,
      output,
      makeCSurface<PixelColor>(i->data),
      FormatARGB{},
      FormatARGB{}
    );
  }
}

void compositePalette(Surface<PixelColor> output, const std::vector<Image> &images, const Palette *palette) {
  assert(palette);
  FormatPalette format{palette->data(), palette->size()};
  for (auto i = images.rbegin(); i != images.rend(); ++i) {
    porterDuff(
      mode_src_over,
      output,
      makeCSurface<PixelPalette>(i->data),
      FormatARGB{},
      format
    );
  }
}

void compositeGray(Surface<PixelColor> output, const std::vector<Image> &images) {
  for (auto i = images.rbegin(); i != images.rend(); ++i) {
    porterDuff(
      mode_src_over,
      output,
      makeCSurface<PixelGray>(i->data),
      FormatARGB{},
      FormatGray{}
    );
  }
}

}

QImage compositeFrame(
  const Palette *palette,
  const Frame &frame,
  const LayerVisible &visible,
  const QSize size,
  const Format format
) {
  std::vector<Image> images = getImages(frame, visible);
  QImage output{size, qimageFormat(Format::color)};
  clearImage(output);
  Surface<PixelColor> outputSurface = makeSurface<PixelColor>(output);
  
  switch (format) {
    case Format::color:
      compositeColor(outputSurface, images);
      break;
    case Format::palette:
      compositePalette(outputSurface, images, palette);
      break;
    case Format::gray:
      compositeGray(outputSurface, images);
      break;
  }

  return output;
}

void compositeOverlay(QImage &drawing, const QImage &overlay) {
  porterDuff(
    mode_src_over,
    makeSurface<PixelColor>(drawing),
    makeSurface<PixelColor>(overlay),
    FormatARGB{},
    FormatARGB{}
  );
}

void blitImage(QImage &dst, const QImage &src, const QPoint pos) {
  visitSurfaces(dst, src, [pos](auto dstSurface, auto srcSurface) {
    copyRegion(
      dstSurface,
      srcSurface,
      pos
    );
  });
}

QImage blitImage(const QImage &src, const QRect rect) {
  // @TODO does it really make sense allocate a new QImage?
  QImage dst{rect.size(), src.format()};
  visitSurfaces(dst, src, [pos = rect.topLeft()](auto dstSurface, auto srcSurface) {
    copyRegion(
      dstSurface,
      srcSurface,
      -pos
    );
  });
  return dst;
}

void blitMaskImage(QImage &dst, const QImage &mask, const QImage &src, const QPoint pos) {
  assert(mask.size() == src.size());
  visitSurfaces(dst, src, [&mask, pos](auto dstSurface, auto srcSurface) {
    maskCopyRegion(
      dstSurface,
      srcSurface,
      makeSurface<PixelMask>(mask),
      pos,
      pos
    );
  });
}

QImage blitMaskImage(const QImage &src, const QImage &mask, const QPoint pos) {
  // @TODO does it really make sense allocate a new QImage?
  QImage dst{mask.size(), src.format()};
  visitSurfaces(dst, src, [&mask, pos](auto dstSurface, auto srcSurface) {
    maskCopyRegion(
      dstSurface,
      srcSurface,
      makeSurface<PixelMask>(mask),
      -pos,
      {0, 0}
    );
  });
  return dst;
}

namespace {

void colorToOverlay(const Surface<QRgb> surface) {
  for (auto row : surface.range()) {
    for (QRgb &pixel : row) {
      const int gray = qGray(pixel);
      const int alpha = std::max(tool_overlay_alpha_min, qAlpha(pixel) * 3 / 4);
      pixel = qRgba(gray, gray, gray, alpha);
    }
  }
}

}

void colorToOverlay(QImage &img) {
  assert(img.format() == qimageFormat(Format::color));
  colorToOverlay(makeSurface<PixelColor>(img));
}

void colorToOverlay(QImage &img, const QImage &mask) {
  assert(img.format() == qimageFormat(Format::color));
  assert(img.size() == mask.size());
  const Surface surface = makeSurface<PixelColor>(img);
  colorToOverlay(surface);
  maskClip(surface, makeCSurface<PixelMask>(mask));
}
