#ifndef _PARAM_
#define _PARAM_
#include "./op.h"
#include "./param/conv1_bias.h"
#include "./param/conv1_weights.h"
#include "./param/conv2_bias.h"
#include "./param/conv2_weights.h"
#include "./param/fc1_bias.h"
#include "./param/fc1_weights.h"
#include "./param/fc2_bias.h"
#include "./param/fc2_weights.h"
#include "./param/fc3_bias.h"
#include "./param/fc3_weights.h"

int n_conv1 = 17;
int n_conv2 = 16;
int n_fc1 	= 15;
int n_fc2 	= 14;

mylenet::BIAS m_conv1 	= 129;
mylenet::BIAS m_conv2 	= 69;
mylenet::BIAS m_fc1 	= 31;
mylenet::BIAS m_fc2 	= 39;


#endif