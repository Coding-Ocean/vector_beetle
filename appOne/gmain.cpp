#include"libOne.h"
#include"VEC.h"
//�J�u�g���V�\����
struct BEETLE {
    struct VEC pos;
    float advSpeed = 0;
    float angle = 0;
    float angSpeed = 0;
};
//���C��
void gmain() {
    window(1920, 1080, full);
    //�摜�ǂݍ���
    int osuImg = loadImage("assets\\osu.png");
    int mesuImg = loadImage("assets\\mesu.png");
    int backImg = loadImage("assets\\green.png");
    //�I�X�f�[�^
    struct BEETLE osu;
    osu.pos.x = width / 2 + 500;
    osu.pos.y = height / 2;
    osu.advSpeed = 10;
    //���X�f�[�^
    struct BEETLE mesu;
    mesu.pos.x = width / 2 - 500;
    mesu.pos.y = height / 2;
    mesu.advSpeed = 10;
    float advAngle = 0;
    //�ړ����̉�]���x�����l
    float adjustAngSpeed = 4.0f;
    //���
    const int WALK = 0;
    const int ROTATE = 1;
    int state = WALK;
    //���̋������߂Â��Ă������������
    float nearDist = 350;
    //���̉񐔃��[�v����ƌ�������
    int numRotation = 30;
    int rotateCnt = 0;
    //�߂����[����
    while (notQuit) {
        if (state == WALK) {
            //���������݌����Ă���x�N�g����
            struct VEC a;
            //���ꂩ��i�ށA�����͌����x�N�g����
            struct VEC b;
            //�I�X�̐i�ޕ���
            if (isPress(KEY_D))b.x = 1;
            if (isPress(KEY_A))b.x = -1;
            if (isPress(KEY_W))b.y = -1;
            if (isPress(KEY_S))b.y = 1;
            if (b.x != 0 || b.y != 0) {
                //�I�X�̈ړ�
                b = normalize(&b);
                osu.pos.x += b.x * osu.advSpeed;
                osu.pos.y += b.y * osu.advSpeed;
                //�I�X�̉�]�i�i��ł�������֓���������j
                a = vecFromAngle(osu.angle);
                osu.angSpeed = angleBetweenTwoVecs(&a, &b) / adjustAngSpeed;
                osu.angle += osu.angSpeed;
            }
            //���X�̐i�ޕ���
            b.x = sin(advAngle);
            b.y = -cos(advAngle) * 0.3f;
            advAngle += 0.02f;
            //���X�̈ړ�
            mesu.pos.x += b.x * mesu.advSpeed;
            mesu.pos.y += b.y * mesu.advSpeed;
            //���X�̉�]�i�i��ł�������֓���������j
            a = vecFromAngle(mesu.angle);
            mesu.angSpeed = angleBetweenTwoVecs(&a, &b) / adjustAngSpeed;
            mesu.angle += mesu.angSpeed;
            //�����������O�̌v�Z
            //�P��̃��[�v�ŉ�]����p���xangSpeed�����߂�
            if (isTrigger(KEY_SPACE)) {
                //�I�X�̊p���x
                b.x = mesu.pos.x - osu.pos.x;
                b.y = mesu.pos.y - osu.pos.y;
                if (magnitude(&b) < nearDist) {
                    a = vecFromAngle(osu.angle);
                    osu.angSpeed = angleBetweenTwoVecs(&a, &b) / numRotation;
                    //���X�̊p���x
                    b.x = -b.x;
                    b.y = -b.y;
                    a = vecFromAngle(mesu.angle);
                    mesu.angSpeed = angleBetweenTwoVecs(&a, &b) / numRotation;
                    //��Ԑ؂�ւ�
                    rotateCnt = 0;
                    state = ROTATE;
                }
            }
        }
        else if (state == ROTATE) {
            if (rotateCnt < numRotation) {
                //��������
                osu.angle += osu.angSpeed;
                mesu.angle += mesu.angSpeed;
                rotateCnt++;
            }
            else {
                //�I�X�𓮂����ƁAWALK��Ԃɖ߂�
                if (isTrigger(KEY_W) || isTrigger(KEY_A) ||
                    isTrigger(KEY_S) || isTrigger(KEY_D) ){
                    state = WALK;
                }
            }
        }
        //�`��
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