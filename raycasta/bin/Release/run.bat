@ECHO OFF
ECHO =============
ECHO  System Info
ECHO =============
wmic cpu get name

ECHO =============
ECHO  Running 1T
ECHO =============
"%cd%"\data\raycasta.exe 1
py "%cd%"\data\bmcalc.py

ping -n 11 127.0.0.1>nul

ECHO =============
ECHO  Running 8T
ECHO =============
"%cd%"\data\raycasta.exe 8
py "%cd%"\data\bmcalc.py

ping -n 11 127.0.0.1>nul

ECHO =============
ECHO  Running 16T
ECHO =============
"%cd%"\data\raycasta.exe 16
py "%cd%"\data\bmcalc.py

ping -n 11 127.0.0.1>nul

ECHO =============
ECHO  Running 64T
ECHO =============
"%cd%"\data\raycasta.exe 64
py "%cd%"\data\bmcalc.py

DEL ft.txt
PAUSE