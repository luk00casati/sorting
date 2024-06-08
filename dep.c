/* DEPRECATED
void quickSortStepIterative(int *array, int arraysize, int low, int high) {
  int stack[high - low + 1];
  int top = -1;

  stack[++top] = low;
  stack[++top] = high;

#ifdef AUDIO
  InitAudioDevice(); // Initialize audio device

  SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

  // Init raw audio stream (sample rate: 44100, sample size: 16bit-short,
  // channels: 1-mono)
  AudioStream stream = LoadAudioStream(44100, 16, 1);

  SetAudioStreamVolume(stream, volume);

  SetAudioStreamCallback(stream, AudioInputCallback);

  // Buffer for the single cycle waveform we are synthesizing
  short *data = (short *)malloc(sizeof(short) * MAX_SAMPLES);

  // Frame buffer, describing the waveform when repeated over the course of a
  // frame
  short *writeBuf = (short *)malloc(sizeof(short) * MAX_SAMPLES_PER_UPDATE);

  PlayAudioStream(stream);
#endif

  while (top >= 0) {
    high = stack[top--];
    low = stack[top--];

    int p = partition(array, low, high);

    if (p - 1 > low) {
      stack[++top] = low;
      stack[++top] = p - 1;
    }

    if (p + 1 < high) {
      stack[++top] = p + 1;
      stack[++top] = high;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < arraysize + 1; i++) {
      int rectHeight = (array[i] * GetScreenHeight()) / arraysize;
      DrawRectangle(i, GetScreenHeight() - rectHeight, 1, rectHeight, RED);
    }
    // DrawRectangle(stack[top], GetScreenHeight() - (stack[top] *
    // GetScreenHeight() / arraysize), 1, stack[top] * GetScreenHeight() /
    // arraysize, GREEN);
    EndDrawing();

#ifdef AUDIO
    frequency = 440.0f + (float)stack[top];
    if (frequency != oldFrequency) {
      changefrequecy(data);
      oldFrequency = frequency;
    }
#endif
    if (WindowShouldClose())
      return;
  }
#ifdef AUDIO
  StopAudioStream(stream);
  UnloadAudioStream(
      stream); // Close raw audio stream and delete buffers from RAM
  CloseAudioDevice();
  free(data);
  free(writeBuf);
#endif
  sleep(1);
  return;
}
*/

// audio
#ifdef AUDIO
#define MAX_SAMPLES 512
#define MAX_SAMPLES_PER_UPDATE 4096

// Cycles per second (hz)
float frequency = 440.0f;

// Audio frequency, for smoothing
float audioFrequency = 440.0f;

// Previous value, used to test if sine needs to be rewritten, and to smoothly
// modulate frequency
float oldFrequency = 1.0f;

// Index for audio rendering
float sineIdx = 0.0f;

// Computed size in samples of the sine wave
int waveLength = 1;

float volume = 0.3f;

// Audio input processing callback
void AudioInputCallback(void *buffer, unsigned int frames) {
  audioFrequency = frequency + (audioFrequency - frequency) * 0.95f;

  float incr = audioFrequency / 44100.0f;
  short *d = (short *)buffer;

  for (unsigned int i = 0; i < frames; i++) {
    d[i] = (short)(32000.0f * sinf(2 * PI * sineIdx));
    sineIdx += incr;
    if (sineIdx > 1.0f)
      sineIdx -= 1.0f;
  }
}

void changefrequecy(short *data) {
  // Compute wavelength. Limit size in both directions.
  // int oldWavelength = waveLength;
  waveLength = (int)(22050 / frequency);
  if (waveLength > MAX_SAMPLES / 2)
    waveLength = MAX_SAMPLES / 2;
  if (waveLength < 1)
    waveLength = 1;

  // Write sine wave
  for (int i = 0; i < waveLength * 2; i++) {
    data[i] = (short)(sinf(((2 * PI * (float)i / waveLength))) * 32000);
  }
  // Make sure the rest of the line is flat
  for (int j = waveLength * 2; j < MAX_SAMPLES; j++) {
    data[j] = (short)0;
  }

  // Scale read cursor's position to minimize transition artifacts
  // readCursor = (int)(readCursor * ((float)waveLength /
  // (float)oldWavelength));
}
#endif