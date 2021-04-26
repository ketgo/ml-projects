"""
    Data loader module
"""

import os.path
import numpy as np
import librosa
import glob
import re


def load_ogg(path, sr=None, **kwargs):
    """
        Load audio .ogg file for the given item ID
        
        :param fname: file name
        :param path: path to audio files
        :param sr: sample rate of the audio signal
        :param **kwargs: other arguments
        :returns: 1D numpy array
    """
    signal = None
    if os.path.exists(path):
        signal, _ = librosa.load(path, sr=sr, **kwargs)
        
    return signal


def load_short_audio(label, filename, data_path, sr=None, **kwargs):
    """
        Load short audio recording of an individual bird call.
        
        :param label: priamary label of the bird
        :param filename: file name of the audio recording
        :param data_path: path to the data folder 
        :returns: 1D numpy array
    """
    file_path = "{}/{}/{}".format(data_path, label, filename)
    
    return load_ogg(file_path, sr, **kwargs)


def load_soundscape_audio(row_id, data_path, sr=None, **kwargs):
    """
        Load soundscape audio recording.
        
        :param row_id: row ID of the soundscape
        :param data_path: path to the data folder
        :returns: list of tuples containing 1D numpy array and the date the 
            signal was taken. 
    """
    file_path = "{}/{}*".format(data_path, row_id)
    
    def extract_date(file_name):
        m = re.search("([0-9]{2}[0-9]{2}[0-9]{4})", name)
        return m.groups()[0]
    
    for name in glob.glob(file_path):
        yield extract_date(name), load_ogg(name, sr, **kwargs)
