#pragma once

#include <memory>

#include "sample_publisher.h"
#include "types.h"

class Costas {
public:
  explicit Costas();

  // Set maximum frequency deviation in radians per sample.
  void setMaxDeviation(float maxDeviation) {
    maxDeviation_ = maxDeviation;
  }

  void setSamplePublisher(std::unique_ptr<SamplePublisher> samplePublisher) {
    samplePublisher_ = std::move(samplePublisher);
  }

  // Set modulation order (2 == BPSK, 4 == QPSK)
  void setModOrder(int modOrder) {
    modOrder_ = modOrder;
  }

  // Returns frequency in radians per sample.
  float getFrequency() const {
    return freq_;
  }

  void work(
      const std::shared_ptr<Queue<Samples> >& qin,
      const std::shared_ptr<Queue<Samples> >& qout);

protected:
  void work(
      size_t nsamples,
      std::complex<float>* fi,
      std::complex<float>* fo);

  float phase_;
  float freq_;
  float alpha_;
  float beta_;
  float maxDeviation_;
  int modOrder_;

  std::unique_ptr<SamplePublisher> samplePublisher_;
};
