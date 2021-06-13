"""
    Data loader module
"""

import os.path

import swifter
import numpy as np
import pandas as pd
import librosa
import glob
import re

METADATA_COLUMNS = [
    "primary_label", 
    "latitude", 
    "longitude", 
    "date", 
    "time", 
    "rating", 
    "filename", 
    "common_name", 
    "scientific_name"
]


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

    files = glob.glob(file_path)
    if not files:
        raise FileNotFoundError()
    name = files[0]

    return extract_date(name), load_ogg(name, sr, **kwargs)


def load_metadata(data_path, nrows=None, col=METADATA_COLUMNS, audio_duration=True):
    """
        Load metadata.

        :param data_path: path to the data folder
        :param nrows: number of rows to load
        :param col: columns to load
        :param audio_duration: load associated audio file dutation
    """
    df = pd.read_csv(data_path + "/train_metadata.csv", nrows=nrows)
    df = df [col]
    df[["year", "month", "day"]] = df["date"].str.split('-', expand=True)
    
    return df


def load_labels(data_path, nrows=None):
    """
        Load labels.

        :param data_path: path to the data folder
        :param nrows: number of rows to load
    """
    df = pd.read_csv(data_path + "/train_soundscape_labels.csv", nrows=nrows)

    return df


def load_audio_duration(row):
    """
        Get audio duration.
    """
    y = load_short_audio(row["primary_label"], row["filename"], DATA_PATH + '/train_short_audio', SAMPLE_RATE)
    if y is not None:
        return librosa.get_duration(y=y, sr=SAMPLE_RATE)
    return 0
