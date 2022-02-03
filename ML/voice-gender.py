import pandas as pd
import numpy as np
import os
import tqdm
from keras.models import Sequential
from keras.layers import Dense, LSTM, Dropout
from keras.callbacks import ModelCheckpoint, TensorBoard, EarlyStopping
from sklearn.model_selection import train_test_split

df = pd.read_csv("voice.csv")
df.head()
