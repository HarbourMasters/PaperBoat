#include <libultraship/libultra/gu.h>
#include <math.h>

static void guIdentityF(float mf[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mf[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void guTranslateF(float mf[4][4], float x, float y, float z) {
    guIdentityF(mf);
    mf[3][0] = x;
    mf[3][1] = y;
    mf[3][2] = z;
}

void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]) {
    float tmp[4][4];
    float (*out)[4] = r;
    int i, j, k;

    if (r == m || r == n) {
        out = tmp;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            float sum = 0.0f;
            for (k = 0; k < 4; k++) {
                sum += m[i][k] * n[k][j];
            }
            out[i][j] = sum;
        }
    }

    if (out != r) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                r[i][j] = out[i][j];
            }
        }
    }
}

void guScaleF(float mf[4][4], float x, float y, float z) {
    guIdentityF(mf);
    mf[0][0] = x;
    mf[1][1] = y;
    mf[2][2] = z;
}

void guRotateF(float mf[4][4], float a, float x, float y, float z) {
    float len = sqrtf(x * x + y * y + z * z);
    float s;
    float c;
    float t;
    float radians;

    if (len == 0.0f) {
        guIdentityF(mf);
        return;
    }

    x /= len;
    y /= len;
    z /= len;

    radians = a * (float)M_PI / 180.0f;
    s = sinf(radians);
    c = cosf(radians);
    t = 1.0f - c;

    guIdentityF(mf);
    mf[0][0] = t * x * x + c;
    mf[0][1] = t * x * y + s * z;
    mf[0][2] = t * x * z - s * y;

    mf[1][0] = t * x * y - s * z;
    mf[1][1] = t * y * y + c;
    mf[1][2] = t * y * z + s * x;

    mf[2][0] = t * x * z + s * y;
    mf[2][1] = t * y * z - s * x;
    mf[2][2] = t * z * z + c;
}

void guRotateRPYF(float mf[4][4], float r, float p, float h) {
    float rx[4][4];
    float ry[4][4];
    float rz[4][4];
    float tmp[4][4];

    guRotateF(rx, r, 1.0f, 0.0f, 0.0f);
    guRotateF(ry, p, 0.0f, 1.0f, 0.0f);
    guRotateF(rz, h, 0.0f, 0.0f, 1.0f);

    guMtxCatF(rx, ry, tmp);
    guMtxCatF(tmp, rz, mf);
}

void guMtxF2L(float mf[4][4], Mtx* m) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m->m[i][j] = (s32) (mf[i][j] * 65536.0f);
        }
    }
}

void guMtxL2F(float mf[4][4], Mtx* m) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mf[i][j] = (float)m->m[i][j] / 65536.0f;
        }
    }
}

void guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale) {
    guIdentityF(mf);
    mf[0][0] = 2.0f / (r - l);
    mf[1][1] = 2.0f / (t - b);
    mf[2][2] = -2.0f / (f - n);
    mf[3][0] = -(r + l) / (r - l);
    mf[3][1] = -(t + b) / (t - b);
    mf[3][2] = -(f + n) / (f - n);

    if (scale != 1.0f) {
        mf[0][0] *= scale;
        mf[1][1] *= scale;
        mf[2][2] *= scale;
    }
}

void guMtxIdentF(float mf[4][4]) {
    guIdentityF(mf);
}

void guMtxIdent(Mtx* m) {
    float mf[4][4];
    guIdentityF(mf);
    guMtxF2L(mf, m);
}

void guScale(Mtx* m, float x, float y, float z) {
    float mf[4][4];
    guScaleF(mf, x, y, z);
    guMtxF2L(mf, m);
}

void guTranslate(Mtx* m, float x, float y, float z) {
    float mf[4][4];
    guTranslateF(mf, x, y, z);
    guMtxF2L(mf, m);
}

void guRotate(Mtx* m, float a, float x, float y, float z) {
    float mf[4][4];
    guRotateF(mf, a, x, y, z);
    guMtxF2L(mf, m);
}

void guPosition(Mtx* m, float r, float p, float h, float s, float x, float y, float z) {
    float mf[4][4];
    guPositionF(mf, r, p, h, s, x, y, z);
    guMtxF2L(mf, m);
}

void guMtxXFMF(float mf[4][4], float x, float y, float z, float* ox, float* oy, float* oz) {
    float tx = x * mf[0][0] + y * mf[1][0] + z * mf[2][0] + mf[3][0];
    float ty = x * mf[0][1] + y * mf[1][1] + z * mf[2][1] + mf[3][1];
    float tz = x * mf[0][2] + y * mf[1][2] + z * mf[2][2] + mf[3][2];

    if (ox) {
        *ox = tx;
    }
    if (oy) {
        *oy = ty;
    }
    if (oz) {
        *oz = tz;
    }
}

void guMtxXFML(Mtx* m, float x, float y, float z, float* ox, float* oy, float* oz) {
    float mf[4][4];
    guMtxL2F(mf, m);
    guMtxXFMF(mf, x, y, z, ox, oy, oz);
}

void guLookAtHiliteF(float mf[4][4], LookAt* l, Hilite* h,
                     float xEye, float yEye, float zEye,
                     float xAt, float yAt, float zAt,
                     float xUp, float yUp, float zUp,
                     float xl1, float yl1, float zl1,
                     float xl2, float yl2, float zl2,
                     int twidth, int theight) {
    float len, xLook, yLook, zLook, xRight, yRight, zRight;
    float xHilite, yHilite, zHilite;

    guMtxIdentF(mf);

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;

    /* Negate because positive Z is behind us: */
    len = -1.0f / sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    /* Right = Up x Look */
    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    /* Up = Look x Right */
    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    /* hilite vectors */
    len = 1.0f / sqrtf(xl1 * xl1 + yl1 * yl1 + zl1 * zl1);
    xl1 *= len;
    yl1 *= len;
    zl1 *= len;

#define THRESH2 0.1f
    xHilite = xl1 + xLook;
    yHilite = yl1 + yLook;
    zHilite = zl1 + zLook;

    len = sqrtf(xHilite * xHilite + yHilite * yHilite + zHilite * zHilite);

    if (len > THRESH2) {
        len = 1.0f / len;
        xHilite *= len;
        yHilite *= len;
        zHilite *= len;

        h->h.x1 = twidth * 4 + (int)((xHilite * xRight + yHilite * yRight + zHilite * zRight) * twidth * 2);
        h->h.y1 = theight * 4 + (int)((xHilite * xUp + yHilite * yUp + zHilite * zUp) * theight * 2);
    } else {
        h->h.x1 = twidth * 2;
        h->h.y1 = theight * 2;
    }

    len = 1.0f / sqrtf(xl2 * xl2 + yl2 * yl2 + zl2 * zl2);
    xl2 *= len;
    yl2 *= len;
    zl2 *= len;

    xHilite = xl2 + xLook;
    yHilite = yl2 + yLook;
    zHilite = zl2 + zLook;
    len = sqrtf(xHilite * xHilite + yHilite * yHilite + zHilite * zHilite);
    if (len > THRESH2) {
        len = 1.0f / len;
        xHilite *= len;
        yHilite *= len;
        zHilite *= len;

        h->h.x2 = twidth * 4 + (int)((xHilite * xRight + yHilite * yRight + zHilite * zRight) * twidth * 2);
        h->h.y2 = theight * 4 + (int)((xHilite * xUp + yHilite * yUp + zHilite * zUp) * theight * 2);
    } else {
        h->h.x2 = twidth * 2;
        h->h.y2 = theight * 2;
    }
#undef THRESH2

    /* reflectance vectors = Up and Right */
    l->l[0].l.dir[0] = FTOFRAC8(xRight);
    l->l[0].l.dir[1] = FTOFRAC8(yRight);
    l->l[0].l.dir[2] = FTOFRAC8(zRight);
    l->l[1].l.dir[0] = FTOFRAC8(xUp);
    l->l[1].l.dir[1] = FTOFRAC8(yUp);
    l->l[1].l.dir[2] = FTOFRAC8(zUp);
    l->l[0].l.col[0] = 0x00;
    l->l[0].l.col[1] = 0x00;
    l->l[0].l.col[2] = 0x00;
    l->l[0].l.pad1 = 0x00;
    l->l[0].l.colc[0] = 0x00;
    l->l[0].l.colc[1] = 0x00;
    l->l[0].l.colc[2] = 0x00;
    l->l[0].l.pad2 = 0x00;
    l->l[1].l.col[0] = 0x00;
    l->l[1].l.col[1] = 0x80;
    l->l[1].l.col[2] = 0x00;
    l->l[1].l.pad1 = 0x00;
    l->l[1].l.colc[0] = 0x00;
    l->l[1].l.colc[1] = 0x80;
    l->l[1].l.colc[2] = 0x00;
    l->l[1].l.pad2 = 0x00;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

    mf[0][3] = 0;
    mf[1][3] = 0;
    mf[2][3] = 0;
    mf[3][3] = 1;
}

void guLookAtReflectF(float mf[4][4], LookAt* l,
                      float xEye, float yEye, float zEye,
                      float xAt, float yAt, float zAt,
                      float xUp, float yUp, float zUp) {
    float len, xLook, yLook, zLook, xRight, yRight, zRight;

    guMtxIdentF(mf);

    xLook = xAt - xEye;
    yLook = yAt - yEye;
    zLook = zAt - zEye;

    /* Negate because positive Z is behind us: */
    len = -1.0f / sqrtf(xLook * xLook + yLook * yLook + zLook * zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    /* Right = Up x Look */
    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0f / sqrtf(xRight * xRight + yRight * yRight + zRight * zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    /* Up = Look x Right */
    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0f / sqrtf(xUp * xUp + yUp * yUp + zUp * zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    /* reflectance vectors = Up and Right */
    l->l[0].l.dir[0] = FTOFRAC8(xRight);
    l->l[0].l.dir[1] = FTOFRAC8(yRight);
    l->l[0].l.dir[2] = FTOFRAC8(zRight);
    l->l[1].l.dir[0] = FTOFRAC8(xUp);
    l->l[1].l.dir[1] = FTOFRAC8(yUp);
    l->l[1].l.dir[2] = FTOFRAC8(zUp);
    l->l[0].l.col[0] = 0x00;
    l->l[0].l.col[1] = 0x00;
    l->l[0].l.col[2] = 0x00;
    l->l[0].l.pad1 = 0x00;
    l->l[0].l.colc[0] = 0x00;
    l->l[0].l.colc[1] = 0x00;
    l->l[0].l.colc[2] = 0x00;
    l->l[0].l.pad2 = 0x00;
    l->l[1].l.col[0] = 0x00;
    l->l[1].l.col[1] = 0x80;
    l->l[1].l.col[2] = 0x00;
    l->l[1].l.pad1 = 0x00;
    l->l[1].l.colc[0] = 0x00;
    l->l[1].l.colc[1] = 0x80;
    l->l[1].l.colc[2] = 0x00;
    l->l[1].l.pad2 = 0x00;

    mf[0][0] = xRight;
    mf[1][0] = yRight;
    mf[2][0] = zRight;
    mf[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);

    mf[0][1] = xUp;
    mf[1][1] = yUp;
    mf[2][1] = zUp;
    mf[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);

    mf[0][2] = xLook;
    mf[1][2] = yLook;
    mf[2][2] = zLook;
    mf[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);

    mf[0][3] = 0;
    mf[1][3] = 0;
    mf[2][3] = 0;
    mf[3][3] = 1;
}

void guOrtho(Mtx* m, float l, float r, float b, float t, float n, float f, float scale) {
    float mf[4][4];
    guOrthoF(mf, l, r, b, t, n, f, scale);
    guMtxF2L(mf, m);
}

void guFrustumF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale) {
    guIdentityF(mf);
    mf[0][0] = (2.0f * n) / (r - l);
    mf[1][1] = (2.0f * n) / (t - b);
    mf[2][0] = (r + l) / (r - l);
    mf[2][1] = (t + b) / (t - b);
    mf[2][2] = -(f + n) / (f - n);
    mf[2][3] = -1.0f;
    mf[3][2] = -(2.0f * f * n) / (f - n);
    mf[3][3] = 0.0f;

    if (scale != 1.0f) {
        mf[0][0] *= scale;
        mf[1][1] *= scale;
    }
}

void guPerspectiveF(float mf[4][4], u16* perspNorm, float fovy, float aspect, float near, float far, float scale) {
    float half = fovy * 0.5f * (float)M_PI / 180.0f;
    float cot = cosf(half) / sinf(half);

    guIdentityF(mf);
    mf[0][0] = cot / aspect;
    mf[1][1] = cot;
    mf[2][2] = (far + near) / (near - far);
    mf[2][3] = -1.0f;
    mf[3][2] = (2.0f * far * near) / (near - far);
    mf[3][3] = 0.0f;

    if (scale != 1.0f) {
        mf[0][0] *= scale;
        mf[1][1] *= scale;
    }

    if (perspNorm != NULL) {
        *perspNorm = 0xFFFF;
    }
}

void guPositionF(float mf[4][4], float r, float p, float h, float s, float x, float y, float z) {
    float rx[4][4];
    float ry[4][4];
    float rz[4][4];
    float tmp[4][4];
    float tmp2[4][4];
    float scale[4][4];
    float trans[4][4];

    guRotateF(rx, r, 1.0f, 0.0f, 0.0f);
    guRotateF(ry, p, 0.0f, 1.0f, 0.0f);
    guRotateF(rz, h, 0.0f, 0.0f, 1.0f);
    guScaleF(scale, s, s, s);
    guTranslateF(trans, x, y, z);

    guMtxCatF(rz, ry, tmp);
    guMtxCatF(tmp, rx, tmp2);
    guMtxCatF(tmp2, scale, tmp);
    guMtxCatF(tmp, trans, mf);
}
