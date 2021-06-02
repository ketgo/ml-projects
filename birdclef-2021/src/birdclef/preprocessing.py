"""
    Preprocessing data module
"""

import swifter

from from birdclef.load_data import get_audio_duration



def attach_audio_duration(metadata_df):
    """
        Attach audio durtation of the short recordings to each row in metadata.
        
        :param metadata_df: metadata dataframe
    """
    metadata_df["audio_duration"] = metadata_df[["primary_label", "filename"]].swifter.apply(get_audio_duration, axis=1)
