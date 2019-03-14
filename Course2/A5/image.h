#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include "matrix.h"
#include "bitmap_image.h"
#include "error.h"

class Image
{
public:
  Image();
  Image(std::string);
  Image& operator=(const Image&);
  Image operator!() const;
  Image operator*(const Matrix&) const;
  int height();
  int width();
  void save(std::string);
private:
  Image(bitmap_image);
  bitmap_image image;
};



#endif
