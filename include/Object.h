// object.h
#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"
#include "Ray.h"
#include "Transform.h"
#include "colorRGB.h"
#include "CollisionResult.h"
#include "Material.h"
#include <vector>

class Object {

    public:
        Object();
        virtual ~Object();
        virtual std::string to_string();
        virtual CollisionResult cast(Ray ray);
        Transform transform;
        Material material;

    protected:

    private:
};

#endif // OBJECT_H
