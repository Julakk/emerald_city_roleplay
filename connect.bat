@echo off
REM connect.bat — taruh file ini di folder yang sama dengan samp.exe
REM (folder instalasi GTA:SA). Double-click buat langsung connect
REM ke Emerald City Roleplay tanpa perlu buka server list.

set SERVER_IP=217.216.111.75
set SERVER_PORT=7034

start "" samp.exe %SERVER_IP%:%SERVER_PORT%
