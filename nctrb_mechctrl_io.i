%module nctrb_mechctrl_io
%{
/* Write include header (Optional) */
/* #include "nctrb_mechctrl_io.h" */
%}

extern void nctrb_mc_io_initialize(void);

extern BYTE nctrb_mc_io_readStartButton(void);

extern BYTE nctrb_mc_io_readLineSensor(void);

extern void nctrb_mc_io_driveWheel(BYTE value);

extern WORD nctrb_mc_io_readPortIN1500(void);

extern void nctrb_mc_io_writePortOUT1500(WORD value);