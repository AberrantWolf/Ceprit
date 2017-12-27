//
//  BVHNode.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef BVHNode_h
#define BVHNode_h

#include <stdlib.h>
#include <cstdlib>
#include <Hitable/Hitable.h>
#include "AABB.h"

int box_x_compare(const void* a, const void* b) {
    AABB box_left, box_right;
    Hitable* ah = *(Hitable**)a;
    Hitable* bh = *(Hitable**)b;
    
    if(!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right)) {
        std::cerr << "no bounding box in BVHNode constructor x comparator\n";// << std::endl;
    }
    
    if (box_left.min().x() - box_right.min().x() < 0.0) {
        return -1;
    }
    
    return 1;
}

int box_y_compare(const void* a, const void* b) {
    AABB box_left, box_right;
    Hitable* ah = *(Hitable**)a;
    Hitable* bh = *(Hitable**)b;
    
    if(!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right)) {
        std::cerr << "no bounding box in BVHNode constructor x comparator" << std::endl;
    }
    
    if (box_left.min().y() - box_right.min().y() < 0.0) {
        return -1;
    }
    
    return 1;
}

int box_z_compare(const void* a, const void* b) {
    AABB box_left, box_right;
    Hitable* ah = *(Hitable**)a;
    Hitable* bh = *(Hitable**)b;
    
    if(!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right)) {
        std::cerr << "no bounding box in BVHNode constructor x comparator" << std::endl;
    }
    
    if (box_left.min().z() - box_right.min().z() < 0.0) {
        return -1;
    }
    
    return 1;
}

class BVHNode : public Hitable {
public:
    BVHNode() {}
    BVHNode(Hitable** l, int n, real time0, real time1);
    
    virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const;
    virtual bool bounding_box(real t0, real t1, AABB& b) const;
    
    // children
    Hitable* left;
    Hitable* right;
    
    // Bounding box
    AABB box;
};

BVHNode::BVHNode(Hitable** l, int n, real time0, real time1) {
    int axis = int(3 * RAND());
    
    if (axis == 0) {
        std::qsort(l, n, sizeof(Hitable*), box_x_compare);
    } else if (axis == 1) {
        std::qsort(l, n, sizeof(Hitable*), box_y_compare);
    } else {
        std::qsort(l, n, sizeof(Hitable*), box_z_compare);
    }
    
    if (n==1) {
        left = right = l[0];
    } else if (n==2) {
        left = l[0];
        right = l[1];
    } else {
        left = new BVHNode(l, n/2, time0, time1);
        right = new BVHNode(l + n/2, n-n/2, time0, time1);
    }
    
    AABB box_left, box_right;
    if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right)) {
        std::cerr << "no bounding box in BVHNode constructor" << std::endl;
    }
    
    box = surrounding_box(box_left, box_right);
}

bool BVHNode::hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const {
    if (box.hit(r, t_min, t_max)) {
        HitRecord left_rec, right_rec;
        bool hit_left = left->hit(r, t_min, t_max, left_rec);
        bool hit_right = right->hit(r, t_min, t_max, right_rec);
        
        if (hit_left && hit_right) {
            if (left_rec.t < right_rec.t) {
                rec = left_rec;
            } else {
                rec = right_rec;
            }
            return true;
        } else if (hit_left) {
            rec = left_rec;
            return true;
        } else if (hit_right) {
            rec = right_rec;
            return true;
        }
    }
    
    return false;
}

bool BVHNode::bounding_box(real t0, real t1, AABB& b) const {
    b = box;
    return true;
}

#endif /* BVHNode_h */
