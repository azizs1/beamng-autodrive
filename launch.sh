#!/bin/bash

set -e

cleanup() {
    echo "Killing ffmpeg..."
    taskkill.exe /IM ffmpeg.exe /F >/dev/null 2>&1 || true

    echo "Killing OBS..."
    taskkill.exe /IM obs64.exe /F >/dev/null 2>&1 || true
}

# https://www.linuxjournal.com/content/bash-trap-command
trap cleanup EXIT

echo "Starting OBS Virtual Camera..."
powershell.exe -Command "Start-Process -FilePath 'C:\Program Files\obs-studio\bin\64bit\obs64.exe' -WorkingDirectory 'C:\Program Files\obs-studio\bin\64bit' -ArgumentList '--startvirtualcam','--minimize-to-tray'"


sleep 2

echo "Starting ffmpeg capture..."
powershell.exe -Command "& 'C:\ffmpeg\bin\ffmpeg.exe' -f dshow -i video='OBS Virtual Camera' -f mpegts udp://172.19.9.85:9001" &

sleep 1

echo "Beginning BeamNG-AutoDrive..."
"./beamng-autodrive"

echo "Exited"
