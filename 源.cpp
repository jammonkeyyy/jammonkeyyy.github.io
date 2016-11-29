#include<iostream>
#include<cmath>

using namespace std;
double compute_line_k(double p1x, double p1y, double p2x, double p2y)
{
	double k;
	k = (p1y - p2y) / (p1x - p2x);
	return k;
}
double compute_line_b(double p1x, double p1y, double p2x, double p2y)
{
	double b;
	b = p1y - compute_line_k(p1x, p1y, p2x, p2y)*p1x;

	return b;
}
bool max(double x1,double x2)
{
	if (x1 > x2)
		return true;
	else
		return false;
	
}
void draw_line(double p1x, double p1y, double p2x, double p2y,double p3x,double p3y)
{
	
	double x1, k2, k3, k1, b1, b2, b3;
	if (p1x == p2x == p3x || p1y == p2y == p3y)

		cout << "不能构成三角形" << endl;
   else if (p1x==p2x||p3x==p1x||p2x==p3x)
	{
		if (p1x == p2x&&p1x != p3x)
		{
			x1 = p1x;
			k2 = compute_line_k(p1x, p1y, p3x, p3y);
			k3 = compute_line_k(p2x, p2y, p3x, p3y);
			b2 = compute_line_b(p1x, p1y, p3x, p3y);
			b3 = compute_line_b(p2x, p2y, p3x, p3y);
		}
		else if (p1x == p3x&&p2x != p3x)
		{
			x1 = p1x;
			k2 = compute_line_k(p1x, p1y, p2x, p2y);
			k3 = compute_line_k(p2x, p2y, p3x, p3y);
			b2 = compute_line_b(p1x, p1y, p2x, p2y);
			b3 = compute_line_b(p2x, p2y, p3x, p3y);
		}
		else if (p2x == p3x || p1x != p2x)
		 {
				x1 = p2x;
				k2 = compute_line_k(p1x, p1y, p2x, p2y);
				k3 = compute_line_k(p1x, p1y, p3x, p3y);
				b2 = compute_line_b(p1x, p1y, p2x, p2y);
				b3 = compute_line_b(p1x, p1y, p3x, p3y);
		}
		
		
		for (double j =-20; fabs(j - 20) > 1e-6; j = j + 0.3)
		{
			for (double i = -20; fabs(i -20) > 1e-6; i = i + 0.3)
			{
				if (fabs(j - k2*i - b2) < 0.1 || fabs(j - k3*i - b3) < 0.1||i==x1)
					cout << "*";
				else
					cout << " ";
			}
			cout << "\n";
		}
	}
	else if (p1x != p2x != p3x)
	{
		k1 = compute_line_k(p1x, p1y, p2x, p2y);
		k2 = compute_line_k(p2x, p2y, p3x, p3y);
		k3 = compute_line_k(p1x, p1y, p3x, p3y);
		b1 = compute_line_b(p1x, p1y, p2x, p2y);
		b2 = compute_line_b(p2x, p2y, p3x, p3y);
		b3 = compute_line_b(p1x, p1y, p3x, p3y);

		for (double j = -20; fabs(j - 20) > 1e-6; j = j + 0.5)
		{
			for (double i = -20; fabs(i - 20) > 1e-6; i = i + 0.5)
			{
				if (fabs(j - k2*i - b2) < 0.1 || fabs(j - k3*i - b3) < 0.1 || fabs(j - k1*i - b1) < 0.1)
					cout << "*";
				else
					cout << " ";
			}
			cout << "\n";
		}
	}

}
int main()
{
	double  p1x, p1y, p2x, p2y, p3x, p3y;
	cin >> p1x >> p1y >> p2x >> p2y >> p3x >> p3y;

	draw_line(p1x, p1y, p2x, p2y, p3x, p3y);
		
	
	return 0;
}