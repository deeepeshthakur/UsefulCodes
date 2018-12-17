#include <bits/stdc++.h>

using namespace std;

// Function returns area of triangle of 3 points
double areaT(double x1, double y1, double x2, double y2, double x3, double y3){
	return std::abs((x1*y2 - x2*y1) + (x2*y3 - x3*y2) + (x3*y1 - x1*y3))/2.0;
}

// Returns area segment of a circle of radius r and distance between the points of intersection m
double areaSeg(double r, double m){
	return std::abs(std::asin(m/(2.0*r))*r*r) - (m*std::sqrt(r*r - (m*m/4.0))/2.0);
}

// Return area of intersection of a circle a origin of radius r and the area between the lines x1, x1, y1, y2 (or a rectangle)
// can be optimised for a square
double areaC(double r, double x1, double x2, double y1, double y2){
	if(x1 == x2 || y1 == y2){
		return 0.0;
	}
	if(x1*x2 >= 0 && y1*y2 >= 0){
		x1 = std::abs(x1);
		x2 = std::abs(x2);
		y1 = std::abs(y1);
		y2 = std::abs(y2);
		if(x1 > x2){
			std::swap(x1, x2);
		}
		if(y1 > y2){
			std::swap(y1, y2);
		}

		if(r*r >= (x2*x2 + y2*y2)){
			return (x2 - x1)*(y2 - y1);
		}
		else{
			if(r*r <= (x1*x1 + y1*y1)){
				return 0;
			}
			else{
				if(r*r <= std::min((x1*x1 + y2*y2), (x2*x2 + y1*y1))){
					double a = std::sqrt(r*r - x1*x1), b = std::sqrt(r*r - y1*y1);
					return areaT(x1, y1, x1, a, b, y1) + areaSeg(r, std::sqrt((x1 - b)*(x1 - b) + (y1 - a)*(y1 - a)));
				}
				else{
					if(r*r >= std::max((x1*x1 + y2*y2), (x2*x2 + y1*y1))){
						double b = std::sqrt(r*r - x2*x2), a = std::sqrt(r*r - y2*y2);
						return areaT(x1, y1, x1, y2, a, y2) + areaT(x1, y1, x2, y1, x2, b) + areaT(x1, y1, a, y2, x2, b) + areaSeg(r, std::sqrt((x2 - a)*(x2 - a) + (y2 - b)*(y2 - b)));
					}

					if(r*r >= x2*x2 + y1*y1){
						double b = std::sqrt(r*r - x2*x2), a = std::sqrt(r*r - x1*x1);
						return areaT(x1, y1, x2, b, x1, y2) + areaT(x1, y1, x2, b, x1, a) + areaSeg(r, std::sqrt((x1 -x2)*(x1 -x2) + (a - b)*(a - b)));
					}

					if(r*r >= x1*x1 + y2*y2){
						double a = std::sqrt(r*r - y2*y2), b = std::sqrt(r*r - y1*y1);
						return areaT(x1, y1, x1, y2, a, y2) + areaT(x1, y1, a, y2, b, y1) + areaSeg(r, std::sqrt((y1 - y2)*(y1 - y2) + (a - b)*(a - b)));
					}
				}
			}
		}
	}
	else{
		if(x1*x2 >= 0 || y1*y2 >= 0){
			if(y1*y2 >= 0){
				std::swap(x1, y1);
				std::swap(x2, y2);
			}
			x1 = std::abs(x1);
			x2 = std::abs(x2);
			if(std::abs(y1) > std::abs(y2)){
				swap(y1, y2);
			}
			if(x1 > x2){
				swap(x1, x2);
			}

			if(x1 >= r){
				return 0.0;
			}

			if(r*r >= x2*x2 + y2*y2){
				return (x2 - x1)*abs(y2 - y1);
			}

			return areaC(r, x1, x2, 0.0, std::abs(y1)) + areaC(r, x1, x2, 0.0, std::abs(y2));
		}

		return areaC(r, 0.0, std::abs(x1), 0.0, std::abs(y1)) + areaC(r, 0.0, std::abs(x1), 0.0, std::abs(y2)) + areaC(r, 0.0, std::abs(x2), 0.0, std::abs(y1)) + areaC(r, 0.0, std::abs(x1), 0.0, std::abs(y2));
	}
	return 0.0;
}

double f1(double x, double y, double r, double a1, double b1, double c1, double a2, double b2, double c2, double a3, double b3, double c3, double a4, double b4, double c4){
	double dx1, dx2, dy1, dy2;
	dx1 = (a1*x + b1*y - c1)/(std::sqrt(a1*a1 + b1*b1));
	dx2 = (a3*x + b3*y - c3)/(std::sqrt(a3*a3 + b3*b3));
	dy1 = (a2*x + b2*y - c2)/(std::sqrt(a2*a2 + b2*b2));
	dy2 = (a4*x + b4*y - c4)/(std::sqrt(a4*a4 + b4*b4));
	return areaC(r, dx1, dx2, dy1, dy2);
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	// take input in the form of
	// For circle
	// x , y, r 

	// For lines :: ax + by = c
	// a1, b1, c1, c2, c3, c4
	// a and b are same for parallel lines ans we can find them for the other sides of the rectangle
	// make sure they are in order i.e. adjacent sides
	double x, y, r, a1, b1, c1, a2, b2, c2, a3, b3, c3, a4, b4, c4;
	// f1 can be further optimised if rectangle is alingled to the axis
	double ans = f1(x, y, r, a1, b1, c1, a2, b2, c2, a3, b3, c3, a4, b4, c4);
	return 0;
}