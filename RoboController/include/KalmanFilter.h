//
// Created by Lukas on 10.11.2018.
//

#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include <vector>
#include <stdint.h>
#include <cmath>

class KalmanFilter
{
public:
    void computeCoordinates();
    std::vector<uint16_t> getFilteredXYZCoordinateSystem() const;
    void setRawCoordinates(uint16_t _ax, uint16_t _gx, uint16_t _ay, uint16_t _gy, uint16_t _az, uint16_t _gz);
    void setFilterfingPollInterval(uint32_t millis);

    KalmanFilter()
    {
        dt = 0.1;

        A[0] = 1;
        A[1] = -dt;
        A[2] = 0;
        A[3] = 1;

        B[0] = dt;
        B[1] = 0;

        C[0] = 1;
        C[1] = 0;

        std_dev_v = 1;
        std_dev_w = 2;
        V[0] = std_dev_v*std_dev_v*dt;
        V[1] = 0;
        V[2] = 0;
        V[3] = std_dev_v*std_dev_v*dt;
        W[0] = std_dev_w*std_dev_w;

        // Initial filter values
        P_post[0] = 1;
        P_post[1] = 0;
        P_post[2] = 0;
        P_post[3] = 1;
    };

private:
    uint16_t filteredX;
    uint16_t filteredY;
    uint16_t filteredZ;

    uint16_t ax, ay, az, gx, gy, gz;

    uint32_t pollIntervalMillis = 100; // 100 ms as default

    float dt;
    float A[4], B[2], C[2];
    float std_dev_v, std_dev_w;
    float V[4], W[1];
    float P_pri[4], P_post[4];
    float x_post[2];
    float x_pri[2];
    float eps[1], S[1], K[2];
    float u[1], y[1];

    float Ax[2], Bu[2];
    float AP[4], AT[4], APAT[4];
    float Cx[1];
    float CP[2], CPCT[1];
    float PCT[2], S1[1];
    float Keps[2];
    float KS[2], KSKT[2];
};

void matrix_2x2_mul_2x1(float * in1, float * in2, float * out);
void matrix_2x1_mul_1x1(float * in1, float * in2, float * out);
void matrix_2x1_add_2x1(float * in1, float * in2, float * out);
void matrix_2x2_mul_2x2(float * in1, float * in2, float * out);
void matrix_2x2_add_2x2(float * in1, float * in2, float * out);
void matrix_1x2_mul_2x1(float * in1, float * in2, float * out);
void matrix_1x2_mul_2x2(float * in1, float * in2, float * out);
void matrix_2x1_mul_1x2(float * in1, float * in2, float * out);
void matrix_2x2_sub_2x2(float * in1, float * in2, float * out);
void matrix_2x2_trans(float * in, float * out);

#endif //KALMAN_FILTER_H
