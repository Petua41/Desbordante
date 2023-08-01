#pragma once

#include <random>
#include <stack>

#include "algorithms/functional/dfd/partition_storage/partition_storage.h"
#include "algorithms/functional/pli_based_fd_algorithm.h"
#include "config/thread_number/type.h"
#include "model/vertical.h"

namespace algos {

class DFD : public PliBasedFDAlgorithm {
private:
    std::vector<Vertical> unique_columns_;

    config::ThreadNumType number_of_threads_;

    void MakeExecuteOptsAvailable() final;
    void RegisterOptions();

    void ResetStateFd() final;
    unsigned long long ExecuteInternal() final;

public:
    DFD();
};

}  // namespace algos