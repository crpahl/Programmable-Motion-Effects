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

#include "Vector.h"
//#include <iostream>



/*ostream& operator<<(ostream& out, const Vector& p) {
    out << '[' << p.x() << ", " << p.y() << ", " << p.z() << ']';
    return out;
}*/

Vector Vector::normal() const {
    Vector v1(*this);
    v1.normalize();
    return v1;
}






