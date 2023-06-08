import numpy as np
import tensorflow as tf

import NonEager

def my_numpy_func(x):
  return np.array(NonEager.Foo.Add(x), np.float32)

@tf.function(input_signature=[tf.TensorSpec(None, tf.float32)])
def tf_function(input):
  y = tf.numpy_function(my_numpy_func, [input], tf.float32)
  return y


@tf.function
def custom_loss(x, y):
    return (tf_function(x) - y)**2

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
    run_eagerly=False
)

model.fit(
    [i * 0.005 for i in range(0,100)], 
    [i * 0.005 for i in range(0,100)],
    batch_size=1,
    epochs=150
)

print(model.predict([0.0015, 0.0025]))