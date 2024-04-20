#!/usr/bin/env python3
import numpy as np
import soundfile as sf

data_n = np.loadtxt("recording.csv")
data_n = data_n / np.max(np.abs(data_n))
sample_rate_hz=44100
sf.write('recording.wav', data_n, sample_rate_hz)