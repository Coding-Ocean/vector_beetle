#pragma once
struct VEC {
    float x = 0;
    float y = 0;
};

float magnitude(struct VEC* v);
struct VEC normalize(struct VEC* v);
struct VEC vecFromAngle(float angle);
float angleBetweenTwoVecs(struct VEC* a, struct VEC* b);