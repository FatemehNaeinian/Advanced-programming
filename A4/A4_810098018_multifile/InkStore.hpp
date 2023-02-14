#ifndef INK_H
#define INK_H "INK_H"

#define CHARGE_RED 1000
#define CHARGE_BLACK 1000
#define CHARGE_GREEN 1000
#define CHARGE_BLUE 1000
#define CHARGE_PAPER 100

class InkStore {
public:
    InkStore(int red_amount=CHARGE_RED , int green_amount=CHARGE_GREEN , int blue_amount=CHARGE_BLUE , int black_amount=CHARGE_BLACK);    void charge_inkStore();

    int has_more_ink(InkStore orderInk , int ratio);

    int get_red();
    int get_blue();
    int get_black();
    int get_green();

    void show_info_InkStore();

    void update_InkStore(InkStore inkOrder , int ratio);

private:
    int red;
    int green;
    int blue;
    int black;
};

#endif