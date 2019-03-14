#include "image.h"
#include <iostream>

using namespace std;


Image::Image()
{
  image = bitmap_image();
}

Image::Image(string filename)
{
  image = bitmap_image(filename);
}

Image::Image(bitmap_image operand)
{
  image = operand;
}

Image& Image::operator=(const Image& operand)
{
  image = operand.image;
}

Image Image::operator!() const
{
  Image temp(image);
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  for (unsigned int i = 0; i < image.width(); i++)
  {
    for (unsigned int j = 0; j < image.height(); j++)
    {
      (temp.image).get_pixel(i, j, red, green, blue);
      (temp.image).set_pixel(i, j, 256 - red, 256 - green, 256 - blue);
    }
  }
  return temp;
}

Image Image::operator*(const Matrix& operand) const
{
  if (operand.height() != operand.width() || operand.height() % 2 == 0)
    throw ConvolveExeption();
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  bitmap_image temp= image;
  int sum_red = 0;
  int sum_green = 0;
  int sum_blue = 0;
  int p = ((operand.width() - 1) / 2);
  for (unsigned int i = p; i < image.width() - p; i++)
  {
    for (unsigned int j = p; j < image.height() - p; j++)
    {
      sum_red = sum_green = sum_blue = 0;
      for (int m = 0; m < operand.height(); m++)
      {
        for (int n = 0; n < operand.width(); n++)
        {
          unsigned int x = i - p + m;
          unsigned int y = j - p + n;
          image.get_pixel(x, y, red, green, blue);
          sum_red += red * operand[m][n];
          sum_green += green * operand[m][n];
          sum_blue += blue * operand[m][n];
        }
      }
      temp.set_pixel(i, j, sum_red, sum_green, sum_blue);
    }
  }
  return Image(temp);
}

int Image::height()
{
  return image.height();
}

int Image::width()
{
  return image.width();
}

void Image::save(string filepath)
{
  image.save_image(filepath);
}
