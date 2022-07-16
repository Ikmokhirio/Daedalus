//
// Created by ikmokhirio on 16.07.2022.
//

#include <cmath>
#include <Logger.h>
#include "Utils.h"
#include "imgui.h"

float animTime = 0.0f;
bool clearNextFrame = true;

void UpdateTime() {
    if (clearNextFrame) {
        animTime = 0;
        clearNextFrame = false;
        return;
    }

    animTime += ImGui::GetIO().DeltaTime;

    if (animTime >= 1.0f) {
        clearNextFrame = true;
        animTime = 1.0f;
    }
}

void AnimateStep(float &value, float start, float end, easing_functions easing, float speed) {
    auto easingFunction = getEasingFunction(easing);

    // easingFunction(animTime) = t
    value = (float) (start + easingFunction(animTime * speed) * (end - start));
}