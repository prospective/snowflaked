#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <assert.h>
#include "../src/snowflake.h"
#include "../src/stats.h"

START_TEST(test_pools_empty) {
    int test = snowflake_init(0, 10);
    ck_assert_msg(test == 1, "Snowflake failed to init");
    ck_assert_msg(snowflake_global_state.region_id == 10L, "Region ID initialized incorrectly in the global state");
    ck_assert_msg(snowflake_global_state.worker_id == 10L, "Worker ID initialized incorrectly in the global state");
    ck_assert_msg(snowflake_global_state.seq_max == (1L << SNOWFLAKE_SEQUENCE_BITS) - 1, "Sequence Max initialized incorrectly in the global state");
    ck_assert_msg(snowflake_global_state.seq == 0L, "Sequence number initialized incorrectly in the global state");
    ck_assert_msg(snowflake_global_state.time == 0L, "Time initialized incorrectly in the global state");
    ck_assert_msg(app_stats.seq_cap == snowflake_global_state.seq_max, "app_stats.seq_cap != snowflake_global_state.seq_max");
    ck_assert_msg(app_stats.waits == 0L, "Waits counter not initialized correctly");
    ck_assert_msg(app_stats.seq_max == 0L, "Max generated sequence number not initialized correctly");
    ck_assert_msg(app_stats.ids == 0L, "ID generation counter not initialized correctly");
    ck_assert_msg(app_stats.region_id == snowflake_global_state.region_id, "app_stats.region_id != snowflake_global_state.region_id");
    ck_assert_msg(app_stats.worker_id == snowflake_global_state.worker_id, "app_stats.region_id != snowflake_global_state.region_id");
    
}

END_TEST


Suite * snowflake_suite(void) {
    Suite *s = suite_create("Snowflake");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_pools_empty);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s = snowflake_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}