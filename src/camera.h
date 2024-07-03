#ifndef POTATO_BUCKET_CAMERA_H
#define POTATO_BUCKET_CAMERA_H

#include "raylib.h"

namespace potato_bucket {

class Camera {
private:
  Rectangle box; 

public:
  Camera(float, float, float, float);
};

}

#endif
