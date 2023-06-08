import numpy as np
import tensorflow as tf

from tensorflow.python.framework import ops
from tensorflow.python.ops import array_ops
from tensorflow.python.ops import sparse_ops

addOpModule = tf.load_op_library('./libAddOp.so')

@ops.RegisterGradient("AddOp")
def _add_op_grad(op, grad):
    # This implementation is currently wrong and does not work!!!
    add_op = op.inputs[0]
    shape = array_ops.shape(add_op)
    index = array_ops.zeros_like(shape)
    first_grad = array_ops.reshape(grad, [-1])[0]
    add_op_grad = sparse_ops.sparse_to_dense([index], shape, first_grad, 0)
    return [add_op_grad]  # List of one Tensor, since we have one input

@tf.function
def add_fnc(a):
    return addOpModule.add_op(a)

@tf.function
def custom_loss(x, y):
    return (add_fnc(x) - y)**2
    # return (x - y)**2

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
    [i * 1.0 for i in range(0,100)], 
    [i * 1.0 + 1.0 for i in range(0,100)], 
    epochs=10)

print(model.predict([2.0, 3.0]))