//created by Shaun David Ramsey and Kristin Potter (c) 20003
//email ramsey()cs.utah.edu with questions/comments
/*
The ray bilinear patch intersection software are "Open Source"
according to the MIT License located at:
        http://www.opensource.org/licenses/mit-license.php

Copyright (c) 2003 Shaun David Ramsey, Kristin Potter, Charles Hansen

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sel copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef VECTOR_H
#define VECTOR_H 1

#include <math.h>
//class ostream;
//class istream;

class Vector {
    double d[3];

public:

    inline Vector (double x, double y, double z=0);
    inline Vector(const Vector& v);
    inline Vector();
    inline double length() const;
    inline double length2() const;
    inline Vector& operator=(const Vector& v);
    inline bool operator==(const Vector& v) const;
    inline Vector operator*(double s) const;
    inline Vector operator*(const Vector& v) const;
    inline Vector operator/(const Vector& v) const;
    inline Vector& operator*=(double s);
    Vector operator/(double s) const;
    inline Vector operator+(const Vector& v) const;
    inline Vector& operator+=(const Vector& v);
    inline Vector operator-() const;
    inline Vector operator-(const Vector& v) const;
    Vector& operator-=(const Vector& v);
    inline double normalize();
    Vector normal() const;
    inline Vector cross(const Vector& v) const;
    inline double dot(const Vector& v) const;
    inline void x(double xx) {	d[0]=xx;    }
    inline double x() const;
    inline void y(double yy) {	d[1]=yy;    }
    inline double y() const;
    inline void z(double zz) {	d[2]=zz;    }
    inline double z() const;
    inline double minComponent() const;
    //friend ostream& operator<<(ostream& os, const Vector& p);
    //friend istream& operator>>(istream& os, Vector& p);
    inline bool operator != (const Vector& v) const;
    inline double* ptr() const {return (double*)&d[0];}

    void make_ortho(Vector&v1, Vector&v2)
      {
	Vector v0(this->cross(Vector(1,0,0)));
	if(v0.length2() == 0){
	  v0=this->cross(this->cross(Vector(0,1,0)));
	}
	v1=this->cross(v0);
	v1.normalize();
	v2=this->cross(v1);
	v2.normalize();
      }
     
};


inline Vector::Vector(double x, double y, double z) {
    d[0]=x;
    d[1]=y;
    d[2]=z;
}

inline Vector::Vector(const Vector& v) {
    d[0]=v.d[0];
    d[1]=v.d[1];
    d[2]=v.d[2];
}

inline Vector::Vector() {
}


inline double Vector::length() const {
    return sqrt(length2());
}

inline double Vector::length2() const {
    return d[0]*d[0]+d[1]*d[1]+d[2]*d[2];
}

inline Vector& Vector::operator=(const Vector& v) {
    d[0]=v.d[0];
    d[1]=v.d[1];
    d[2]=v.d[2];
    return *this;
    //return this;
}



inline Vector Vector::operator*(double s) const {
    return Vector(d[0]*s, d[1]*s, d[2]*s);
}

inline Vector operator*(double s, const Vector& v) {
    return v*s;
}

inline Vector Vector::operator*(const Vector& v) const {
    return Vector(d[0]*v.d[0], d[1]*v.d[1], d[2]*v.d[2]);
}

inline Vector Vector::operator/(const Vector& v) const {
    return Vector(d[0]/v.d[0], d[1]/v.d[1], d[2]/v.d[2]);
}

inline Vector Vector::operator+(const Vector& v) const {
    return Vector(d[0]+v.d[0], d[1]+v.d[1], d[2]+v.d[2]);
}

inline Vector& Vector::operator+=(const Vector& v) {
    d[0]+=v.d[0];
    d[1]+=v.d[1];
    d[2]+=v.d[2];
    return *this;
}

inline Vector& Vector::operator*=(double s) {
    d[0]*=s;
    d[1]*=s;
    d[2]*=s;
    return *this;
}

inline Vector Vector::operator-() const {
    return Vector(-d[0], -d[1], -d[2]);
}

inline Vector Vector::operator-(const Vector& v) const {
    return Vector(d[0]-v.d[0], d[1]-v.d[1], d[2]-v.d[2]);
}


inline double Vector::normalize() {
    double l=length();
    if(l != 0)
      {
      d[0]/=l;
      d[1]/=l;
      d[2]/=l;
      }
    return l;
}

inline Vector Vector::cross(const Vector& v) const {
    return Vector(d[1]*v.d[2]-d[2]*v.d[1],
    	      d[2]*v.d[0]-d[0]*v.d[2],
    	      d[0]*v.d[1]-d[1]*v.d[0]);
}

inline double Vector::dot(const Vector& v) const {
    return d[0]*v.d[0]+d[1]*v.d[1]+d[2]*v.d[2];
}


inline double Vector::x() const {
    return d[0];
}

inline double Vector::y() const {
    return d[1];
}

inline double Vector::z() const {
    return d[2];
}

inline double Vector::minComponent() const {
    return (d[0]<d[1] && d[0]<d[2])?d[0]:d[1]<d[2]?d[1]:d[2];
}

inline bool Vector::operator != (const Vector& v) const {
    return d[0] != v.d[0] || d[1] != v.d[1] || d[2] != v.d[2];
}

inline bool Vector::operator == (const Vector& v) const {
   return d[0] == v.d[0] && d[1] == v.d[1] && d[2] == v.d[2];
}



#endif
