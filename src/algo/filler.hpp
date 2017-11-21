#pragma once

#include "../isalgorithm.hpp"

#include <vector>
#include <set>
#include <list>
#include <map>

#include "../locality.hpp"
#include "../machine_range.hpp"

class Workload;
class SchedulingDecision;

class Filler : public ISchedulingAlgorithm
{
public:
    Filler(Workload * workload, SchedulingDecision * decision, Queue * queue, ResourceSelector * selector,
           double rjms_delay, rapidjson::Document * variant_options);

    virtual ~Filler();

    virtual void on_simulation_start(double date, const rapidjson::Value & batsim_config);

    virtual void on_simulation_end(double date);

    virtual void make_decisions(double date,
                                SortableJobOrder::UpdateInformation * update_info,
                                SortableJobOrder::CompareInformation * compare_info);
private:
    void fill(double date);

private:
    double fraction_of_machines_to_use = 1; //! In ]0,1]. If job requests 42 machines, the scheduler will allocate ceil(42*rho) machines.
    bool set_job_metadata = false; //! If set to true, metadata will be associated to jobs when they are started.

    MachineRange available_machines;
    std::map<std::string, MachineRange> current_allocations;
    bool _debug = true;
};
