#ifndef PLANE_H
#define PLANE_H
#include "Object.h"


class Plane : public Object
{
    public:
        Plane();
        Plane(Vector3 scale);
        Plane(Vector3 scale, Vector3 position);
        Plane(Vector3 scale, Vector3 position, Vector3 rotation);
        std::string to_string() override;
        CollisionResult cast(Ray ray) override;
        double contains (Vector3 point);
        double getD();
        double k_d;
        double k_s;
        double k_a;
        double k_r;
        double k_t;
        double n;

    protected:

    private:
};

#endif // PLANE_H
