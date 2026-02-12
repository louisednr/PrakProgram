#include<iostream>
#include<vector>
#include<random>
#include"vec.h"

int main(){

    std::mt19937 gen(0);
	std::uniform_real_distribution<double> dist(-1.0, 1.0);
	
	vec::vec u,v,test;
	u.set(dist(gen),dist(gen),dist(gen));
	v.set(dist(gen),dist(gen),dist(gen));
	u.print(" u= ");
	v.print(" v= ");
	std::cout << " u=" << u << std::endl;
	std::cout << " v=" << v << std::endl;

	test.set(-u.x,-u.y,-u.z);
	(-u).print("-u  = ");
	test.print("test= ");
	if(approx(-u,test))std::cout << "\ntest 'unary -' passed\n" << std::endl;

	test.set(u.x+v.x,u.y+v.y,u.z+v.z);
	(u+v).print(" u+v = ");
	test.print (" test= ");
	if(approx(u+v,test))std::cout << " test '+' passed\n" << std::endl;

	test.set(u.x-v.x,u.y-v.y,u.z-v.z);
	(u-v).print("u-v = ");
	test.print   ("test= ");
	if(approx(u-v,test))std::cout << " test '-' passed\n" << std::endl;



    double c=dist(gen);

	test.set(u.x*c,u.y*c,u.z*c);
	(u*c).print("u*c  = ");
    test.print (" test= ");
    if(vec::approx(u*c,test))std::cout << "\ntest '*' passed\n" << std::endl;
	
    double t = u.x*v.x + u.y*v.y + u.z*v.z;
	std::cout << "dot(u,v)=" << dot(u,v)<< std::endl;
    std::cout << " test= " << t << std::endl;
    if(vec::approx(dot(u,v),t))std::cout << "\ntest dot passed\n" << std::endl;


    std::cout << "Explanation for the difference between traditional and modern forms of operator+\n";
    std::cout << "Old input: (const vec& a, const vec& b) is different from the modern input: (vec a, const vec& b)\n";
    std::cout << "The old had to define a new vector 'r' manually: vec r = a;\n";
    std::cout << "This adds an extra line (higher chance for typos).\n";
    std::cout << " Instead, can simply edit the copy of the first vector. \n";


return 0;
}
