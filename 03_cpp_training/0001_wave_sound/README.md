# 외국사람이 만든거
- C++
  - https://github.com/RobertDurfee/Wave

- C
  - wav2c makes arrays out of sounds - useful for Arduino SMAPLER v2 (and for GameBoy Advance) etc
    -  https://github.com/olleolleolle/wav2c

# 좋습니다 🎵 그러면 10초 동안 음이 바뀌는 WAV 파일을 만들어보겠습니다.

- 예를 들어 10초를 5등분해서, 각 2초마다
  - 도 (C4, 261.63Hz)
  - 레 (D4, 293.66Hz)
  - 미 (E4, 329.63Hz)
  - 파 (F4, 349.23Hz)
  - 솔 (G4, 392.00Hz)
- 이 순서대로 재생되도록 하겠습니다.# 



# 1. What is a WAV file?

- WAV is a container format that usually stores uncompressed PCM audio.
- It’s basically a binary file with:
  - 1.  A header (metadata: format, sample rate, bit depth, etc.)
  - 2. The raw audio samples (numbers representing air pressure changes).
- So when your computer plays a WAV, it just reads those samples at the correct rate and sends them to the speakers.

# 2. Structure of a WAV file

- The typical layout looks like this:

```
RIFF Header (12 bytes)
 ├─ "RIFF" (4 bytes)
 ├─ File size - 8 (4 bytes)
 └─ "WAVE" (4 bytes)

fmt Chunk (24 bytes for PCM)
 ├─ "fmt " (4 bytes)
 ├─ Chunk size (16 for PCM)
 ├─ Audio format (1 = PCM)
 ├─ Number of channels (1=mono, 2=stereo)
 ├─ Sample rate (e.g., 44100)
 ├─ Byte rate (SampleRate × Channels × BitsPerSample/8)
 ├─ Block align (Channels × BitsPerSample/8)
 └─ Bits per sample (8, 16, 24…)

data Chunk
 ├─ "data" (4 bytes)
 ├─ Subchunk size (numSamples × Channels × BitsPerSample/8)
 └─ Raw PCM data (the samples)
```

# 3. The audio samples (the “wave”)

- A sample is just a number representing the amplitude of the sound wave at a given instant.
- For example, with 16-bit PCM, each sample is a signed integer between `-32768` and `+32767`.
- If you plot those numbers over time and connect the dots, you get a waveform.
- To make a pure sine wave at frequency `f`:


$$ sample[n] = A \times{sin}\left(2\pi{f}\frac{n}{SampleRate}\right) $$

- Where:
  - A = amplitude (volume)
  - f = frequency (Hz, cycles per second)
  - n = sample index
  - SampleRate = how many samples per second (e.g., 44100)


# 4. Example: 440 Hz A note (sine wave)
- Sample rate: 44100 Hz
- Duration: 1 second
- Frequency: 440 Hz

- So, we generate 44100 numbers with that sine formula, each scaled to fit in a 16-bit signed integer.
Then we write them after the WAV header → and voilà, a playable `.wav` file!

# 5. Why WAV is easy
- It’s just RIFF metadata + raw numbers.
- No compression, so it’s bigger than MP3/OGG, but much simpler to generate manually.
- That’s why we can write a .wav with only ~50 lines of C++ or Rust.
