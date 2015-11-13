/* main.c  -  Foundation error test  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform foundation library in C11 providing basic support
 * data types and functions to write applications and games in a platform-independent fashion.
 * The latest source code is always available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without
 * any restrictions.
 */

#include <foundation/foundation.h>
#include <test/test.h>

static application_t
test_error_application(void) {
	application_t app;
	memset(&app, 0, sizeof(app));
	app.name = string_const(STRING_CONST("Foundation error tests"));
	app.short_name = string_const(STRING_CONST("test_error"));
	app.config_dir = string_const(STRING_CONST("test_error"));
	app.flags = APPLICATION_UTILITY;
	app.dump_callback = test_crash_handler;
	return app;
}

static memory_system_t
test_error_memory_system(void) {
	return memory_system_malloc();
}

static foundation_config_t
test_error_config(void) {
	foundation_config_t config;
	memset(&config, 0, sizeof(config));
	return config;
}

static int
test_error_initialize(void) {
	return 0;
}

static void
test_error_finalize(void) {
}

DECLARE_TEST(error, error) {
	EXPECT_EQ(error(), ERROR_NONE);
	EXPECT_EQ(error(), ERROR_NONE);

	error_report(ERRORLEVEL_WARNING, ERROR_ACCESS_DENIED);
	EXPECT_EQ(error(), ERROR_ACCESS_DENIED);
	EXPECT_EQ(error(), ERROR_NONE);

	error_report(ERRORLEVEL_ERROR, ERROR_INVALID_VALUE);
	EXPECT_EQ(error(), ERROR_INVALID_VALUE);
	EXPECT_EQ(error(), ERROR_NONE);

	return 0;
}

DECLARE_TEST(error, context) {
	error_context_t* context = 0;

	context = error_context();
	if (context)
		EXPECT_EQ(context->depth, 0);

	error_context_push(STRING_CONST("error test"), STRING_CONST("data"));
	context = error_context();

#if BUILD_ENABLE_ERROR_CONTEXT
	EXPECT_NE(context, 0);
	EXPECT_EQ(context->depth, 1);
	EXPECT_CONSTSTRINGEQ(context->frame[0].name, string_const(STRING_CONST("error test")));
	EXPECT_CONSTSTRINGEQ(context->frame[0].data, string_const(STRING_CONST("data")));
#else
	EXPECT_EQ(context, 0);
#endif

	error_context_pop();
	context = error_context();

#if BUILD_ENABLE_ERROR_CONTEXT
	EXPECT_NE(context, 0);
	EXPECT_EQ(context->depth, 0);
#else
	EXPECT_EQ(context, 0);
#endif

	error_context_push(STRING_CONST("error test"), STRING_CONST("data"));
	error_context_push(STRING_CONST("another test"), STRING_CONST("more data"));
	context = error_context();

#if BUILD_ENABLE_ERROR_CONTEXT
	EXPECT_NE(context, 0);
	EXPECT_EQ(context->depth, 2);
	EXPECT_CONSTSTRINGEQ(context->frame[0].name, string_const(STRING_CONST("error test")));
	EXPECT_CONSTSTRINGEQ(context->frame[0].data, string_const(STRING_CONST("data")));
	EXPECT_CONSTSTRINGEQ(context->frame[1].name, string_const(STRING_CONST("another test")));
	EXPECT_CONSTSTRINGEQ(context->frame[1].data, string_const(STRING_CONST("more data")));
#else
	EXPECT_EQ(context, 0);
#endif

	error_context_pop();
	context = error_context();

#if BUILD_ENABLE_ERROR_CONTEXT
	EXPECT_NE(context, 0);
	EXPECT_EQ(context->depth, 1);
	EXPECT_CONSTSTRINGEQ(context->frame[0].name, string_const(STRING_CONST("error test")));
	EXPECT_CONSTSTRINGEQ(context->frame[0].data, string_const(STRING_CONST("data")));
#else
	EXPECT_EQ(context, 0);
#endif

	error_context_pop();

	return 0;
}

static void*
error_test_thread(void) {
	error_context_t* context = 0;

	EXPECT_EQ(error(), ERROR_NONE);
	EXPECT_EQ(error(), ERROR_NONE);

	error_report(ERRORLEVEL_WARNING, ERROR_ACCESS_DENIED);
	EXPECT_EQ(error(), ERROR_ACCESS_DENIED);
	EXPECT_EQ(error(), ERROR_NONE);

	error_report(ERRORLEVEL_ERROR, ERROR_INVALID_VALUE);
	EXPECT_EQ(error(), ERROR_INVALID_VALUE);
	EXPECT_EQ(error(), ERROR_NONE);

	context = error_context();
	if (context)
		EXPECT_EQ(context->depth, 0);

	error_context_push(STRING_CONST("error test"), STRING_CONST("data"));
	context = error_context();

#if BUILD_ENABLE_ERROR_CONTEXT
	EXPECT_NE(context, 0);
	EXPECT_EQ(context->depth, 1);
	EXPECT_CONSTSTRINGEQ(context->frame[0].name, string_const(STRING_CONST("error test")));
	EXPECT_CONSTSTRINGEQ(context->frame[0].data, string_const(STRING_CONST("data")));
#else
	EXPECT_EQ(context, 0);
#endif

	error_context_pop();
	context = error_context();

#if BUILD_ENABLE_ERROR_CONTEXT
	EXPECT_NE(context, 0);
	EXPECT_EQ(context->depth, 0);
#else
	EXPECT_EQ(context, 0);
#endif

	error_context_push(STRING_CONST("error test"), STRING_CONST("data"));
	error_context_push(STRING_CONST("another test"), STRING_CONST("more data"));
	context = error_context();

#if BUILD_ENABLE_ERROR_CONTEXT
	EXPECT_NE(context, 0);
	EXPECT_EQ(context->depth, 2);
	EXPECT_CONSTSTRINGEQ(context->frame[0].name, string_const(STRING_CONST("error test")));
	EXPECT_CONSTSTRINGEQ(context->frame[0].data, string_const(STRING_CONST("data")));
	EXPECT_CONSTSTRINGEQ(context->frame[1].name, string_const(STRING_CONST("another test")));
	EXPECT_CONSTSTRINGEQ(context->frame[1].data, string_const(STRING_CONST("more data")));
#else
	EXPECT_EQ(context, 0);
#endif

	error_context_pop();
	context = error_context();

#if BUILD_ENABLE_ERROR_CONTEXT
	EXPECT_NE(context, 0);
	EXPECT_EQ(context->depth, 1);
	EXPECT_CONSTSTRINGEQ(context->frame[0].name, string_const(STRING_CONST("error test")));
	EXPECT_CONSTSTRINGEQ(context->frame[0].data, string_const(STRING_CONST("data")));
#else
	EXPECT_EQ(context, 0);
#endif

	error_context_pop();

	return 0;
}

static void*
error_thread(void* arg) {
	int ipass = 0;
	FOUNDATION_UNUSED(arg);

	thread_sleep(10);

	for (ipass = 0; ipass < 512; ++ipass) {
		if (error_test_thread())
			return FAILED_TEST;
		thread_yield();
	}

	return 0;
}

DECLARE_TEST(error, thread) {
	//Launch 32 threads
	thread_t thread[32];
	int i;

	for (i = 0; i < 32; ++i)
		thread_initialize(&thread[i], error_thread, 0, STRING_CONST("error"), THREAD_PRIORITY_NORMAL, 0);
	for (i = 0; i < 32; ++i)
		thread_start(&thread[i]);

	test_wait_for_threads_startup(thread, 32);
	test_wait_for_threads_finish(thread, 32);

	for (i = 0; i < 32; ++i) {
		EXPECT_EQ(thread[i].result, 0);
		thread_finalize(&thread[i]);
	}

	return 0;
}

static void
test_error_declare(void) {
	ADD_TEST(error, error);
	ADD_TEST(error, context);
	ADD_TEST(error, thread);
}

static test_suite_t test_error_suite = {
	test_error_application,
	test_error_memory_system,
	test_error_config,
	test_error_declare,
	test_error_initialize,
	test_error_finalize
};

#if BUILD_MONOLITHIC

int
test_error_run(void);

int
test_error_run(void) {
	test_suite = test_error_suite;
	return test_run_all();
}

#else

test_suite_t
test_suite_define(void);

test_suite_t
test_suite_define(void) {
	return test_error_suite;
}

#endif
