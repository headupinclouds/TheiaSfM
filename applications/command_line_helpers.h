// Copyright (C) 2015 The Regents of the University of California (Regents).
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//
//     * Neither the name of The Regents or University of California nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Please contact the author of this library if you have any questions.
// Author: Chris Sweeney (cmsweeney@cs.ucsb.edu)

#ifndef APPLICATIONS_COMMAND_LINE_HELPERS_H_
#define APPLICATIONS_COMMAND_LINE_HELPERS_H_

#include <glog/logging.h>
#include <gflags/gflags.h>
#include <theia/theia.h>

#include <string>

using theia::DescriptorExtractorType;
using theia::GlobalPositionEstimatorType;
using theia::GlobalRotationEstimatorType;
using theia::MatchingStrategy;
using theia::OptimizeIntrinsicsType;
using theia::ReconstructionEstimatorType;

inline DescriptorExtractorType StringToDescriptorExtractorType(
    const std::string& descriptor) {
  if (descriptor == "SIFT") {
    return DescriptorExtractorType::SIFT;
  } else {
    LOG(FATAL) << "Invalid DescriptorExtractor specified. Using SIFT instead.";
    return DescriptorExtractorType::SIFT;
  }
}

inline MatchingStrategy StringToMatchingStrategyType(
    const std::string& matching_strategy) {
  if (matching_strategy == "BRUTE_FORCE") {
    return MatchingStrategy::BRUTE_FORCE;
  } else if (matching_strategy == "CASCADE_HASHING") {
    return MatchingStrategy::CASCADE_HASHING;
  } else {
    LOG(FATAL)
        << "Invalid matching strategy specified. Using BRUTE_FORCE instead.";
    return MatchingStrategy::BRUTE_FORCE;
  }
}

inline ReconstructionEstimatorType StringToReconstructionEstimatorType(
    const std::string& reconstruction_estimator) {
  if (reconstruction_estimator == "GLOBAL") {
    return ReconstructionEstimatorType::GLOBAL;
  } else if (reconstruction_estimator == "INCREMENTAL") {
    return ReconstructionEstimatorType::INCREMENTAL;
  } else {
    LOG(FATAL)
        << "Invalid reconstruction estimator type. Using GLOBAL instead.";
    return ReconstructionEstimatorType::GLOBAL;
  }
}

inline GlobalRotationEstimatorType StringToRotationEstimatorType(
    const std::string& rotation_estimator) {
  if (rotation_estimator == "ROBUST_L1L2") {
    return GlobalRotationEstimatorType::ROBUST_L1L2;
  } else if (rotation_estimator == "NONLINEAR") {
    return GlobalRotationEstimatorType::NONLINEAR;
  } else if (rotation_estimator == "LINEAR") {
    return GlobalRotationEstimatorType::LINEAR;
  } else {
    LOG(FATAL)
        << "Invalid rotation estimator type. Using ROBUST_L1L2 instead.";
    return GlobalRotationEstimatorType::ROBUST_L1L2;
  }
}

inline GlobalPositionEstimatorType StringToPositionEstimatorType(
    const std::string& position_estimator) {
  if (position_estimator == "NONLINEAR") {
    return GlobalPositionEstimatorType::NONLINEAR;
  } else if (position_estimator == "LINEAR") {
    return GlobalPositionEstimatorType::LINEAR_TRIPLET;
  } else if (position_estimator == "LEAST_UNSQUARED_DEVIATION") {
    return GlobalPositionEstimatorType::LEAST_UNSQUARED_DEVIATION;
  } else {
    LOG(FATAL)
        << "Invalid position estimator type. Using NONLINEAR instead.";
    return GlobalPositionEstimatorType::NONLINEAR;
  }
}

inline OptimizeIntrinsicsType StringToOptimizeIntrinsicsType(
    const std::string& intrinsics_to_optimize) {
  if (intrinsics_to_optimize == "NONE") {
    return OptimizeIntrinsicsType::NONE;
  } else if (intrinsics_to_optimize == "ALL") {
    return OptimizeIntrinsicsType::ALL;
  } else if (intrinsics_to_optimize == "FOCAL_LENGTH") {
    return OptimizeIntrinsicsType::FOCAL_LENGTH;
  } else if (intrinsics_to_optimize == "FOCAL_LENGTH_AND_PRINCIPAL_POINTS") {
    return OptimizeIntrinsicsType::FOCAL_LENGTH_AND_PRINCIPAL_POINTS;
  } else if (intrinsics_to_optimize == "FOCAL_LENGTH_AND_RADIAL_DISTORTION") {
    return OptimizeIntrinsicsType::FOCAL_LENGTH_AND_RADIAL_DISTORTION;
  } else if (intrinsics_to_optimize ==
             "FOCAL_LENGTH_PRINCIPAL_POINTS_AND_RADIAL_DISTORTION") {
    return OptimizeIntrinsicsType::
        FOCAL_LENGTH_PRINCIPAL_POINTS_AND_RADIAL_DISTORTION;
  } else {
    LOG(FATAL) << "Invalid option for intrinsics_to_optimize";
  }
}

#endif  // APPLICATIONS_COMMAND_LINE_HELPERS_H_
