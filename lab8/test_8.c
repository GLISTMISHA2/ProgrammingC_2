#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "lab8.c"

void test_plus(void **state) {
    assert_int_equal(plus(2,3), 5);
    assert_int_equal(plus(-1,1), 0);
}
void test_min(void **state) {
    assert_int_equal(min(5,3), 2);
    assert_int_equal(min(3,5), -2);
}
void test_ymn(void **state) {
    assert_int_equal(ymn(4,5), 20);
    assert_int_equal(ymn(0,100), 0);
}
void test_del(void **state) {
    assert_float_equal(del(10,2), 5.0, 0.1);
    assert_float_equal(del(5,2), 2.5, 0.1);
    assert_float_equal(del(10,0), 0, 0.1);
}
void test_plmi(void **state) {
    assert_true(plmi(5));
    assert_false(plmi(-3));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_plus),
        cmocka_unit_test(test_min),
        cmocka_unit_test(test_ymn),
        cmocka_unit_test(test_del),
        cmocka_unit_test(test_plmi),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
