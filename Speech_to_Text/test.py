import os
import librosa   
import IPython.display as ipd
import matplotlib.pyplot as plt
import numpy as np
from scipy.io import wavfile 
import warnings
from tensorflow import keras

os.environ['KERAS_BACKEND']='tensorflow'

from tensorflow.keras.utils import to_categorical
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from tensorflow.keras.layers import Dense, Dropout, Flatten, Conv1D, Input, MaxPooling1D
from tensorflow.keras.models import Model
from tensorflow.keras.callbacks import EarlyStopping, ModelCheckpoint
from tensorflow.keras import backend as K
from matplotlib import pyplot 
from tensorflow.keras.models import load_model
import random
from tensorflow import keras
from tensorflow.keras import layers

warnings.filterwarnings("ignore")



train_audio_path = 'C:\\Users\\Suren\\source\\repos\\ML_1.0\\train\\audio\\on\\'

filepath='C:\\Users\\Suren\\source\\repos\\ML_1.0\\train\\audio\\on\\'

labels=os.listdir(train_audio_path)


model=load_model('best_model.hdf5')

model.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])

def predict(audio):
    prob=model.predict(audio.reshape(1,8000,1))

    return prob



def predict_2(audio):
    prob=model.predict(audio.reshape(1,8000,1))
    index=np.argmax(prob[0])
    return classes[index]

import random
index=random.randint(0,len(x_val)-1)
samples=x_val[index].ravel()
print("Audio:",classes[np.argmax(y_val[index])])
ipd.Audio(samples, rate=8000)
print("Text:",predict(samples))



#reading the voice commands
samples, sample_rate = librosa.load(filepath + '\\' + '00b01445_nohash_0.wav', sr = 16000)
samples = librosa.resample(samples, sample_rate, 8000)
ipd.Audio(samples,rate=8000)  

print(predict(samples))
