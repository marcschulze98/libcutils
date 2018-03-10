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
	Vector* vector;
	struct test* my_struct;

	my_struct = malloc(sizeof(*my_struct));
	vector = new_vector();

	my_struct->a = 5;
	my_struct->b = 5;
	vector_push(vector, my_struct);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 6;
	my_struct->b = 6;
	vector_push(vector, my_struct);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 7;
	my_struct->b = 7;
	vector_push(vector, my_struct);
	assert(vector->length == 3);

	vector_remove(vector, 0,free);
	assert(vector->length == 2);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 8;
	my_struct->b = 8;
	vector_insert(vector, 2, my_struct);
	assert(vector->length == 3);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 8;
	my_struct->b = 8;

	find = vector_find(vector, my_struct, cmp_str);

	assert(*find == 2);
	free(find);

	free(my_struct);
	my_struct = vector_pop(vector);
	assert(my_struct->a == 8 && my_struct->b == 8);
	free(my_struct);

	delete_vector(vector, free);
}

static void test2(void)
{
	String* string;
	String* string2;
	char* cstring;
	size_t* tmp;

	string = new_string();

	string_push(string, 'a');
	string_push(string, 'b');
	string_push(string, 'c');
	string_push(string, 'd');
	assert(string->length == 4);

	cstring = to_cstring(string);
	assert(strcmp(cstring, "abcd") == 0);
	free(cstring);

	string_remove(string, 3);
	cstring = to_cstring(string);
	assert(strcmp(cstring, "abc") == 0);
	free(cstring);
	assert(string->length == 3);

	string_insert(string, 0,'a');
	cstring = to_cstring(string);
	assert(strcmp(cstring, "aabc") == 0);
	free(cstring);

	string2 = from_cstring("xyz");

	string_concat(string,string2);
	cstring = to_cstring(string);
	assert(strcmp(cstring, "aabcxyz") == 0);
	free(cstring);

	delete_string(string2);
	delete_string(string);

	string = from_cstring("abcd");
	string2 = from_cstring("cd");
	tmp = string_find_str(string, string2);
	assert(*tmp == 2);
	free(tmp);

	delete_string(string2);
	delete_string(string);
}

static void test3(void)
{
	Bytearray* bt;
	char* tmpchar;

	bt = new_bytearray(1);
	bytearray_push(bt, "a");
	bytearray_push(bt, "b");
	bytearray_push(bt, "c");
	bytearray_push(bt, "d");
	bytearray_push(bt, "\0");

	assert(strcmp(bt->items, "abcd") == 0);

	tmpchar = bytearray_pop(bt, NULL);
	assert(*tmpchar == '\0');
	free(tmpchar);

	tmpchar = bytearray_pop(bt, NULL);
	assert(*tmpchar == 'd');
	free(tmpchar);

	tmpchar = bytearray_pop(bt, NULL);
	assert(*tmpchar == 'c');
	free(tmpchar);

	tmpchar = malloc(1);
	bytearray_pop(bt, tmpchar);
	assert(*tmpchar == 'b');

	bytearray_pop(bt, tmpchar);
	assert(*tmpchar == 'a');
	free(tmpchar);

	tmpchar = bytearray_pop(bt, NULL);
	assert(tmpchar == NULL);

	bytearray_push(bt, "a");
	tmpchar = bytearray_pop(bt, NULL);
	assert(*tmpchar == 'a');
	free(tmpchar);

	delete_bytearray(bt, NULL);
}
#if __STDC_VERSION__ >= 201112L
static void test4(void)
{
	struct timespec ts1 = {10, 10};
	struct timespec ts2 = {10, 10};
	struct timespec res;

	res = timespec_add(&ts1, &ts2);
	assert(res.tv_sec == 20 && res.tv_nsec == 20);

	ts1.tv_sec = 10;
	ts1.tv_nsec = 999999999;
	ts2.tv_sec = 0;
	ts2.tv_nsec = 1;

	res = timespec_add(&ts1, &ts2);
	assert(res.tv_sec == 11 && res.tv_nsec == 0);

	ts1.tv_sec = 0;
	ts1.tv_nsec = 1;
	ts2.tv_sec = 10;
	ts2.tv_nsec = 999999999;

	res = timespec_add(&ts1, &ts2);
	assert(res.tv_sec == 11 && res.tv_nsec == 0);

	ts1.tv_sec = 0;
	ts1.tv_nsec = 1;
	ts2.tv_sec = 10;
	ts2.tv_nsec = 999999999;

	res = timespec_diff(&ts1, &ts2);
	assert(res.tv_sec == 10 && res.tv_nsec == 999999998);

	ts1.tv_sec = 0;
	ts1.tv_nsec = 999999999;
	ts2.tv_sec = 10;
	ts2.tv_nsec = 1;

	res = timespec_diff(&ts1, &ts2);
	assert(res.tv_sec == 9 && res.tv_nsec == 2);

	ts1.tv_sec = 0;
	ts1.tv_nsec = 1;
	ts2.tv_sec = 10;
	ts2.tv_nsec = 999999999;

	res = timespec_diff(&ts1, &ts2);
	assert(res.tv_sec == 10 && res.tv_nsec == 999999998);
}
#endif

int main(int argc, char** argv)
{
	test1();
	test2();
	test3();
	#if __STDC_VERSION__ >= 201112L
	test4();
	#endif
	sleep_ms(1000);
	return 0;
}
