#ifndef _ports_h_                              /* include file only once */
#define _ports_h_
class Ports{
public:
const static int DRIVE_TRAIN_TOP_LEFT_PORT =2;
const static int DRIVE_TRAIN_BOTTOM_LEFT_PORT =15;
const static int DRIVE_TRAIN_TOP_RIGHT_PORT =13;
const static int DRIVE_TRAIN_BOTTOM_RIGHT_PORT =14;

const static int INTAKE_PORT_0 =2;
const static int INTAKE_PORT_1 =10;

const static int TRAY_PORT_0 =17;
const static int TRAY_PORT_1 =16;
const static int TRAY_CUBE_SWITCH = 0;
const static int TRAY_ZERO_SWITCH = 1;

const static int LIFT_PORT_0 =17;
const static int LIFT_PORT_1 =16;
const static int LIFT_ZERO_SWITCH = 2;

constexpr static double UNFOLD_OFFSET = 2;




};
#endif