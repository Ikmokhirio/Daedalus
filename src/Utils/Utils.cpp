//
// Created by ikmokhirio on 16.07.2022.
//

#include <cmath>
#include <Logger.h>
#include "Utils.h"
#include "imgui.h"

Animation::Animation(float &value, float start, float end, easing_functions easing, float speed)
        : animationValue(value) {

    startValue = start;
    endValue = end;

    func = getEasingFunction(easing);
    animationSpeed = speed;
    animTime = 0.0f;

    reversed = false;
}

void Animation::Restart() {
    animTime = 0.0f;
    reversed = false;
}

bool Animation::Play() {

    if (reversed) {
        animTime -= (ImGui::GetIO().DeltaTime * animationSpeed);
    } else {
        animTime += (ImGui::GetIO().DeltaTime * animationSpeed);
    }

    if (animTime >= 1.0f) {
        animTime = 1.0f;
    }
    if (animTime < 0.0f) {
        animTime = 0.0f;
    }

    animationValue = (float) (startValue +
                              func(animTime) * (endValue - startValue));

    return animTime >= 1.0f;
}

void Animation::Reverse() {
    reversed = !reversed;
}
