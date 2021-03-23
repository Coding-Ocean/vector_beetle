#include"libOne.h"
struct VEC {
    float x=0, y=0;
};
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
float angleBetween2vec(const struct VEC& a, const struct VEC& b) {
    //引数のベクトルa,bは正規化されてなければいけない
    float cosAngle = a.x * b.x + a.y * b.y;
    if (cosAngle > 1.0f) { cosAngle = 1.0f; }
    else if (cosAngle < -1.0f) { cosAngle = -1.0f; }
    float angle = acos(cosAngle);
    if (a.x * b.y - a.y * b.x < 0) {
        angle = -angle;
    }
    return angle;
}

struct DATA {
    struct VEC pos;
    float angle = 0;
    float advSpeed = 0;
    float angSpeed = 0;
};


void gmain(){
    window(1920, 1080, full);
    int backImg = loadImage("assets\\green.png");
    int osuImg = loadImage("assets\\osu.png");
    int mesuImg = loadImage("assets\\mesu.png");

    struct DATA osu, mesu;
    osu.pos.x = width / 4;
    osu.pos.y = height / 4;
    osu.advSpeed = 10;
    float adjustSpeed = 0.25;
    mesu.pos.x = width / 2;
    mesu.pos.y = height / 2;
    float dist = 0;
    float nearDist = 400;
    int numRepitision = 30;
    int cnt = 0;
    int state, walk = 0, rot = 1;
    state = walk;
    //左上のベクトル表示用
    struct VEC a_, b_;
    while (notQuit){
        if (state == walk) {
            struct VEC a, b;
            //オスを歩かせる-------------------------------------------
            //これから進む方向ベクトルb
            b.x = 0;
            b.y = 0;
            if (isPress(KEY_A))b.x = -1;
            if (isPress(KEY_D))b.x = 1;
            if (isPress(KEY_W))b.y = -1;
            if (isPress(KEY_S))b.y = 1;
            if ((b.x != 0 || b.y != 0)) {
                b = normalize(b);
                //移動
                osu.pos.x += b.x * osu.advSpeed;
                osu.pos.y += b.y * osu.advSpeed;
                b_ = b;//表示用ベクトルにコピー
                //現在向いている方向ベクトルa
                a = vecFromAngle(osu.angle);
                osu.angSpeed = angleBetween2vec(a, b) * adjustSpeed;
                //回転
                osu.angle += osu.angSpeed;
            }
            //回転前準備計算--------------------------------------------
            if(isTrigger(KEY_SPACE)) {
                //オス--------------------------------------------
                //オスからメスへの方向ベクトルb
                b = vecPosToPos(osu.pos, mesu.pos);
                dist = magnitude(b);
                if (dist < nearDist) {
                    b = normalize(b);
                    //オスの向いている方向ベクトルa
                    a = vecFromAngle(osu.angle);
                    osu.angSpeed = angleBetween2vec(a, b) / numRepitision;
                    b_ = b;//表示用ベクトルにコピー

                    //メス--------------------------------------------
                    //マイナスにするとメスからオスへのベクトルになる
                    b.x = -b.x;
                    b.y = -b.y;
                    //メスの向いている方向ベクトルa
                    a = vecFromAngle(mesu.angle);
                    mesu.angSpeed = angleBetween2vec(a, b) / numRepitision;
                    
                    //次のステートへ-----------------------------------
                    state = rot;
                    cnt = 0;
                }
            }
        }
        else if (state == rot) {
            //向き合う
            osu.angle += osu.angSpeed;
            mesu.angle += mesu.angSpeed;
            cnt++;
            if (cnt >= numRepitision) {
                state = walk;
            }
        }
        
        clear(200);
        rectMode(CORNER);
        image(backImg, 0, 0);
        rectMode(CENTER);
        strokeWeight(0);
        fill(255, 255, 255, 128);
        circle(mesu.pos.x, mesu.pos.y, nearDist*2);
        image(mesuImg, mesu.pos.x, mesu.pos.y, mesu.angle);
        image(osuImg, osu.pos.x, osu.pos.y, osu.angle);
        
        
        float ox = 100, oy = 100, armag = 90;
        circle(ox, oy, 200);
        strokeWeight(5);
        stroke(0,0,0);
        a_ = vecFromAngle(osu.angle);
        arrow(ox, oy, ox+a_.x*armag, oy+a_.y*armag);
        stroke(255, 0, 0);
        if ((b_.x != 0 || b_.y != 0)) {
            arrow(ox, oy, ox + b_.x * armag, oy + b_.y * armag);
        }
        
    }
}
