#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/op_kernel.h"

using namespace tensorflow;

REGISTER_OP("AddOp")
    .Input("in:   float")
    .Output("out: float");

class AddOp : public OpKernel {
 public:
  explicit AddOp(OpKernelConstruction* context) : OpKernel(context) {}

  void Compute(OpKernelContext* context) override {

    // Grab the input tensor
    const Tensor& input_tensor = context->input(0);
    auto input = input_tensor.flat<float>();

    // Create an output tensor
    Tensor* output_tensor = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, input_tensor.shape(),
                                                     &output_tensor));
    auto output = output_tensor->template flat<float>();

    // Set all but the first element of the output tensor to 0.
    for (int i = 0; i < input.size(); i++) {
      output(i) += 1;
    }
  }
};

REGISTER_KERNEL_BUILDER(Name("AddOp").Device(DEVICE_CPU), AddOp);