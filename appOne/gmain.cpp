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
    //�����̃x�N�g��a,b�͐��K������ĂȂ���΂����Ȃ�
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
    //����̃x�N�g���\���p
    struct VEC a_, b_;
    while (notQuit){
        if (state == walk) {
            struct VEC a, b;
            //�I�X���������-------------------------------------------
            //���ꂩ��i�ޕ����x�N�g��b
            b.x = 0;
            b.y = 0;
            if (isPress(KEY_A))b.x = -1;
            if (isPress(KEY_D))b.x = 1;
            if (isPress(KEY_W))b.y = -1;
            if (isPress(KEY_S))b.y = 1;
            if ((b.x != 0 || b.y != 0)) {
                b = normalize(b);
                //�ړ�
                osu.pos.x += b.x * osu.advSpeed;
                osu.pos.y += b.y * osu.advSpeed;
                b_ = b;//�\���p�x�N�g���ɃR�s�[
                //���݌����Ă�������x�N�g��a
                a = vecFromAngle(osu.angle);
                osu.angSpeed = angleBetween2vec(a, b) * adjustSpeed;
                //��]
                osu.angle += osu.angSpeed;
            }
            //��]�O�����v�Z--------------------------------------------
            if(isTrigger(KEY_SPACE)) {
                //�I�X--------------------------------------------
                //�I�X���烁�X�ւ̕����x�N�g��b
                b = vecPosToPos(osu.pos, mesu.pos);
                dist = magnitude(b);
                if (dist < nearDist) {
                    b = normalize(b);
                    //�I�X�̌����Ă�������x�N�g��a
                    a = vecFromAngle(osu.angle);
                    osu.angSpeed = angleBetween2vec(a, b) / numRepitision;
                    b_ = b;//�\���p�x�N�g���ɃR�s�[

                    //���X--------------------------------------------
                    //�}�C�i�X�ɂ���ƃ��X����I�X�ւ̃x�N�g���ɂȂ�
                    b.x = -b.x;
                    b.y = -b.y;
                    //���X�̌����Ă�������x�N�g��a
                    a = vecFromAngle(mesu.angle);
                    mesu.angSpeed = angleBetween2vec(a, b) / numRepitision;
                    
                    //���̃X�e�[�g��-----------------------------------
                    state = rot;
                    cnt = 0;
                }
            }
        }
        else if (state == rot) {
            //��������
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
