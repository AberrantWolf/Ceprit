//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_DEFINES_H
#define CEPRIT_DEFINES_H

#define _USE_MATH_DEFINES

//#define real double
//#define REAL_MAX DBL_MAX
#define real float
#define REAL_MAX FLT_MAX

#define RAND() (std::rand() / (RAND_MAX))

#endif //CEPRIT_DEFINES_H
