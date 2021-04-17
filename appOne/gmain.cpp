#include"libOne.h"
#include"VEC.h"

struct BEETLE {
    struct VEC pos;
    float advSpeed = 0;
    float angle = 0;
    float angSpeed = 0;
};

void gmain(){
    window(1920, 1080, full);
    //画像ロード
    int backImg = loadImage("assets\\green.png");
    int osuImg = loadImage("assets\\osu.png");
    int mesuImg = loadImage("assets\\mesu.png");
    //オスデータ
    struct BEETLE osu;
    osu.pos.x = width / 4;
    osu.pos.y = height / 2;
    osu.advSpeed = 10;
    float adjustSpeed = 0.25;
    //メスデータ
    struct BEETLE mesu;
    mesu.pos.x = width / 2;
    mesu.pos.y = height / 2 - 150;
    mesu.advSpeed = 10;
    float advAngle = 0;
    //向かい合いに必要なデータ
    float nearDist = 400;
    int numRotation = 30;
    int rotationCnt = 0;
    //状態
    const int WALKING = 0, ROTATING = 1;
    int state = WALKING;
    //カーソル非表示
    ShowCursor(FALSE);
    //メインループ
    while (notQuit){
        if (state == WALKING) {
            //自分が向いているベクトルａ（オスメス共有）
            struct VEC a;
            //これから向く方向ベクトルｂ（オスメス共有）
            struct VEC b;
            //オスを歩かせる-------------------------------------------
            //これから進む方向ベクトルb
            b = vecFromWASDkey();
            if ((b.x != 0 || b.y != 0)) {
                //移動
                b = normalize(b);
                osu.pos.x += b.x * osu.advSpeed;
                osu.pos.y += b.y * osu.advSpeed;
                //現在向いている方向ベクトルa
                a = vecFromAngle(osu.angle);
                //なす角に調整値を掛けて回転スピードとする
                osu.angSpeed = angleBetween2vec(a, b) * adjustSpeed;
                //回転
                osu.angle += osu.angSpeed;
            }
            //メスを歩かせる-------------------------------------------
            //これから進む方向ベクトルb
            b.x = cos(advAngle);
            b.y = sin(advAngle)*0.3f;
            advAngle += 0.02f;
            //移動
            mesu.pos.x += b.x * mesu.advSpeed;
            mesu.pos.y += b.y * mesu.advSpeed;
            //現在向いている方向ベクトルa
            a = vecFromAngle(mesu.angle);
            //なす角に調整値を掛けて回転スピードとする
            mesu.angSpeed = angleBetween2vec(a, b) * adjustSpeed;
            //回転
            mesu.angle += mesu.angSpeed;
            //向き合う前の計算--------------------------------------------
            if(isTrigger(KEY_SPACE)) {
                //オス--------------------------------------------
                //オスからメスへの方向ベクトルb
                b = vecPosToPos(osu.pos, mesu.pos);
                //オスとメスの距離がnearDistより近い
                if (magnitude(b) < nearDist) {
                    //オスの向いている方向ベクトルa
                    a = vecFromAngle(osu.angle);
                    //１回のループで回転する角度を求める
                    osu.angSpeed = angleBetween2vec(a, b) / numRotation;

                    //メス--------------------------------------------
                    //マイナスにするとメスからオスへのベクトルになる
                    b.x = -b.x;
                    b.y = -b.y;
                    //メスの向いている方向ベクトルa
                    a = vecFromAngle(mesu.angle);
                    //１回のループで回転する角度を求める
                    mesu.angSpeed = angleBetween2vec(a, b) / numRotation;
                    
                    //次のステートへ-----------------------------------
                    state = ROTATING;
                    rotationCnt = 0;
                }
            }
        }
        else if (state == ROTATING) {
            //向き合わせる------------------------------------------
            if (rotationCnt < numRotation) {
                osu.angle += osu.angSpeed;
                mesu.angle += mesu.angSpeed;
                rotationCnt++;
            }
            if (isTrigger(KEY_SPACE)) {
                state = WALKING;
            }
        }
        
        clear(200);
        //背景描画
        rectMode(CORNER);
        image(backImg, 0, 0);
        //メスと向き合える領域円描画
        strokeWeight(0);
        fill(255, 255, 255, 128);
        circle(mesu.pos.x, mesu.pos.y, nearDist * 2);
        //カブトムシ描画
        rectMode(CENTER);
        image(mesuImg, mesu.pos.x, mesu.pos.y, mesu.angle);
        image(osuImg, osu.pos.x, osu.pos.y, osu.angle);

        //for (float angle = 0; angle < 6.28f; angle += 0.01f) {
        //    float x = cos(angle) * 500 + width / 2;
        //    float y = sin(angle) * 0.3f * 500 + height / 2;
        //    strokeWeight(20);
        //    point(x, y);
        //}
    }
    ShowCursor(TRUE);
}
