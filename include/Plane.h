#ifndef PLANE_H
#define PLANE_H
#include "Object.h"


class Plane : public Object
{
    public:
        Plane();
        Plane(Vector3 normal);
        Plane(Vector3 normal, Vector3 position);
        std::string to_string() override;
        CollisionResult cast(Ray ray) override;
        //double contains (Vector3 point);
        //double getD();

    protected:

    private:
        Vector3 normal;
        Vector3 right;
        Vector3 forward;
};

#endif // PLANE_H
