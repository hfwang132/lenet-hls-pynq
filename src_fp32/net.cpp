#include "op.h"
#include "param.h"

using namespace mylenet;

int lenet(INPUT (&img)[32][32])
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi port=img offset=slave depth=1024
    // preprocess
    DATA img_preprocessed[1][32][32] = {0};
    preprocess(img, img_preprocessed);

    // compute
    DATA conv1_relu_rst[6][28][28];
    conv_relu(img_preprocessed, conv1_weights, conv1_bias, conv1_relu_rst);

    // (2) pooling1
    DATA pool1_rst[6][14][14];
    maxpooling(conv1_relu_rst, 2, 2, pool1_rst);

    // (3) conv2 and relu
    DATA conv2_relu_rst[16][10][10];
    conv_relu(pool1_rst, conv2_weights, conv2_bias, conv2_relu_rst);

    // (4) pool2
    DATA pool2_rst[16][5][5];
    maxpooling(conv2_relu_rst, 2, 2, pool2_rst);

    // (5) flatten
    DATA flattened[400];
    flatten(pool2_rst, flattened);

    // (6) fc1
    DATA fc1_relu_rst[120];
    fc_relu(flattened, fc1_weights, fc1_bias, fc1_relu_rst);

    // (7) fc2
    DATA fc2_relu_rst[84];
    fc_relu(fc1_relu_rst, fc2_weights, fc2_bias, fc2_relu_rst);

    // (8) fc3
    DATA final_rst[10];
    fc(fc2_relu_rst, fc3_weights, fc3_bias, final_rst);

    return max_idx(final_rst);
}
