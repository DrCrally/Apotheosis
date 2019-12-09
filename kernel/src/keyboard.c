#include "pic.h"
#include "portio.h"
#include "klog.h"
#include "kcommon.h"

#define PRESSED_ESC 0x1
#define PRESSED_1 0x2
#define PRESSED_2 0x3
#define PRESSED_3 0x4
#define PRESSED_4 0x5
#define PRESSED_5 0x6
#define PRESSED_6 0x7
#define PRESSED_7 0x8
#define PRESSED_8 0x9
#define PRESSED_9 0xA
#define PRESSED_0 0xB

#define PRESSED_Q 0x10
#define PRESSED_W 0x11
#define PRESSED_E 0x12
#define PRESSED_R 0x13
#define PRESSED_T 0x14
#define PRESSED_Y 0x15
#define PRESSED_U 0x16
#define PRESSED_I 0x17
#define PRESSED_O 0x18
#define PRESSED_P 0x19

#define PRESSED_A 0x1E
#define PRESSED_S 0x1F
#define PRESSED_D 0x20
#define PRESSED_F 0x21
#define PRESSED_G 0x22
#define PRESSED_H 0x23
#define PRESSED_J 0x24
#define PRESSED_K 0x25
#define PRESSED_L 0x26

#define PRESSED_Z 0x2C
#define PRESSED_X 0x2D
#define PRESSED_C 0x2E
#define PRESSED_V 0x2F
#define PRESSED_B 0x30
#define PRESSED_N 0x31
#define PRESSED_M 0x32

__attribute__((interrupt))
void keyboard_irq(void* unused)
{
    UNUSED(unused);
    klog("Key pressed (%d)\n", inb(0x60));
    pic_send_eoi(1);
}