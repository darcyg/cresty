check_PROGRAMS = test_dict test_request

test_dict_SOURCES = test_dict.c
test_request_SOURCES = test_request.c

TESTS = test_dict test_request

LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/build-aux/tap-driver.sh
