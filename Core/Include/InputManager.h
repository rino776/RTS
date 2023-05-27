#pragma once
#include <memory>
namespace core {

typedef enum key {
        key_0 = 48,
        key_1,
        key_2,
        key_3,
        key_4,
        key_5,
        key_6,
        key_7,
        key_8,
        key_9,
        key_a = 65,
        key_b,
        key_c,
        key_d,
        key_e,
        key_f,
        key_g,
        key_h,
        key_i,
        key_j,
        key_k,
        key_l,
        key_m,
        key_n,
        key_o,
        key_p,
        key_q,
        key_r,
        key_s,
        key_t,
        key_u,
        key_v,
        key_w,
        key_x,
        key_y,
        key_z,
        key_escape = 256,
        key_enter,
        key_tab,
        key_right = 262,
        key_left,
        key_down,
        key_up,
        key_max_value
    } Key;

class InputManager
{
public:

    InputManager();
    ~InputManager();
    //TODO:: add these as needed

    bool getKeyDown(Key key);
    void setKey(int key, int action);

private:
    bool* m_keyState;
};
}

