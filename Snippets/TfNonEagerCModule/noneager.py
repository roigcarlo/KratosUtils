import tensorflow as tf
import numpy as np

import NonEager

# @tf.function
def add_fnc(a):
    result = []
    for i in a.numpy():
        r = NonEager.Foo.Add(i)
        result.append(r)
    return tf.convert_to_tensor(result)

# @tf.function
def custom_loss(x, y):
    return (add_fnc(x) - y)**2

model = tf.keras.Sequential(
    [
        tf.keras.Input(shape=(1)),
        tf.keras.layers.Dense(1, activation='linear')
    ]
)

model.compile(
    optimizer=tf.keras.optimizers.Adam(learning_rate=0.001),
    loss=custom_loss,
    metrics=[tf.keras.metrics.AUC(name='auc')],
    run_eagerly=True
)

model.fit(
    [i * 1.0 for i in range(0,10000)], 
    [i * 1.0 + 1.0 for i in range(0,10000)], 
    epochs=200)

print(model.predict([2.0, 6.0]))