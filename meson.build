project('batsched', 'cpp',
    version: '1.4.0',
    license: 'free',
    default_options: ['cpp_std=c++11'],
    meson_version: '>=0.40.0'
)

# Dependencies
boost_dep = dependency('boost',
    modules : ['locale', 'regex', 'system']
)
rapidjson_dep = dependency('RapidJSON')
libzmq_dep = dependency('libzmq')
loguru_dep = dependency('loguru')
intervalset_dep = dependency('intervalset')
gmpxx_dep = dependency('gmpxx')

batsched_deps = [
    boost_dep,
    rapidjson_dep,
    libzmq_dep,
    loguru_dep,
    intervalset_dep,
    gmpxx_dep
]

# Source files
src = [
    'src/algo/conservative_bf.cpp',
    'src/algo/conservative_bf.hpp',
    'src/algo/crasher.cpp',
    'src/algo/crasher.hpp',
    'src/algo/easy_bf.cpp',
    'src/algo/easy_bf_fast.cpp',
    'src/algo/easy_bf_fast.hpp',
    'src/algo/easy_bf.hpp',
    'src/algo/easy_bf_plot_liquid_load_horizon.cpp',
    'src/algo/easy_bf_plot_liquid_load_horizon.hpp',
    'src/algo/energy_bf.cpp',
    'src/algo/energy_bf_dicho.cpp',
    'src/algo/energy_bf_dicho.hpp',
    'src/algo/energy_bf.hpp',
    'src/algo/energy_bf_idle_sleeper.cpp',
    'src/algo/energy_bf_idle_sleeper.hpp',
    'src/algo/energy_bf_machine_subpart_sleeper.cpp',
    'src/algo/energy_bf_machine_subpart_sleeper.hpp',
    'src/algo/energy_bf_monitoring_inertial_shutdown.cpp',
    'src/algo/energy_bf_monitoring_inertial_shutdown.hpp',
    'src/algo/energy_bf_monitoring_period.cpp',
    'src/algo/energy_bf_monitoring_period.hpp',
    'src/algo/energy_watcher.cpp',
    'src/algo/energy_watcher.hpp',
    'src/algo/fcfs_fast.cpp',
    'src/algo/fcfs_fast.hpp',
    'src/algo/fcfs.cpp',
    'src/algo/fcfs.hpp',
    'src/algo/filler.cpp',
    'src/algo/filler.hpp',
    'src/algo/killer2.cpp',
    'src/algo/killer2.hpp',
    'src/algo/killer.cpp',
    'src/algo/killer.hpp',
    'src/algo/random.cpp',
    'src/algo/random.hpp',
    'src/algo/rejecter.cpp',
    'src/algo/rejecter.hpp',
    'src/algo/sequencer.cpp',
    'src/algo/sequencer.hpp',
    'src/algo/sleeper.cpp',
    'src/algo/sleeper.hpp',
    'src/algo/submitter.cpp',
    'src/algo/submitter.hpp',
    'src/algo/wt_estimator.cpp',
    'src/algo/wt_estimator.hpp',
    'src/decision.cpp',
    'src/decision.hpp',
    'src/exact_numbers.hpp',
    'src/external/taywee_args.hpp',
    'src/isalgorithm.cpp',
    'src/isalgorithm.hpp',
    'src/json_workload.cpp',
    'src/json_workload.hpp',
    'src/locality.cpp',
    'src/locality.hpp',
    'src/main.cpp',
    'src/network.cpp',
    'src/network.hpp',
    'src/pempek_assert.cpp',
    'src/pempek_assert.hpp',
    'src/protocol.cpp',
    'src/protocol.hpp',
    'src/queue.cpp',
    'src/queue.hpp',
    'src/queueing_theory_waiting_time_estimator.cpp',
    'src/queueing_theory_waiting_time_estimator.hpp',
    'src/schedule.cpp',
    'src/schedule.hpp'
]
include_dir = include_directories('src')

batsched = executable('batsched', src,
    include_directories: include_dir,
    dependencies: batsched_deps,
    cpp_args: '-DBATSCHED_VERSION=@0@'.format(meson.project_version()),
    install: true
)
