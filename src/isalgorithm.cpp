#include "isalgorithm.hpp"

#include "pempek_assert.hpp"

using namespace std;

void ISchedulingAlgorithm::set_nb_machines(int nb_machines)
{
    PPK_ASSERT_ERROR(_nb_machines == -1);
    _nb_machines = nb_machines;
}

void ISchedulingAlgorithm::set_redis(RedisStorage *redis)
{
    PPK_ASSERT_ERROR(_redis == nullptr);
    _redis = redis;
}

void ISchedulingAlgorithm::clear_recent_data_structures()
{
    _jobs_released_recently.clear();
    _jobs_ended_recently.clear();
    _jobs_killed_recently.clear();
    _machines_whose_pstate_changed_recently.clear();
    _recent_failstate_changes.clear();
    _nopped_recently = false;
}

ISchedulingAlgorithm::ISchedulingAlgorithm(Workload *workload,
                                           SchedulingDecision *decision,
                                           Queue *queue,
                                           ResourceSelector *selector,
                                           double rjms_delay,
                                           rapidjson::Document *variant_options) :
    _workload(workload), _decision(decision), _queue(queue), _selector(selector),
    _rjms_delay(rjms_delay), _variant_options(variant_options)
{

}

void ISchedulingAlgorithm::on_job_release(double date, const vector<string> &job_ids)
{
    (void) date;
    _jobs_released_recently.insert(_jobs_released_recently.end(),
                                   job_ids.begin(),
                                   job_ids.end());
}

void ISchedulingAlgorithm::on_job_end(double date, const vector<string> &job_ids)
{
    (void) date;
    _jobs_ended_recently.insert(_jobs_ended_recently.end(),
                                job_ids.begin(),
                                job_ids.end());
}

void ISchedulingAlgorithm::on_job_killed(double date, const std::vector<string> &job_ids)
{
    (void) date;
    _jobs_killed_recently.insert(_jobs_killed_recently.end(),
                                 job_ids.begin(),
                                 job_ids.end());
}

void ISchedulingAlgorithm::on_machine_state_changed(double date, MachineRange machines, int new_state)
{
    (void) date;

    if (_machines_whose_pstate_changed_recently.count(new_state) == 0)
        _machines_whose_pstate_changed_recently[new_state] = machines;
    else
        _machines_whose_pstate_changed_recently[new_state] += machines;
}

void ISchedulingAlgorithm::on_failure(double date, MachineRange machines)
{
    (void) date;
    _recent_failstate_changes.push_back(Failure(date, machines, true));
}

void ISchedulingAlgorithm::on_failure_end(double date, MachineRange machines)
{
    (void) date;
    _recent_failstate_changes.push_back(Failure(date, machines, false));
}

void ISchedulingAlgorithm::on_nop(double date)
{
    (void) date;
    _nopped_recently = true;
}

ISchedulingAlgorithm::Failure::Failure(double date, MachineRange machines, bool failed) :
    date(date),
    machines(machines),
    failed(failed)
{

}
