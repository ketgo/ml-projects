# BirdCLEF 2021 - Bird Call Identification

Birds of a feather flock together. Thankfully, this makes it easier to hear them! There are over 10,000 bird species around the world. Identifying the red-winged blackbirds or Bewick’s wrens in an area, for example, can provide important information about the habitat. As birds are high up in the food chain, they are excellent indicators of deteriorating environmental quality and pollution. Monitoring the status and trends of biodiversity in ecosystems is no small task. With proper sound detection and classification—aided by machine learning—researchers can improve their ability to track the status and trends of biodiversity in important ecosystems, enabling them to better support global conservation efforts.

Recent advances in machine listening have improved acoustic data collection. However, it remains a challenge to generate analysis outputs with high precision and recall. The majority of data is unexamined due to a lack of effective tools for efficient and reliable extraction of the signals of interests (e.g., bird calls).

The Cornell Lab of Ornithology is dedicated to advancing the understanding and protection of birds and the natural world. The Lab joins with people from all walks of life to make new scientific discoveries, share insights, and galvanize conservation action. For this competition, they're collaborating with Google Research, LifeCLEF, and Xeno-canto.

In this competition, you’ll automate the acoustic identification of birds in soundscape recordings. You'll examine an acoustic dataset to build detectors and classifiers to extract the signals of interest (bird calls). Innovative solutions will be able to do so efficiently and reliably.

The ornithology community is collecting many petabytes of acoustic data every year, but the majority of data remains unexamined. If successful, you'll help researchers properly detect and classify bird sounds, significantly improving their ability to monitor the status and trends of biodiversity in important ecosystems. Researchers will better be able to infer factors about an area’s quality of life based on a changing bird population, which allows them to identify how they can best support global conservation efforts.

The LifeCLEF Bird Recognition Challenge (BirdCLEF) focuses on developing machine learning algorithms to identify avian vocalizations in continuous soundscape data to aid conservation efforts worldwide. Launched in 2014, it has become one of the largest bird sound recognition competitions in terms of dataset size and species diversity.

## Evaluation

Submissions will be evaluated based on their row-wise micro averaged F1 score.

For each row_id/time window, you need to provide a space delimited list of the set of unique birds that made a call beginning or ending in that time window. If there are no bird calls in a time window, use the code nocall.

The submission file must have a header and should look like the following:

### Submission File

```
row_id,birds
3575_COL_5,wewpew batpig1
3575_COL_10,wewpew batpig1
3575_COL_15,wewpew batpig1
...
```

### Working Note Award Criteria (optional)

Criteria for the BirdCLEF best working note award:

Originality. The value of a paper is a function of the degree to which it presents new or novel technical material. Does the paper present results previously unknown? Does it push forward the frontiers of knowledge? Does it present new methods for solving old problems or new viewpoints on old problems? Or, on the other hand, is it a re-hash of information already known?

Quality. A paper's value is a function of the innate character or degree of excellence of the work described. Was the work performed, or the study made with a high degree of thoroughness? Was high engineering skill demonstrated? Is an experiment described which has a high degree of elegance? Or, on the other hand, is the work described pretty much of a run-of-the-mill nature?

Contribution. The value of a paper is a function of the degree to which it represents an overall contribution to the advancement of the art. This is different from originality. A paper may be highly original but may be concerned with a very minor, or even insignificant, matter or problem. On the other hand, a paper may make a great contribution by collecting and analyzing known data and facts and pointing out their significance. Or, a fine exposition of a known but obscure or complex phenomenon or theory or system or operating technique may be a very real contribution to the art. Obviously, a paper may well score highly on both originality and contribution. Perhaps a significant question is, will the engineer who reads the paper be able to practice his profession more effectively because of having read it?

Presentation. The value of the paper is a function of the ease with which the reader can determine what the author is trying to present. Regardless of the other criteria, a paper is not good unless the material is presented clearly and effectively. Is the paper well written? Is the meaning of the author clear? Are the tables, charts, and figures clear? Is their meaning readily apparent? Is the information presented in the paper complete? At the same time, is the paper concise?

Evaluation of the submitted BirdCLEF working notes:

Each working note will be reviewed by two reviewers and scores averaged. Maximum score: 15.

a) Evaluation of work and contribution

    5 points: Excellent work and a major contribution
    4 points: Good solid work of some importance
    3 points: Solid work but a marginal contribution
    2 points: Marginal work and minor contribution
    1 point: Work doesn't meet scientific standards

b) Originality and novelty

    5 points Trailblazing
    4 points: A pioneering piece of work
    3 points: One step ahead of the pack
    2 points: Yet another paper about…
    1 point: It's been said many times before

c) Readability and organization

    5 points: Excellent
    4 points: Well written
    3 points: Readable
    2 points: Needs considerable work
    1 point: Work doesn't meet scientific standards

## Data

Your challenge in this competition is to identify which birds are calling in long recordings, given training data generated in meaningfully different contexts. This is the exact problem facing scientists trying to automate the remote monitoring of bird populations. This competition builds on the previous one by adding soundscapes from new locations, more bird species, richer metadata about the test set recordings, and soundscapes to the train set.

### Files

__train_short_audio__ - The bulk of the training data consists of short recordings of individual bird calls generously uploaded by users of xenocanto.org. These files have been downsampled to 32 kHz where applicable to match the test set audio and converted to the ogg format. The training data should have nearly all relevant files; we expect there is no benefit to looking for more on xenocanto.org.

__train_soundscapes__ - Audio files that are quite comparable to the test set. They are all roughly ten minutes long and in the ogg format. The test set also has soundscapes from the two recording locations represented here.

__test_soundscapes__ - When you submit a notebook, the test_soundscapes directory will be populated with approximately 80 recordings to be used for scoring. These will be roughly 10 minutes long and in ogg audio format. The file names include the date the recording was taken, which can be especially useful for identifying migratory birds.

This folder also contains text files with the name and approximate coordinates of the recording location plus a csv with the set of dates the test set soundscapes were recorded.

__test.csv__ - Only the first three rows are available for download; the full test.csv is in the hidden test set.

- `row_id`: ID code for the row.
- `site`: Site ID.
- `seconds`: the second ending the time window
- `audio_id`: ID code for the audio file.

__train_metadata.csv__ - A wide range of metadata is provided for the training data. The most directly relevant fields are:

- `primary_label`: a code for the bird species. You can review detailed information about the bird codes by appending the code to https://ebird.org/species/, such as https://ebird.org/species/amecro for the American Crow.
- `recodist`: the user who provided the recording.
- `latitude` & `longitude`: coordinates for where the recording was taken. Some bird species may have local call 'dialects,' so you may want to seek geographic diversity in your training data.
- `date`: while some bird calls can be made year round, such as an alarm call, some are restricted to a specific season. You may want to seek temporal diversity in your training data.
- `filename`: the name of the associated audio file.

__train_soundscape_labels.csv__ -

- `row_id`: ID code for the row.
- `site`: Site ID.
- `seconds`: the second ending the time window
- `audio_id`: ID code for the audio file.
- `birds`: space delimited list of any bird songs present in the 5 second window. The label nocall means that no call occurred.

__sample_submission.csv__ - A properly formed sample submission file. Only the first three rows are public, the remainder will be provided to your notebook as part of the hidden test set.

- `row_id`: ID code for the row.
- `birds`: space delimited list of any bird songs present in the 5 second window. If there are no bird calls, use the label nocall.

