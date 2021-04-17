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
    //�摜���[�h
    int backImg = loadImage("assets\\green.png");
    int osuImg = loadImage("assets\\osu.png");
    int mesuImg = loadImage("assets\\mesu.png");
    //�I�X�f�[�^
    struct BEETLE osu;
    osu.pos.x = width / 4;
    osu.pos.y = height / 2;
    osu.advSpeed = 10;
    float adjustSpeed = 0.25;
    //���X�f�[�^
    struct BEETLE mesu;
    mesu.pos.x = width / 2;
    mesu.pos.y = height / 2 - 150;
    mesu.advSpeed = 10;
    float advAngle = 0;
    //�����������ɕK�v�ȃf�[�^
    float nearDist = 400;
    int numRotation = 30;
    int rotationCnt = 0;
    //���
    const int WALKING = 0, ROTATING = 1;
    int state = WALKING;
    //�J�[�\����\��
    ShowCursor(FALSE);
    //���C�����[�v
    while (notQuit){
        if (state == WALKING) {
            //�����������Ă���x�N�g�����i�I�X���X���L�j
            struct VEC a;
            //���ꂩ����������x�N�g�����i�I�X���X���L�j
            struct VEC b;
            //�I�X���������-------------------------------------------
            //���ꂩ��i�ޕ����x�N�g��b
            b = vecFromWASDkey();
            if ((b.x != 0 || b.y != 0)) {
                //�ړ�
                b = normalize(b);
                osu.pos.x += b.x * osu.advSpeed;
                osu.pos.y += b.y * osu.advSpeed;
                //���݌����Ă�������x�N�g��a
                a = vecFromAngle(osu.angle);
                //�Ȃ��p�ɒ����l���|���ĉ�]�X�s�[�h�Ƃ���
                osu.angSpeed = angleBetween2vec(a, b) * adjustSpeed;
                //��]
                osu.angle += osu.angSpeed;
            }
            //���X���������-------------------------------------------
            //���ꂩ��i�ޕ����x�N�g��b
            b.x = cos(advAngle);
            b.y = sin(advAngle)*0.3f;
            advAngle += 0.02f;
            //�ړ�
            mesu.pos.x += b.x * mesu.advSpeed;
            mesu.pos.y += b.y * mesu.advSpeed;
            //���݌����Ă�������x�N�g��a
            a = vecFromAngle(mesu.angle);
            //�Ȃ��p�ɒ����l���|���ĉ�]�X�s�[�h�Ƃ���
            mesu.angSpeed = angleBetween2vec(a, b) * adjustSpeed;
            //��]
            mesu.angle += mesu.angSpeed;
            //���������O�̌v�Z--------------------------------------------
            if(isTrigger(KEY_SPACE)) {
                //�I�X--------------------------------------------
                //�I�X���烁�X�ւ̕����x�N�g��b
                b = vecPosToPos(osu.pos, mesu.pos);
                //�I�X�ƃ��X�̋�����nearDist���߂�
                if (magnitude(b) < nearDist) {
                    //�I�X�̌����Ă�������x�N�g��a
                    a = vecFromAngle(osu.angle);
                    //�P��̃��[�v�ŉ�]����p�x�����߂�
                    osu.angSpeed = angleBetween2vec(a, b) / numRotation;

                    //���X--------------------------------------------
                    //�}�C�i�X�ɂ���ƃ��X����I�X�ւ̃x�N�g���ɂȂ�
                    b.x = -b.x;
                    b.y = -b.y;
                    //���X�̌����Ă�������x�N�g��a
                    a = vecFromAngle(mesu.angle);
                    //�P��̃��[�v�ŉ�]����p�x�����߂�
                    mesu.angSpeed = angleBetween2vec(a, b) / numRotation;
                    
                    //���̃X�e�[�g��-----------------------------------
                    state = ROTATING;
                    rotationCnt = 0;
                }
            }
        }
        else if (state == ROTATING) {
            //�������킹��------------------------------------------
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
        //�w�i�`��
        rectMode(CORNER);
        image(backImg, 0, 0);
        //���X�ƌ���������̈�~�`��
        strokeWeight(0);
        fill(255, 255, 255, 128);
        circle(mesu.pos.x, mesu.pos.y, nearDist * 2);
        //�J�u�g���V�`��
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
