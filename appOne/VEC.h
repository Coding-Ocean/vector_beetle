#pragma once
struct VEC {
    float x = 0, y = 0;
};
float magnitude(const struct VEC& v);
struct VEC normalize(const struct VEC& v);
struct VEC vecFromWASDkey();
struct VEC vecFromAngle(float angle);
struct VEC vecPosToPos(const struct VEC& sp, const struct VEC& ep);
float angleBetween2vec(const struct VEC& a, const struct VEC& b);