#include"libOne.h"
#include"VEC.h"

struct BEETLE {
    struct VEC pos;
    float advSpeed = 0;
    float angle = 0;
    float angSpeed = 0;
};

void gmain() {
    window(1920, 1080, full);
    //画像読み込み
    int osuImg = loadImage("assets\\osu.png");
    //オスデータ
    struct BEETLE osu;
    osu.pos.x = width / 2;
    osu.pos.y = height / 2;
    osu.advSpeed = 10;
    //めいんるーっぷ
    while (notQuit) {
        struct VEC a,b;
        if (isPress(KEY_D))b.x = 1;
        if (isPress(KEY_A))b.x = -1;
        if (isPress(KEY_W))b.y = -1;
        if (isPress(KEY_S))b.y = 1;
        if (b.x != 0 || b.y != 0) {
            //オスの移動
            b = normalize(&b);
            osu.pos.x += b.x * osu.advSpeed;
            osu.pos.y += b.y * osu.advSpeed;
            //オスの回転
            a = vecFromAngle(osu.angle);
            osu.angSpeed = angleBetweenTwoVecs(&a, &b) / 4;
            osu.angle += osu.angSpeed;
        }
        clear();
        rectMode(CENTER);
        image(osuImg, osu.pos.x, osu.pos.y, osu.angle);
    }
}