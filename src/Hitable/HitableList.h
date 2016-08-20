//
//  HitableList.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef HitableList_h
#define HitableList_h

#include "Hitable.h"

class HitableList : public Hitable {
public:
    HitableList() {}
    HitableList(Hitable** l, int n) {
        list = l;
        list_size = n;
    }
    
    virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const override;
    virtual bool bounding_box(real t0, real t1, AABB& box) const override;
    
    // TODO: Should be private with accessor funcs
    Hitable** list;
    int list_size;
};

#endif /* HitableList_h */
