#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>
#include <memora_server.h>

START_TEST(test_create_record)
{
    create_record("key1", "value1");
    char *value = read_record("key1");
    ck_assert_str_eq(value, "value1");
    free(value);
}
END_TEST

START_TEST(test_read_record)
{
    create_record("key2", "value2");
    char *value = read_record("key2");
    ck_assert_str_eq(value, "value2");
    free(value);
}
END_TEST

START_TEST(test_update_record)
{
    create_record("key3", "value3");
    update_record("key3", "new_value");
    char *value = read_record("key3");
    ck_assert_str_eq(value, "new_value");
    free(value);
}
END_TEST

START_TEST(test_delete_record)
{
    create_record("key4", "value4");
    delete_record("key4");
    char *value = read_record("key4");
    ck_assert_ptr_eq(value, NULL);
}
END_TEST

// Create the test suites
Suite *create_suite(void)
{
    Suite *suite = suite_create("MemoraDB Tests");

    TCase *create_record_case = tcase_create("Create Record");
    tcase_add_test(create_record_case, test_create_record);
    suite_add_tcase(suite, create_record_case);

    TCase *read_record_case = tcase_create("Read Record");
    tcase_add_test(read_record_case, test_read_record);
    suite_add_tcase(suite, read_record_case);

    TCase *update_record_case = tcase_create("Update Record");
    tcase_add_test(update_record_case, test_update_record);
    suite_add_tcase(suite, update_record_case);

    TCase *delete_record_case = tcase_create("Delete Record");
    tcase_add_test(delete_record_case, test_delete_record);
    suite_add_tcase(suite, delete_record_case);

    return suite;
}

// Run the test suite
int main(void)
{
    int number_failed;
    Suite *suite = create_suite();
    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}







