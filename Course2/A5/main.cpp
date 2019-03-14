#include <iostream>
#include "matrix.h"
#include "row.h"
#include "image.h"

using namespace std;

int main()
{
	Matrix matrix;
	cin >> matrix;
	string s;
	cin >> s;
	Image img(s);
	Image img2;
	img2 = !img;
	img2.save("negative.bmp");

	Image img3;
	double a = 1;
	cin >> a;
	img3 = img * (a * matrix);
	img3.save("result.bmp");

	return 0;
}
