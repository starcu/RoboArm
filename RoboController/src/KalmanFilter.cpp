//
// Created by Lukas on 10.11.2018.
//

#include "KalmanFilter.h"

std::vector<uint16_t> KalmanFilter::getFilteredXYZCoordinateSystem() const
{
    return {filteredX, filteredY, filteredZ};
}

void KalmanFilter::setRawCoordinates(uint16_t _ax, uint16_t _gx, uint16_t _ay, uint16_t _gy, uint16_t _az, uint16_t _gz)
{
    ax = _ax;
    gx = _gx;

    ay = _ay;
    gy = _gy;

    az = _az;
    gz = _gz;
}

void KalmanFilter::setFilterfingPollInterval(uint32_t millis)
{
    pollIntervalMillis = millis;
}

void KalmanFilter::computeCoordinates()
{
    // x(t+1|t) = Ax(t|t) + Bu(t)
    u[0] = gz*250/32768;
    matrix_2x2_mul_2x1(A, x_post, Ax);
    matrix_2x1_mul_1x1(B, u, Bu);
    matrix_2x1_add_2x1(Ax, Bu, x_pri);

    // P(t+1|t) = AP(t|t)A^T + V
    matrix_2x2_mul_2x2(A, P_post, AP);
    matrix_2x2_trans(A, AT);
    matrix_2x2_mul_2x2(AP, AT, APAT);
    matrix_2x2_add_2x2(APAT, V, P_pri);

    // eps(t) = y(t) - Cx(t|t-1)
    if(ay == 0)
        ay = 1;
    y[0] = atan(ax/ay)*180/M_PI;
    matrix_1x2_mul_2x1(C, x_pri, Cx);
    eps[0] = y[0] - Cx[0];

    // S(t) = CP(t|t-1)C^T + W
    matrix_1x2_mul_2x2(C, P_pri, CP);
    matrix_1x2_mul_2x1(CP, C, CPCT);
    S[0] = CPCT[0] + W[0];

    // K(t) = P(t|t-1)C^TS(t)^-1
    matrix_2x2_mul_2x1(P_pri, C, PCT);
    if(S[0] == 0)
        S[0] = 1;
    S1[0] = 1/S[0];
    matrix_2x1_mul_1x1(PCT, S1, K);

    // x(t|t) = x(t|t-1) + K(t)eps(t)
    matrix_2x1_mul_1x1(K, eps, Keps);
    matrix_2x1_add_2x1(x_pri, Keps, x_post);

    // P(t|t) = P(t|t-1) - K(t)S(t)K(t)^T
    matrix_2x1_mul_1x1(K, S, KS);
    matrix_2x1_mul_1x2(KS, K, KSKT);
    matrix_2x2_sub_2x2(P_pri, KSKT, P_post);

    filteredX = x_post[1];
    filteredY = 0;
    filteredZ = 0;
}

void matrix_2x2_mul_2x1(float * in1, float * in2, float * out)
{
    out[0] = in1[0] * in2[0] + in1[1] * in2[1];
    out[1] = in1[2] * in2[0] + in1[3] * in2[1];
}

void matrix_2x1_mul_1x1(float * in1, float * in2, float * out)
{
    out[0] = in1[0] * in2[0];
    out[1] = in1[1] * in2[0];
}

void matrix_2x1_add_2x1(float * in1, float * in2, float * out)
{
    out[0] = in1[0] + in2[0];
    out[1] = in1[1] + in2[1];
}

void matrix_2x2_mul_2x2(float * in1, float * in2, float * out)
{
    out[0] = in1[0] * in2[0] + in1[1] * in2[2];
    out[1] = in1[0] * in2[1] + in1[1] * in2[3];
    out[2] = in1[2] * in2[0] + in1[3] * in2[2];
    out[3] = in1[2] * in2[1] + in1[3] * in2[3];
}

void matrix_2x2_add_2x2(float * in1, float * in2, float * out)
{
    out[0] = in1[0] + in2[0];
    out[1] = in1[1] + in2[1];
    out[2] = in1[2] + in2[2];
    out[3] = in1[3] + in2[3];
}

void matrix_1x2_mul_2x1(float * in1, float * in2, float * out)
{
    out[0] = in1[0] * in2[0] + in1[1] * in2[1];
}

void matrix_1x2_mul_2x2(float * in1, float * in2, float * out)
{
    out[0] = in1[0] * in2[0] + in1[1] * in2[2];
    out[1] = in1[0] * in2[1] + in1[1] * in2[3];
}

void matrix_2x1_mul_1x2(float * in1, float * in2, float * out)
{
    out[0] = in1[0] * in2[0];
    out[1] = in1[0] * in2[1];
    out[2] = in1[1] * in2[0];
    out[3] = in1[1] * in2[1];
}

void matrix_2x2_sub_2x2(float * in1, float * in2, float * out)
{
    out[0] = in1[0] - in2[0];
    out[1] = in1[1] - in2[1];
    out[2] = in1[2] - in2[2];
    out[3] = in1[3] - in2[3];
}

void matrix_2x2_trans(float * in, float * out)
{
    out[0] = in[0];
    out[1] = in[2];
    out[2] = in[1];
    out[3] = in[3];
}