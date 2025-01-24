#ifndef INTERFACE_DEFINES
#define INTERFACE_DEFINES

/* INPUT */

#define ENTER 10
#define ESCAPE 27
#define WHITESPACE 32
#define STICK 7

/* WINDOWS */

/* board window */
#define W0_H 27
#define W0_W 47

/* field window */
#define W1_H 20
#define W1_W 20
#define W1_MIN_Y 4
#define W1_MIN_X 6

/* next window */
#define W2_H 2
#define W2_W 8
#define W2_MIN_Y 6
#define W2_MIN_X 33

/* level window */
#define W3_H 1
#define W3_W 1
#define W3_MIN_Y 11
#define W3_MIN_X 40

/* score window */
#define W4_H 1
#define W4_W 8
#define W4_MIN_Y 17
#define W4_MIN_X 33

/* record window */
#define W5_H 1
#define W5_W 8
#define W5_MIN_Y 23
#define W5_MIN_X 33

/* message window */
#define W6_H 8
#define W6_W 16
#define W6_MIN_Y 6
#define W6_MIN_X 2

/* debug window */
#define W7_H 16
#define W7_W 32
#define W7_MIN_Y 0
#define W7_MIN_X 0

/* BORDERS */

/* board border */
#define R0_MIN_Y 0
#define R0_MIN_X 0
#define R0_MAX_Y 26
#define R0_MAX_X 46

/* field border */
#define R1_MIN_Y 3
#define R1_MIN_X 4
#define R1_MAX_Y 24
#define R1_MAX_X 27

/* next border */
#define R2_MIN_Y 3
#define R2_MIN_X 31
#define R2_MAX_Y 8
#define R2_MAX_X 42

/* level border */
#define R3_MIN_Y 10
#define R3_MIN_X 31
#define R3_MAX_Y 12
#define R3_MAX_X 42

/* score border */
#define R4_MIN_Y 14
#define R4_MIN_X 31
#define R4_MAX_Y 18
#define R4_MAX_X 42

/* record border */
#define R5_MIN_Y 20
#define R5_MIN_X 31
#define R5_MAX_Y 24
#define R5_MAX_X 42

/* INSCRIPTIONS */

/* texts */
#define I0 "Tetris by bodgerun               v1.1"
#define I1 "Next:"
#define I2 "Level:"
#define I3 "Score:"
#define I4 "Record:"

/* positions (board) */
#define I0_Y 1
#define I0_X 5
#define I1_Y 4
#define I1_X 33
#define I2_Y 11
#define I2_X 33
#define I3_Y 15
#define I3_X 33
#define I4_Y 21
#define I4_X 33

/* debug */
#define YES "YES"
#define NO "NO "
#define ON "ON "
#define OFF "OFF"

#endif
