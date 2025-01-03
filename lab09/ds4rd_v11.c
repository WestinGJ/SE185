/*-----------------------------------------------------------------------------
-                       DualShock4 Interface Program
-               Developed for 185-Rursch by T.Tran and K.Wang
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <math.h>

#include "include/hidapi.h"

#define RUMBLE_F 2048
#define TPAD_F 1024
#define GRYO_F 512
#define DPAD_F 256
#define TRIGGER_F 128
#define TIME_F 64
#define BUTTON_F 32
#define RJOYSTICK_F 16
#define LJOYSTICK_F 8
#define ACCEL_F 4
#define TYPE_F 2
#define DEV_F 1

#define DS4_BT 1
#define DS4_USB 2

#define HID_RS 78

#define TRI_B 128
#define CIR_B 64
#define X_B 32
#define SQU_B 16

#define D_RELEASED 8
#define NW_B 7
#define W_B 6
#define SW_B 5
#define S_B 4
#define SE_B 3
#define E_B 2
#define NE_B 1
#define N_B 0

#define R3_B 128
#define L3_B 64
#define OPT_B 32
#define SHARE_B 16
#define R2_B 8
#define L2_B 4
#define R1_B 2
#define L1_B 1

#define T_PAD 2
#define PS 1

#define F1_BTNS 1
#define F2_BTNS 2
#define F3_BTNS 4

struct timeval prog_start;

struct ds4_t {
    unsigned char lx;
    unsigned char ly;
    unsigned char rx;
    unsigned char ry;
    unsigned char f1_btns; // Circle, Triangle, etc high nibble, d-pad low nibble
    unsigned char f2_btns; // L# and R# buttons plus OPT and SHARE
    unsigned char tpps_btns;  // 6 bits counter, 7 T-PAD and 8 PS button
    unsigned char l_trigger;
    unsigned char r_trigger;
    unsigned short time_stamp;
    unsigned char battery;
    short accel[3];
    short gyro[3];
    unsigned char f0[10];
    unsigned char tf0[3];
    unsigned char f1;
    unsigned char tf1[3];
} __attribute((packed));


void print_time(char *output)
{
    struct timeval t;
    char tmp[64] = {0};
    int res = gettimeofday(&t, NULL);
    if(res)
        perror("gettimeofday");
    long mt = (t.tv_sec - prog_start.tv_sec)*1000 + (t.tv_usec - prog_start.tv_usec)/1000.0;
    sprintf(tmp,"%8ld", mt);
    strcat(output, tmp);
    strcat(output, ", ");
}

void _print_f1_buttons(unsigned char buttons, char *output)
{
    char str[9] = {0};
    (buttons & TRI_B) ? strcpy(str, "1") : strcpy(str, "0");
    (buttons & CIR_B) ? strcat(str, ",1") : strcat(str, ",0");
    (buttons & X_B) ? strcat(str, ",1") : strcat(str, ",0");
    (buttons & SQU_B) ? strcat(str, ",1") : strcat(str, ",0");
    strcat(output, str);
    strcat(output, ", ");
}

void _print_f2_buttons(unsigned char buttons, char *output)
{
    char str[18] = {0};
    (buttons & R3_B) ? strcpy(str, "1") : strcpy(str, "0");
    (buttons & L3_B) ? strcat(str, ",1") : strcat(str, ",0");
    (buttons & OPT_B) ? strcat(str, ",1") : strcat(str, ",0");
    (buttons & SHARE_B) ? strcat(str, ",1") : strcat(str, ",0");
    (buttons & R2_B) ? strcat(str, ",1") : strcat(str, ",0");
    (buttons & L2_B) ? strcat(str, ",1") : strcat(str, ",0");
    (buttons & R1_B) ? strcat(str, ",1") : strcat(str, ",0");
    (buttons & L1_B) ? strcat(str, ",1") : strcat(str, ",0");
    strcat(output, str);
    strcat(output, ", ");
}

void _print_f3_buttons(unsigned char buttons, char *output)
{
   char str[9] =  {0};
   switch(buttons & 0xFF) {
       case  NW_B:
            strcpy(str, "1,1,0,0");
            break;
       case W_B:
            strcpy(str, "0,1,0,0");
            break;
       case SW_B:
            strcpy(str, "0,1,1,0");
            break;
        case S_B:
            strcpy(str, "0,0,1,0");
            break;
       case SE_B:
            strcpy(str, "0,0,1,1");
            break;
       case E_B:
            strcpy(str, "0,0,0,1");
            break;
       case NE_B:
            strcpy(str, "1,0,0,1");
            break;
       case N_B:
            strcpy(str, "1,0,0,0");
            break;
       default:
            strcpy(str, "0,0,0,0");
   }
   strcat(output, str);
   strcat(output, ", ");
}

void print_buttons(unsigned char buttons, unsigned char type, char *output)
{
    if(type & F1_BTNS)
        _print_f1_buttons(buttons, output);
    if(type & F2_BTNS)
        _print_f2_buttons(buttons, output);
    if(type & F3_BTNS)
        _print_f3_buttons(buttons, output);
}

void bound_values(float *v)
{
    if(*v > 1) {
        *v = 1;
    } else if(*v < -1) {
        *v = -1;
    }
}



#define USENSOR_MAX 2048
void uprint_sensor(unsigned short *sen, char *output)
{

    float x,y,z;
	char tmp[256] = {0};
	unsigned short newX, newY, newZ;
	signed short newX2, newY2, newZ2;
	newX = (sen[0] & 0x0FFF) <<4 ;
	newX2 = (signed) newX;
	newX2 = newX2/16;

	newY = (sen[1] & 0x0FFF) <<4 ;
	newY2 = (signed) newY;
	newY2 = newY2/16;

	newZ = (sen[2] & 0x0FFF) <<4 ;
	newZ2 = (signed) newZ;
	newZ2 = newZ2/16;


	if (newX2 < 0.0) {
		x = (float) newX2/2047.0;
	}
	else {
		x = (float) newX2/2048.0;
	}

	if (newY2 < 0.0) {
		y = (float) newY2/2047.0;
	}
	else {
		y = (float) newY2/2048.0;
	}

	if (newZ2 < 0.0) {
		z = (float) newZ2/2047.0;
	}
	else {
		z = (float) newZ2/2048.0;
	}


	sprintf(tmp, "%10f, %10f, %10f", x,y,z);
	strcat(output, tmp);
    strcat(output, ", ");

}






#define SENSOR_MAX 8192
void print_sensor(short *sen, char *output)
{
    float x,y,z;
	char tmp[256] = {0};
    x = -1+((float)((int)(sen[0]+SENSOR_MAX)*2)/(SENSOR_MAX*2-1));
    y = -1+((float)((int)(sen[1]+SENSOR_MAX)*2)/(SENSOR_MAX*2-1));
    z = -1+((float)((int)(sen[2]+SENSOR_MAX)*2)/(SENSOR_MAX*2-1));
    bound_values(&x); bound_values(&y); bound_values(&z);
    sprintf(tmp, "%10f, %10f, %10f", x,y,z);
    strcat(output, tmp);
    strcat(output, ", ");
}

void print_tpad(unsigned char *tf0, unsigned char *tf1, char *output)
{
    char tmp[128] = {0};
    sprintf(tmp, "%2u,%2u,%2u %2u,%2u,%2u", tf0[0], tf1[1], tf1[2], tf1[0], tf1[1], tf1[2]);
    strcat(output, tmp);
    strcat(output, ", ");
}

#define JOY_MIN 128
void print_thejoy(unsigned char x, unsigned char y, char *output)
{
    char tmp[64] = {0};
    sprintf(tmp, "%4d, %4d", (x-JOY_MIN), (y-JOY_MIN));
    strcat(output, tmp);
    strcat(output, ", ");
}


void process_by_type(char *rbuf, int type, int flags)
{
        struct ds4_t *ds4 = (struct ds4_t *) calloc(1, sizeof(struct ds4_t));
        if(type & DS4_BT)
            ds4 = (struct ds4_t *) &rbuf[3];
        else if(type & DS4_USB)
            ds4 = (struct ds4_t *) &rbuf[1];
        else {
            fprintf(stderr, "No proper type given!\n");
            exit(-1);
        }
#ifdef DEBUG
        unsigned char *test = (unsigned char *) ds4;
        int i;
        for(i=0; i < HID_RS; i++)
            printf("%02x ", test[i]);
        printf("\n");
#endif
        char output[1024] = {0};
        if(flags & TIME_F)
            print_time(output);
		// Changed to uprint_sensor to see if unsigned values make sense
		//if(flags & ACCEL_F)
        //    print_sensor(ds4->accel, output);
		if(flags & ACCEL_F)
            uprint_sensor(ds4->accel, output);
        if(flags & GRYO_F)
            print_sensor(ds4->gyro, output);
        if(flags & BUTTON_F)
            print_buttons(ds4->f1_btns, F1_BTNS, output);
        if(flags & TRIGGER_F)
            print_buttons(ds4->f2_btns, F2_BTNS, output);
        if(flags & DPAD_F)
            print_buttons(ds4->f1_btns, F3_BTNS, output);
        if(flags & TPAD_F)
            print_tpad(ds4->tf0, ds4->tf1, output);
        if(flags & LJOYSTICK_F)
            print_thejoy(ds4->lx, ds4->ly, output);
        if(flags & RJOYSTICK_F)
            print_thejoy(ds4->rx, ds4->ry, output);
        int len = strlen(output);
        output[len-2] = 0;
        printf("%s\n", output);
        fflush(stdout);
}

void print_help(char *name)
{
    fprintf(stderr,"%s [-d DEVICE] [-D TYPE] [-j[lr]b[adt]tag]\n"
           "-d - Device string, format is XXXX:XXXX\n"
           "-D - Device Type: DS4_BT (DS4 Bluetooth) or DS4_USB (DS4 USB)\n"
           "-j - Joystick, optional arguments (l | r) for left or right only\n"
           "-b - Button, optional arguments (bt | td | d | t) for (button,trigger), (dpad,trigger), dpad or triggers.  No arguments - normal buttons.\n"
           "-t - Time\n"
           "-a - Accelerometer\n"
           "-g - Gyro\n", name
          );
}

int main(int argc, char *argv[])
{
    int res = gettimeofday(&prog_start, NULL);
    if(res)
        perror("gettimeofday");

    struct hid_device_info *devs, *cur_dev;

    if(hid_init()) {
        perror("hid_init failed!\n");
        return -1;
    }

    if(argc < 2) {
        devs = hid_enumerate(0,0);
        cur_dev = devs;
        while(cur_dev) {
            printf("Device\n\tType: %04hx %04hx\n\tPath: %s\n\tSerial Number:%ls\n\t",
                    cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
            printf("Manufacturer: %ls\n\t", cur_dev->manufacturer_string);
            printf("Product: %ls\n\t", cur_dev->product_string);
            printf("Release: %hx\n\t", cur_dev->release_number);
            printf("Interface: %d\n", cur_dev->interface_number);
            cur_dev = cur_dev->next;
        }
        hid_free_enumeration(devs);
        return 0;
    }


    int opt;
    unsigned int flags=0, type=0, i;
    unsigned long vid,pid;
    vid=pid=0;
    res=0;
    unsigned char *sc, *sub;
    unsigned char *rbuf = calloc(HID_RS+1,1);
    hid_device *hid;

    while((opt = getopt(argc, argv, "rhgTtab::j::d:D:")) != -1) {
        switch(opt) {
            case 'd':
                sc = calloc(5, 1);
                sub = optarg;
                while(*sub++ != ':')
                    res++;
#ifdef DEBUG
                printf("Vendor ID, res=%d\n", res);
#endif
                if(res > 4) {
                    fprintf(stderr, "-d incorrect.  Vendor ID is a short\n");
                    return -1;
                }
                memcpy(sc, optarg, res);
#ifdef DEBUG
                printf("Vendor ID, sc=%s\n", sc);
#endif
                vid = strtoul(sc, NULL, 16);
                res = strlen(sub);
                if(res > 4) {
                    fprintf(stderr, "-d incorrect, Product ID is a short\n");
                    return -1;
                }
                memcpy(sc, sub, res);
                pid = strtoul(sc, NULL, 16);
                flags |= DEV_F;
                free(sc);
                break;
            case 'D':
                flags |= TYPE_F;
                if(!strcmp(optarg, "DS4_BT")) {
                    type |= DS4_BT;
                } else if(!strcmp(optarg, "DS4_USB")) {
                    type |= DS4_USB;
                } else {
                    fprintf(stderr, "Unrecognized device type given: %s\n", optarg);
                    return -1;
                }
                break;
            case 'b':
                if(!optarg)
                    flags |= BUTTON_F;
                else if(!strcmp(optarg, "bt"))
                    flags |= BUTTON_F | TRIGGER_F;
                else if(!strcmp(optarg, "dt"))
                    flags |= DPAD_F | TRIGGER_F;
                else if(!strcmp(optarg, "d"))
                    flags |= DPAD_F;
                else if(!strcmp(optarg, "t"))
                    flags |= TRIGGER_F;
                else {
                    fprintf(stderr, "Unknown button argument given: %s\n", optarg);
                    return -1;
                }
                break;
            case 'j':
                if(!optarg)
                    flags |= LJOYSTICK_F | RJOYSTICK_F;
                else if(!strcmp(optarg, "l"))
                    flags |= LJOYSTICK_F;
                else if(!strcmp(optarg, "r"))
                    flags |= RJOYSTICK_F;
                else {
                    fprintf(stderr, "Invalid argument -j\n");
                    return -1;
                }
                break;
            case 'a':
                flags |= ACCEL_F;
                break;
            case 't':
                flags |= TIME_F;
                break;
            case 'g':
                flags |= GRYO_F;
                break;
            case 'T':
                flags |= TPAD_F;
                break;
            case 'r':
                flags |= RUMBLE_F;
                break;
            case 'h':
                print_help(argv[0]);
                return 0;
            default:
                fprintf(stderr, "Unrecognized option: %c\n", opt);
                break;
        }
    }

    if(!(flags & DEV_F)) {
        fprintf(stderr, "No device argument given.  Try -d\n");
        return 0;
    }

    if(!(flags & TYPE_F)) {
        fprintf(stderr, "No device type given.  Try -D\n");
        return 0;
    }

    hid = hid_open(vid, pid, NULL);
    if(!hid) {
        fprintf(stderr, "hid_open, try device enumeration and check Vendor ID and Product ID values.\n");
        return -1;
    }

    hid_set_nonblocking(hid, 1);
    rbuf[0] = 0x2;
    res = hid_get_feature_report(hid, rbuf, HID_RS);
    if(res < 0) {
        fprintf(stderr, "Unable to get feature requested feature report.\nhid_error=%ls\n", hid_error(hid));
    }
#ifdef DEBUG
    printf("Requested Feature report:\n");
    if(res > 0) {
        for(i=0; i<res; i++)
            printf("%02hhx ", rbuf[i]);
        printf("\n");
    }
#endif

    if(flags & RUMBLE_F) {
        char buf[30] = {0};
        buf[0] = 0x05; // HID data
        buf[1] = 0xff;
        buf[2] = 0x00; // LED
        buf[3] = 0x00; // ?
        buf[4] = 0xFF; // Rumble
        buf[5] = 0xFF; // Rumble
        buf[6] = 0xFF; // Red LED
        buf[7] = 0x00; // Green LED
        buf[8] = 0xFF; // Blue LED
        int test = hid_write(hid, buf, 30);
        if(test == -1)
            fprintf(stderr, "Could not write to device\n");
    }

    while(1) {
        res=0;
        while(res == 0) {
            res = hid_read(hid, rbuf, HID_RS);
#ifdef DEBUG
            if(res < 0)
                printf("hid_read failed, returned -1\n");
            if(res == 0)
                printf("Waiting on read........\n");
#endif
            usleep(10000);
        }

#ifdef DEBUG
        printf("Read %d bytes from hid_read\n", res);
        for(i=0; i< res; i++)
            printf("%02hhx ", rbuf[i]);
        printf("\n");
#endif
        process_by_type(rbuf, type, flags);
    }

    hid_close(hid);
    hid_exit();
    return 0;
}

