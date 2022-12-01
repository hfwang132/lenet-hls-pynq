#include "op.h"
#include "param.h"

//#define TEST

#ifdef TEST
#include "tbutils.h"
#endif

using namespace mylenet;

int lenet(INPUT (&img)[32][32])
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi port=img offset=slave depth=1024
    // preprocess
	INPUT img_preprocessed[1][32][32] = {0};
    preprocess(img, img_preprocessed);

#ifdef TEST
    arr2txt("img_preprocessed_0.txt", img_preprocessed[0]); //
#endif

    // compute
    // (1) conv1 and relu
    BIAS conv1_relu_rst[6][28][28] = {0};
    DATA pool1_in[6][28][28] = {0};
    conv_relu(img_preprocessed, conv1_weights, conv1_bias, conv1_relu_rst);
    scale(conv1_relu_rst, n_conv1, m_conv1, pool1_in);

#ifdef TEST
    arr2txt("conv1_relu_rst_0.txt", conv1_relu_rst[0]);
#endif

    // (2) pooling1
    DATA pool1_rst[6][14][14] = {0};
    maxpooling(pool1_in, 2, 2, pool1_rst);

    // (3) conv2 and relu
    BIAS conv2_relu_rst[16][10][10] = {0};
    DATA pool2_in[16][10][10] = {0};
    conv_relu(pool1_rst, conv2_weights, conv2_bias, conv2_relu_rst);
    scale(conv2_relu_rst, n_conv2, m_conv2, pool2_in);

#ifdef TEST
    arr2txt("conv2_relu_rst_0.txt", conv2_relu_rst[0]);
#endif
    // (4) pool2
    DATA pool2_rst[16][5][5] = {0};
    maxpooling(pool2_in, 2, 2, pool2_rst);

    // (5) flatten
    DATA flattened[400] = {0};
    flatten(pool2_rst, flattened);

    // (6) fc1
    BIAS fc1_relu_rst[120] = {0};
    DATA fc2_in[120] = {0};
    fc_relu(flattened, fc1_weights, fc1_bias, fc1_relu_rst);
    scale(fc1_relu_rst, n_fc1, m_fc1, fc2_in);

#ifdef TEST
    arr1d2txt("fc1_relu_rst.txt", fc1_relu_rst);
#endif

    // (7) fc2
    BIAS fc2_relu_rst[84] = {0};
    DATA fc3_in[84] = {0};
    fc_relu(fc2_in, fc2_weights, fc2_bias, fc2_relu_rst);
    scale(fc2_relu_rst, n_fc2, m_fc2, fc3_in);

#ifdef TEST
    arr1d2txt("fc2_relu_rst.txt", fc2_relu_rst);
#endif

    // (8) fc3
    BIAS final_rst[10] = {0};
    fc(fc3_in, fc3_weights, fc3_bias, final_rst);

#ifdef TEST
    arr1d2txt("final_rst.txt", final_rst);
#endif

    return max_idx(final_rst);
}
