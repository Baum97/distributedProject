#include <stdlib.h>
#include <check.h>
#include "memora.h"

void* connection;

void setup(void) {
    connection = memora_connect("127.0.0.1", 5000);
}

void teardown(void) {
    memora_close(connection);
}

START_TEST(test_create_read_delete) {
    int rc = memora_create(connection, "foo", "bar");
    ck_assert_int_eq(rc, 0);

    char* value = memora_read(connection, "foo");
    ck_assert_str_eq(value, "bar");
    free(value);

    rc = memora_delete(connection, "foo");
    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite* memora_suite(void) {
    Suite* s = suite_create("Memora");

    TCase* tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_create_read_delete);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite* s = memora_suite();
    SRunner* sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
