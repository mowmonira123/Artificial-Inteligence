# -*- coding: utf-8 -*-
"""neural_network_classifier.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1baRfl7REfZl64IbcHfDufsYO-taOxk8V

Name: Mohammad BakiBillah Chowdhuryy
id: 2017-2-60-146

Name: Kamarum Monira Mow
id : 2018-1-60-016
"""

import pandas as pd
import numpy as np
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import train_test_split

data = pd.read_csv('/content/covid_early_stage_symptoms.csv')
data.head()

features = data.columns
features

features = [x for x in features if x!= 'SARS-CoV-2 Positive']
features

train, test = train_test_split(data, test_size=0.25)
print(len(data))
print(len(train))
print(len(test))

mlp = MLPClassifier(hidden_layer_sizes=(30,30,30), max_iter=1500, activation='logistic', learning_rate_init=0.01)

x_train =train[features]
y_train = train['SARS-CoV-2 Positive']

x_test = test[features]
y_test = test['SARS-CoV-2 Positive']

mlp=mlp.fit(x_train, y_train)

y_pred=mlp.predict(x_test)

y_pred

from sklearn.metrics import accuracy_score

score = accuracy_score(y_test, y_pred)*100

print(round(score,1))

"89.9"