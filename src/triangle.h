#ifndef TRIANGLEH
#define TRIANGLEH

#include "hitable.h"

class triangle : public hitable {
    public: 
    triangle(vec3 _v0, vec3 _v1, vec3 _v2, vec3 _vn, material *m) : v0(_v0), v1(_v1), v2(_v2), vnorm(_vn), mat_ptr(m) {}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    vec3 v0;
    vec3 v1;
    vec3 v2;
    vec3 vnorm;
    material *mat_ptr;

};

bool triangle::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    //Möller–Trumbore intersection algorithm
    vec3 e1, e2, h, s, q;
    float a, f, u, v;
    float epsilon = 0.0000001;

    e1 = v1 - v0;
    e2 = v2 - v0;

    h = cross(r.direction(), e2);
    a = dot(e1, h);

    if (a > -epsilon && a < epsilon) return false;

    f = 1.0 / a;
    s = r.origin() - v0;
    u = f*dot(s, h);

    if (u < 0.0 || u > 1.0) return false;

    q = cross(s, e1);
    v = f*dot(r.direction(), q);

    if (v < 0.0 || u+v > 1.0) return false;

    float temp = f * dot(e2, q);
    if (temp < t_max && temp > t_min)
    {
        rec.t = temp;
        rec.p = r.point_at_parameter(rec.t);
        rec.normal = vnorm;
        rec.mat_ptr = mat_ptr;
        return true;
    }
    return false;
}
#endif