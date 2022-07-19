//
// Created by ikmokhirio on 16.07.2022.
//

#ifndef DAEDALUS_UTILS_H
#define DAEDALUS_UTILS_H

#include <functional>
#include "Easing/Easing.h"

class Animation {
public:

    Animation(float &value, float start, float end, easing_functions easing, float speed = 1.0f);

    void Restart();

    // Return isFinished
    bool Play();

    void Reverse();

private:

    float startValue;
    float endValue;

    easingFunction func;
    float animationSpeed;
    float animTime;

    bool reversed;

    float &animationValue;
};

#endif //DAEDALUS_UTILS_H
