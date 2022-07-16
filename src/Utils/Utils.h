//
// Created by ikmokhirio on 16.07.2022.
//

#ifndef DAEDALUS_UTILS_H
#define DAEDALUS_UTILS_H

#include "Easing/Easing.h"

extern float animTime;
extern bool clearNextFrame;

void UpdateTime();

void AnimateStep(float &value, float start, float end, easing_functions easing, float speed = 1.0f);

#endif //DAEDALUS_UTILS_H
