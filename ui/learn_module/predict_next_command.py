# -*- coding: utf-8 -*-
"""py-version_predict_next_command.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1ZrLaqDHkdXaItD064RVCuI88Z7S4lcy7
"""

import os
import re
import pickle
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Embedding, LSTM, Dense, Bidirectional
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences

from tensorflow.keras.preprocessing.text import tokenizer_from_json
from tensorflow.keras.models import load_model, save_model

import sys
import types
import tensorflow.keras.preprocessing.text as kpt

# Создаем "фиктивный" модуль keras.preprocessing.text
sys.modules['keras.preprocessing.text'] = kpt
sys.modules['keras.src.preprocessing'] = sys.modules['tensorflow.keras.preprocessing']

uploaded_h5_path = "D:\\diploma\\project_m\\cpp_version\\learn_module\\next_commands_end.keras"

# Load the model and tokenizer
model = load_model(uploaded_h5_path)
model.save('next_words.keras')
tokenizer = pickle.load(open(rf'D:\diploma\project_m\cpp_version\learn_module\token.pkl', 'rb'))

expected_text = "OpenDocument LAYOUT_CONTROL CopyWithBasePoint PasteBlock SimplePolyLine"
seed_text = "OpenDocument LAYOUT_CONTROL CopyWithBasePoint PasteBlock"

next_words = 1
output_text = ""
max_sequence_len = 1000 #max([len(x) for x in input_sequences])

for _ in range(next_words):
    token_list = tokenizer.texts_to_sequences([seed_text])[0]
    token_list = pad_sequences([token_list], maxlen=max_sequence_len-1, padding='pre')
    predicted_model = model.predict(token_list, verbose=0)
    predicted_class = np.argmax(predicted_model, axis=-1)
    output_word = ""
    for word, index in tokenizer.word_index.items():
        if index == predicted_class:
            output_word = word
            break
    output_text += " " + output_word

print(output_text)