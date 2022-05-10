# yuvput
Build:
gcc yuvput.cpp -o yuvput
Usage:
yuvput outfile width height rate
If rate is 0, the YUV 422 uyvy 8bit pulses once through the entire spectrum of possible values across the height and width of the frame.
This is useful for tools such as AWS CDI sender which take a finite but large YUV file as input and cycle through it repeatedly.
If rate is non-zero, the output YUV file is updated in place at that frame rate until the cycle is finished.
This keeps the size of the output file small but does not necessarily sync well with the sender (needs more work).
