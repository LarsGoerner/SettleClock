/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#ifndef APP_INPUT_H_
#define APP_INPUT_H_

struct input_pin {
        unsigned up_key         : 1;
        unsigned down_key       : 1;
        unsigned left_key       : 1;
        unsigned right_key      : 1;
};
extern struct input_pin pending_inputs;

void input_init(void);
void input_enable(void);
void input_disable(void);
void input_ack_inputs(void);

#endif // APP_INPUT_H_