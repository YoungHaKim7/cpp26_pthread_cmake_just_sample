#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>

// WAV 파일 헤더 구조체
struct WAVHeader {
    char riff[4] = { 'R', 'I', 'F', 'F' };
    uint32_t chunkSize;
    char wave[4] = { 'W', 'A', 'V', 'E' };
    char fmt[4] = { 'f', 'm', 't', ' ' };
    uint32_t subchunk1Size = 16; // PCM
    uint16_t audioFormat = 1; // PCM
    uint16_t numChannels = 1; // 모노
    uint32_t sampleRate = 44100; // 표준 CD 품질
    uint32_t byteRate; // = sampleRate * numChannels * bitsPerSample/8
    uint16_t blockAlign; // = numChannels * bitsPerSample/8
    uint16_t bitsPerSample = 16; // 16비트
    char data[4] = { 'd', 'a', 't', 'a' };
    uint32_t subchunk2Size; // 샘플 데이터 크기
};

int main()
{
    const int duration = 10; // 전체 10초
    const int sampleRate = 44100;
    const int numSamples = duration * sampleRate;
    const int amplitude = 30000; // 최대 진폭(16비트 범위 내)

    // 도, 레, 미, 파, 솔 (Hz)
    double notes[] = { 261.63, 293.66, 329.63, 349.23, 392.00 };
    const int numNotes = sizeof(notes) / sizeof(notes[0]);
    const int samplesPerNote = numSamples / numNotes; // 각 음 길이

    WAVHeader header;
    header.numChannels = 1;
    header.sampleRate = sampleRate;
    header.bitsPerSample = 16;
    header.byteRate = header.sampleRate * header.numChannels * header.bitsPerSample / 8;
    header.blockAlign = header.numChannels * header.bitsPerSample / 8;
    header.subchunk2Size = numSamples * header.numChannels * header.bitsPerSample / 8;
    header.chunkSize = 36 + header.subchunk2Size;

    std::ofstream out("melody.wav", std::ios::binary);
    if (!out) {
        std::cerr << "파일을 열 수 없습니다.\n";
        return 1;
    }

    // 헤더 쓰기
    out.write(reinterpret_cast<const char*>(&header), sizeof(header));

    // 오디오 데이터 생성
    int sampleIndex = 0;
    for (int n = 0; n < numNotes; n++) {
        double freq = notes[n];
        for (int i = 0; i < samplesPerNote; i++, sampleIndex++) {
            double t = static_cast<double>(sampleIndex) / sampleRate;
            int16_t sample = static_cast<int16_t>(
                amplitude * std::sin(2.0 * M_PI * freq * t));
            out.write(reinterpret_cast<const char*>(&sample), sizeof(sample));
        }
    }

    out.close();
    std::cout << "10초짜리 멜로디 (도-레-미-파-솔) melody.wav 파일 생성 완료!\n";
    return 0;
}
