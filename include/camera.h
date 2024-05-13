#ifndef CAMERA_H
#define CAMERA_H

#include <object.h>
#include <string>


class camera : public object
{
    public:
        camera();
        std::string to_string() override;

    protected:

    private:
};

#endif // CAMERA_H
