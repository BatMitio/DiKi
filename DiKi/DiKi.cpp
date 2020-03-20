#include <windows.h> 
#include <mmsystem.h>
#include <stdio.h>

const int sampleRate = 44100;
const int timeSpan = 10;
const int NUMPTS = sampleRate * timeSpan;
short int clpData[NUMPTS];

#define SOUNDBUFF 65536;
#pragma comment(lib,"winmm.lib")//this will make the linker links 
//with this library
WAVEFORMATEX wf;
WAVEHDR whdr;
HWAVEIN hWaveIn;
HWAVEOUT hWaveOut;

int main(void)
{
    
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 2;
    wf.nSamplesPerSec = 44100;
    wf.wBitsPerSample = 16;
    wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
    wf.nAvgBytesPerSec = wf.nBlockAlign * wf.nSamplesPerSec;
    wf.cbSize = 0;
    waveInOpen((LPHWAVEIN)&hWaveIn, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL);

    whdr.lpData = (LPSTR)clpData;
    whdr.dwBufferLength = NUMPTS * 2;
    whdr.dwBytesRecorded = 0;
    whdr.dwFlags = 0L;
    whdr.dwLoops = 0L;
    waveInPrepareHeader(hWaveIn, &whdr, sizeof(whdr));
    waveInAddBuffer(hWaveIn, &whdr, sizeof(whdr));
    waveInStart(hWaveIn);

    do {
    } while (!(whdr.dwFlags & WHDR_DONE));
    waveInUnprepareHeader((HWAVEIN)hWaveOut, &whdr, sizeof(whdr));
    waveInClose(hWaveIn);
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL);
    waveOutPrepareHeader(hWaveOut, &whdr, sizeof(whdr));
    waveOutWrite(hWaveOut, &whdr, sizeof(whdr));

    do {
    } while (!(whdr.dwFlags & WHDR_DONE));
    waveOutUnprepareHeader(hWaveOut, &whdr, sizeof(whdr));
    waveOutClose(hWaveOut);
    return 0;

}