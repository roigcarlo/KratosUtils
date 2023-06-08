# General concepts

## Tracing

Not sure yet

## Grappler 
https://www.tensorflow.org/guide/graph_optimization
https://www.tensorflow.org/api_docs/python/tf/config/optimizer/set_experimental_options

Optimizations
- layout_optimizer: Optimize tensor layouts e.g. This will try to use NCHW layout on GPU which is faster.
- constant_folding: Fold constants Statically infer the value of tensors when possible, and materialize the result using constants.
- shape_optimization: Simplify computations made on shapes.
- remapping: Remap subgraphs onto more efficient implementations.
- arithmetic_optimization: Simplify arithmetic ops with common sub-expression elimination and arithmetic simplification.
- dependency_optimization: Control dependency optimizations. Remove redundant control dependencies, which may enable other - optimization. This optimizer is also essential for pruning Identity and NoOp nodes.
- loop_optimization: Loop optimizations.
- function_optimization: Function optimizations and inlining.
- debug_stripper: Strips debug-related nodes from the graph.
- disable_model_pruning: Disable removal of unnecessary ops from the graph
- scoped_allocator_optimization: Try to allocate some independent Op outputs contiguously in order to merge or eliminate downstream Ops.
- pin_to_host_optimization: Force small ops onto the CPU.
- implementation_selector: Enable the swap of kernel implementations based on the device placement.
- auto_mixed_precision: Change certain float32 ops to float16 on Volta GPUs and above. Without the use of loss scaling, this can cause numerical underflow (see keras.mixed_precision.experimental.LossScaleOptimizer).
- disable_meta_optimizer: Disable the entire meta optimizer.
- min_graph_nodes: The minimum number of nodes in a graph to optimizer. For smaller graphs, optimization is skipped. 

Can be activated and deactivated with:

```python
with options({'constant_folding': False}):
```

## New operations

https://www.tensorflow.org/guide/create_op
