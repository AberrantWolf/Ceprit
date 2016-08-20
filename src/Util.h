//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_UTIL_H
#define CEPRIT_UTIL_H

#include <AABB.h>
#include <Hitable/Hitable.h>

Vec3 random_point_in_unit_sphere();
Vec3 random_point_in_unit_disk();

real schlick(real cosine, real ref_idx);
AABB surrounding_box(AABB box0, AABB box1);
Hitable* CornellBox();

#endif //CEPRIT_UTIL_H
