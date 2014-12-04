;C_zgdec

;Direct Polarization for X channel (13C)
;written by WTF
;Avance II+ version

;######################################################
;#                                                    #
;#  C Direct Polarization Experiment                  #
;#                                                    #
;#  Adjust pl1, p1 for maximum signal.                #
;#                                                    #
;######################################################

;$COMMENT= C Direct excitation
;$CLASS=Solids
;$DIM=1D
;$TYPE=Direct Polarization
;$SUBTYPE=Setup
;$OWNER=Guest

define delay ONTIME
;prosol relations=<solids_cp>

;#include <Avancesolids.incl>
#include <C_detect_def.incl>

;cnst11 : to adjust t=0 for acquisition, if digmod = baseopt
"acqt0=1u*cnst11"
                            ;##########################
;$EXTERN                    ;# Python insertion point #
                            ;##########################
Prepare, ze

;######################################################
;#               Protections: Pre-Check               #
;######################################################

"ONTIME=aq"

#include <Standard_Prot.incl>
        ;acq, CP time, etc.
#include <ONTIME_prot.incl>
        ;total RF depsosition restriction

;######################################################
;#           Start of Active Pulse Program            #
;######################################################

Start, d1 do:H

  0.3u cpds2:H ;decouple 1H during acquisition
  (p1 pl1 ph10):C

;#######################################################
;#                     Acquisition                     #
;#######################################################

  go=Start ph31         
  1m do:H
  30m mc #0 to Start F0(zd)

HaltAcqu, 1m
exit

ph10= 1 3 3 1 2 0 0 2  ; X90 DP
ph31= 0 2 2 0 1 3 3 1  ; receiver

;#########################################################################

;PARAMETERS:
;pl1     : C HP pwr level
;p1      : C 90 
;p2      : C 180
;pl2     : H HP pwr
;p3      : H 90 at pl2
;p4      : H 180 at pl2
;pl12    : H dec pwr
;pl13    : H alt dec pwr (Spinlock and CW)
;d1      : recycle delay
;pcpd2   : pulse length in decoupling sequence
;cpdprg2 : cw, tppm (at pl12), or lgs, cwlg. cwlgs (LG-decoupling 

