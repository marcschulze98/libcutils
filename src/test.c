#include <cutils/cutils.h>
#include <stdio.h>
#include <assert.h>

struct test
{
	int a;
	int b;
};

static int cmp_str(const void* str1, const void* str2)
{
	const struct test* str1_s = str1;
	const struct test* str2_s = str2;
	return !((str1_s->a == str2_s->a) && (str1_s->b == str2_s->b));
}

static void test1(void)
{
	size_t* find;
	Vector* test;
	struct test* my_struct;

	my_struct = malloc(sizeof(*my_struct));
	test = new_vector()

	my_struct->a = 5;
	my_struct->b = 5;
	vector_push(test, my_struct);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 6;
	my_struct->b = 6;
	vector_push(test, my_struct);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 7;
	my_struct->b = 7;
	vector_push(test, my_struct);
	assert(test->length == 3);

	vector_remove(test, 0,free);
	assert(test->length == 2);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 8;
	my_struct->b = 8;
	vector_insert(test, 2, my_struct);
	assert(test->length == 3);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 8;
	my_struct->b = 8;

	find = vector_find(test, my_struct, cmp_str);

	assert(*find == 2);
	free(find);

	free(my_struct);
	my_struct = vector_pop(test);
	assert(my_struct->a == 8 && my_struct->b == 8);
	free(my_struct);

	delete_vector(test,free);
}

static void test2(void)
{
	String* test;
	String* test2;
	char* cstring;

	test = new_string();

	string_push(test, 'a');
	string_push(test, 'b');
	string_push(test, 'c');
	string_push(test, 'd');
	assert(test->length == 4);

	cstring = to_cstring(test);
	assert(strcmp(cstring, "abcd") == 0);
	free(cstring);

	string_remove(test, 3);
	cstring = to_cstring(test);
	assert(strcmp(cstring, "abc") == 0);
	free(cstring);
	assert(test->length == 3);

	string_insert(test, 0,'a');
	cstring = to_cstring(test);
	assert(strcmp(cstring, "aabc") == 0);
	free(cstring);

	test2 = from_cstring("xyz");

	string_concat(test,test2);
	cstring = to_cstring(test);
	assert(strcmp(cstring, "aabcxyz") == 0);
	free(cstring);

	delete_string(test2);
	delete_string(test);
}

int main(int argc, char** argv)
{
	test1();
	test2();
	sleep_ms(1000);
	return 0;
}
