;HH NOE experiment (TopSpin 2.3)

;######################################################
;#                                                    #
;#  HN NOESY for solids                                #
;#                                                    #
;######################################################
;
;$COMMENT= HH NOESY Transfer Experiment
;$CLASS=Solids
;$DIM=2D
;$TYPE= 1H detect Hetero
;$SUBTYPE=Dipolar Transfer
;$OWNER=guest
;
#include <HCN_defs.incl>

;######################################################
;#                   Define Mixing                    #
;#    NOESY is Default, add Selective 90 w/ option    #
;######################################################

#include <fmp.HNOE.subr>

;cnst11 : adjust t=0 for acq, if digmod = baseopt
"acqt0=1u*cnst11"

define delay ONTIME
                            ;##########################
;$EXTERN                    ;# python insertion point #
                            ;##########################


Prepare, ze

"ONTIME=aq"                 ;#  DARR left out   #

;######################################################
;#               Protections: Pre-Check               #
;######################################################

#include <1H_ON_prot.incl>
        ;total RF depsosition restriction

;######################################################
;#           Start of Active Pulse Program            #
;######################################################

Start, d1 do:C do:N

;######################
;#      PRESAT        #
;######################

#ifdef PRE
  3u pl9:H
  d18 cw:H ph20
  4u do:H
#endif

#ifdef PURGE
  5u
  (p23:spf23 pl23 ph0):H
  5u
  d5
#endif

#ifdef SInv
  5u
  (p24:spf24 pl24 ph0):H
  5u
  d5
#endif

  (p3 pl2 ph1):H
  3u

;#######################################################
;#                     Acquisition                     #
;#######################################################

;  3u  pl3:N  pl4:C     ; GARP power on 15N
;  1u  cpd3:N cpd4:C

  go=Start ph31
;  1m do:N do:C

  30m mc #0 to Start F0(zd)

HaltAcqu, 1m
exit

;#######################################################
;#             Phase Cycle (min=4, full=16)            #
;#######################################################

ph0=  2 1 0 3 
ph1=  0 2
ph20= 0

ph31= 0 2 

;PARAMETERS:
;p1      : C 90  (pl1)
;p2      : C 180 (pl1)
;p3      : H 90  (pl2)
;p8      : C Presat (-DCpre)
;p6      : C soft 90  (pl26)
;p10     : HC CP contact pl10 (C) and sp0 (H)
;sp0     : H CP pwr
;pl1     : C HP pwr
;pl2     : H HP pwr
;pl3     : N dec pwr
;pl4     : C dec pwr
;pl10    : C CP pwr
;pl12    : H dec pwr
;pl13    : H alt dec pwr (Spinlock and CW)
;pl16    : H DARR pwr (DARR = MAS freq; PDSD =120)
;pl26    : C soft 90 pwr
;d1      : recycle delay
;d8      : PDSD/DARR mix time
;pcpd2   : pulse length in decoupling sequence
;cpdprg2 : cw, tppm (at pl12), or lgs, cwlg. cwlgs (LG-decoupling 
;spnam0  : use e.g. ramp.100 for variable amplitude CP
;spnam6  : C soft 90 purge pulse (e.g. eSNOB)
;cnst30  : expected td1 for use in constant Duty (-DCDC)
;cnst31  : MAS Rate
;FnMode  : TPPI, States or States-TPPI
;zgoptns : (-D) PRE, PURGE
