"""
    Postprocessing data module
"""

import numpy as np
import librosa

DEFAULT_NORM_ENERGY = 100
DEFAULT_N_MEL = 200


def normalize(signal, eng_norm=DEFAULT_NORM_ENERGY):
    """
        Normalize audio signal.
        
        :param signal: audio signal as 1D numpy array
        :param eng_norm: normalization energy value
        :returns: 1D numpy array
    """
    return signal * np.sqrt(eng_norm / np.sum(signal * signal))


def get_mel_spec(signal, **kwargs):
    """
        Get Mel spectogram for given audio signal
        
        :param signal: audio signal as 1D numpy array
        :param **kwargs: other arguments
        
        :returns: 2D numpy array
    """
    mel_spec = librosa.feature.melspectrogram(y=signal, **kwargs)
    
    return mel_spec
