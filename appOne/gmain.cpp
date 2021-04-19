#include"libOne.h"
#include"VEC.h"
//カブトムシ構造体
struct BEETLE {
    struct VEC pos;
    float advSpeed = 0;
    float angle = 0;
    float angSpeed = 0;
};
//メイン
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
    //移動中の回転速度調整値
    float adjustAngSpeed = 4.0f;
    //状態
    const int WALK = 0;
    const int ROTATE = 1;
    int state = WALK;
    //この距離より近づいていたら向き合う
    float nearDist = 350;
    //この回数ループすると向き合う
    int numRotation = 30;
    int rotateCnt = 0;
    //めいんるーっぷ
    while (notQuit) {
        if (state == WALK) {
            //自分が現在向いているベクトルａ
            struct VEC a;
            //これから進む、或いは向くベクトルｂ
            struct VEC b;
            //オスの進む方向
            if (isPress(KEY_D))b.x = 1;
            if (isPress(KEY_A))b.x = -1;
            if (isPress(KEY_W))b.y = -1;
            if (isPress(KEY_S))b.y = 1;
            if (b.x != 0 || b.y != 0) {
                //オスの移動
                b = normalize(&b);
                osu.pos.x += b.x * osu.advSpeed;
                osu.pos.y += b.y * osu.advSpeed;
                //オスの回転（進んでいる方向へ頭を向ける）
                a = vecFromAngle(osu.angle);
                osu.angSpeed = angleBetweenTwoVecs(&a, &b) / adjustAngSpeed;
                osu.angle += osu.angSpeed;
            }
            //メスの進む方向
            b.x = sin(advAngle);
            b.y = -cos(advAngle) * 0.3f;
            advAngle += 0.02f;
            //メスの移動
            mesu.pos.x += b.x * mesu.advSpeed;
            mesu.pos.y += b.y * mesu.advSpeed;
            //メスの回転（進んでいる方向へ頭を向ける）
            a = vecFromAngle(mesu.angle);
            mesu.angSpeed = angleBetweenTwoVecs(&a, &b) / adjustAngSpeed;
            mesu.angle += mesu.angSpeed;
            //向き合う直前の計算
            //１回のループで回転する角速度angSpeedを求める
            if (isTrigger(KEY_SPACE)) {
                //オスの角速度
                b.x = mesu.pos.x - osu.pos.x;
                b.y = mesu.pos.y - osu.pos.y;
                if (magnitude(&b) < nearDist) {
                    a = vecFromAngle(osu.angle);
                    osu.angSpeed = angleBetweenTwoVecs(&a, &b) / numRotation;
                    //メスの角速度
                    b.x = -b.x;
                    b.y = -b.y;
                    a = vecFromAngle(mesu.angle);
                    mesu.angSpeed = angleBetweenTwoVecs(&a, &b) / numRotation;
                    //状態切り替え
                    rotateCnt = 0;
                    state = ROTATE;
                }
            }
        }
        else if (state == ROTATE) {
            if (rotateCnt < numRotation) {
                //向き合う
                osu.angle += osu.angSpeed;
                mesu.angle += mesu.angSpeed;
                rotateCnt++;
            }
            else {
                //オスを動かすと、WALK状態に戻る
                if (isTrigger(KEY_W) || isTrigger(KEY_A) ||
                    isTrigger(KEY_S) || isTrigger(KEY_D) ){
                    state = WALK;
                }
            }
        }
        //描画
        clear();
        rectMode(CORNER);
        image(backImg, 0, 0);
        noStroke();
        fill(255, 255, 255, 128);
        circle(mesu.pos.x, mesu.pos.y, nearDist*2);
        rectMode(CENTER);
        image(mesuImg, mesu.pos.x, mesu.pos.y, mesu.angle);
        image(osuImg, osu.pos.x, osu.pos.y, osu.angle);
    }
}