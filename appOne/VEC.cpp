#include"libOne.h"
#include"VEC.h"
float magnitude(const struct VEC& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}
struct VEC normalize(const struct VEC& v) {
    float mag = magnitude(v);
    struct VEC tmp;
    if (mag > 0) {
        tmp.x = v.x / mag;
        tmp.y = v.y / mag;
    }
    return tmp;
}
struct VEC vecFromAngle(float angle) {
    struct VEC tmp;
    tmp.x = sin(angle);
    tmp.y = -cos(angle);
    return tmp;
}
struct VEC vecPosToPos(const struct VEC& sp, const struct VEC& ep) {
    struct VEC tmp;
    tmp.x = ep.x - sp.x;
    tmp.y = ep.y - sp.y;
    return tmp;
}
struct VEC vecFromWASDkey() {
    struct VEC tmp;
    if (isPress(KEY_A))tmp.x = -1;
    if (isPress(KEY_D))tmp.x = 1;
    if (isPress(KEY_W))tmp.y = -1;
    if (isPress(KEY_S))tmp.y = 1;
    return tmp;
}
float angleBetween2vec(const struct VEC& a, const struct VEC& b) {
    float dotProduct = a.x * b.x + a.y * b.y;
    float crossProduct = a.x * b.y - a.y * b.x;
    return atan2(crossProduct, dotProduct);
}
