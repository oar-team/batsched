#include "scenario.hpp"

// Shared by the first two scenarios: 4 machines and intensity 100 until 20,
// then 1, so a 2-node job released at 0 is displaced to 20 and holds nodes 0-1
// idle until then. Behind it, a 3-node job cannot run before 30: nodes 2-3 are
// too few, and from 20 the displaced job uses 0-1 until 30. A 2-node job that
// runs for 50 fits now on nodes 2-3 and would still be running at 30.
static const std::vector<double> CLEAN_FROM_20 = { 100, 100, 1 };

static void backfill_mode_lets_a_later_job_overtake_the_blocked_head()
{
    GreenWindowScenario scenario(4, CLEAN_FROM_20, 20, 0, "backfill");
    scenario.add_job("a_displaced", 2, 10);
    scenario.add_job("b_wide", 3, 10);
    scenario.add_job("c_long", 2, 50);
    scenario.dispatch(0, { "a_displaced", "b_wide", "c_long" });
    scenario.expect_started({ "c_long" });
}

static void easy_mode_reserves_the_blocked_head_after_the_displaced_job()
{
    GreenWindowScenario scenario(4, CLEAN_FROM_20, 20, 0, "easy");
    scenario.add_job("a_displaced", 2, 10);
    scenario.add_job("b_wide", 3, 10);
    scenario.add_job("c_long", 2, 50);
    scenario.dispatch(0, { "a_displaced", "b_wide", "c_long" });
    scenario.expect_started({});
    scenario.expect_callback(20);
    require_green_window(GreenWindowSchedulingTestAccess::contention_start(*scenario.scheduler) == 30,
        "Expected b_wide reserved at 30, after the displaced job, not on the held nodes before 20");

    scenario.dispatch(20, {}, {}, true);
    scenario.expect_started({ "a_displaced" });
    scenario.dispatch(30, {}, { "a_displaced" });
    scenario.expect_started({ "b_wide" });
}

// Under a flat trace, a_short takes nodes 0-1 until 1 and b_running nodes 2-3
// until 5. Then the trace changes, and a 2-node job released at 1 is displaced
// to 20. Every node is free at 20, so its window, and its hold, is on nodes 0-1.
// The 2-node head behind it can use nodes 2-3 from 5, before the displaced start.
static void easy_mode_reserves_outside_the_held_nodes_before_the_displaced_start()
{
    GreenWindowScenario scenario(4, { 100 }, 20, 0, "easy");
    scenario.add_job("a_short", 2, 1);
    scenario.add_job("b_running", 2, 5);
    scenario.dispatch(0, { "a_short", "b_running" });
    scenario.expect_started({ "a_short", "b_running" });

    scenario.trace->values = CLEAN_FROM_20;
    scenario.add_job("c_displaced", 2, 10, 1);
    scenario.add_job("d_head", 2, 10, 1);
    scenario.dispatch(1, { "c_displaced", "d_head" }, { "a_short" });
    scenario.expect_started({});
    scenario.expect_callback(20);
    require_green_window(GreenWindowSchedulingTestAccess::contention_start(*scenario.scheduler) == 5,
        "Expected d_head reserved at 5 on the nodes outside the hold");

    scenario.dispatch(5, {}, { "b_running" });
    scenario.expect_started({ "d_head" });
    require_green_window(scenario.allocated_nodes("d_head") == "2-3", "Expected d_head on nodes 2-3");
}

void test_heads_behind_displacement_regressions()
{
    backfill_mode_lets_a_later_job_overtake_the_blocked_head();
    easy_mode_reserves_the_blocked_head_after_the_displaced_job();
    easy_mode_reserves_outside_the_held_nodes_before_the_displaced_start();
}
