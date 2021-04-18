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
    int mesuImg = loadImage("assets\\mesu.png");
    int backImg = loadImage("assets\\green.png");
    //オスデータ
    struct BEETLE osu;
    osu.pos.x = width / 2 + 500;
    osu.pos.y = height / 2;
    osu.advSpeed = 10;
    //メスデータ
    struct BEETLE mesu;
    mesu.pos.x = width / 2 - 500;
    mesu.pos.y = height / 2;
    mesu.advSpeed = 10;
    float advAngle = 0;
    //状態
    const int WALK = 0;
    const int ROTATE = 1;
    int state = WALK;
    int rotateCnt = 0;
    //めいんるーっぷ
    while (notQuit) {
        if (state == WALK) {
            struct VEC a, b;
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
            //メスの動く方向
            b.x = sin(advAngle);
            b.y = -cos(advAngle) * 0.3f;
            advAngle += 0.02f;
            //メスの移動
            mesu.pos.x += b.x * mesu.advSpeed;
            mesu.pos.y += b.y * mesu.advSpeed;
            //メスの回転
            a = vecFromAngle(mesu.angle);
            mesu.angSpeed = angleBetweenTwoVecs(&a, &b) / 4;
            mesu.angle += mesu.angSpeed;

            if (isTrigger(KEY_SPACE)) {
                //オス
                b.x = mesu.pos.x - osu.pos.x;
                b.y = mesu.pos.y - osu.pos.y;
                if (magnitude(&b) < 300) {
                    a = vecFromAngle(osu.angle);
                    osu.angSpeed = angleBetweenTwoVecs(&a, &b) / 30;
                    //メス
                    b.x = -b.x;
                    b.y = -b.y;
                    a = vecFromAngle(mesu.angle);
                    mesu.angSpeed = angleBetweenTwoVecs(&a, &b) / 30;
                    //状態切り替え
                    rotateCnt = 0;
                    state = ROTATE;
                }
            }
        }
        else if (state == ROTATE) {
            if (rotateCnt < 30) {
                osu.angle += osu.angSpeed;
                mesu.angle += mesu.angSpeed;
                rotateCnt++;
            }
            else {
                if (isTrigger(KEY_W) ||
                    isTrigger(KEY_A) ||
                    isTrigger(KEY_S) ||
                    isTrigger(KEY_D) ){
                    state = WALK;
                }
            }
        }
        clear();
        rectMode(CORNER);
        image(backImg, 0, 0);
        noStroke();
        fill(255, 255, 255, 128);
        circle(mesu.pos.x, mesu.pos.y, 600);
        rectMode(CENTER);
        image(mesuImg, mesu.pos.x, mesu.pos.y, mesu.angle);
        image(osuImg, osu.pos.x, osu.pos.y, osu.angle);
    }
}