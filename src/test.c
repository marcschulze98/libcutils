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

static void test_vector(void)
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

static void test_string(void)
{
	String* string;
	String* string2;
	char* cstring;
	size_t tmp;
	int truth;
	Vector* vec;

	for(truth = false; truth == false || truth == true; truth++)
	{
		string = new_string(truth);

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
		string2 = from_cstring("xyz", truth);

		string_concat(string,string2);
		cstring = to_cstring(string);
		assert(strcmp(cstring, "aabcxyz") == 0);
		free(cstring);

		delete_string(string2);
		delete_string(string);

		string = from_cstring("abababcd", truth);
		string2 = from_cstring("ababcd", truth);
		assert(string_find_str(string, string2, &tmp));
		assert(tmp == 2);
		delete_string(string2);
		delete_string(string);

		string = from_cstring("abab", truth);
		string2 = from_cstring("abc", truth);
		assert(!string_find_str(string, string2, &tmp));
		delete_string(string2);
		delete_string(string);

		string = from_cstring("abababcd", truth);
		string2 = from_cstring("ab", truth);
		assert(string_find_str(string, string2, &tmp));
		assert(tmp == 0);
		delete_string(string2);
		delete_string(string);

		string = from_cstring("ABC ABCDAB ABCDABCDABDE", truth);
		string2 = from_cstring("ABCDABD", truth);
		assert(string_find_str(string, string2, &tmp));
		assert(tmp == 15);
		delete_string(string2);
		delete_string(string);

		string = from_cstring("asdasdasdasdp", truth);
		string2 = from_cstring("p", truth);
		assert(string_find_str(string, string2, &tmp));
		assert(tmp == 12);
		delete_string(string2);
		delete_string(string);

		string = from_cstring("asdpsdasdasdpa", truth);
		string2 = from_cstring("pa", truth);
		assert(string_find_str(string, string2, &tmp));
		assert(tmp == 12);
		delete_string(string2);
		delete_string(string);

		string = from_cstring("abcd", truth);
		assert(string->length == 4);
		string_remove_range(string, 0, string->length);
		assert(string->length == 0);
		delete_string(string);

		string = from_cstring("bba", truth);
		string_strip(string, 'a');
		assert(string->length == 2);

		cstring = to_cstring_del(string);
		free(cstring);


		string = from_cstring("asdyx782", truth);
		string2 = from_cstring("asdyx782", truth);
		assert(string_cmp(string, string2) == 0);
		delete_string(string2);
		delete_string(string);
	}

	string = from_cstring("asdyx782", true);
	string_push(string, 'a');
	string_remove(string, 2);
	assert(strcmp(string->chars, "asyx782a") == 0);
	string_remove_range(string, 1, 7);
	assert(strcmp(string->chars, "a") == 0);
	assert(string_pop(string) == 'a');
	string2 = from_cstring("asdasdas", false);
	string_concat(string, string2);
	assert(strcmp(string->chars, "asdasdas") == 0);

	delete_string(string2);
	string2 = from_cstring("koasä_ #", true);
	string_move(string, string2);
	assert(strcmp(string->chars, "koasä_ #") == 0);

	delete_string(string);

	string = from_cstring_reuse("asdasdas1", strlen("asdasdas1"), false);
	string2 = from_cstring_reuse("asdasdas", strlen("asdasdas"), false);
	assert(string_cmp(string, string2) > 0);
	free(string);
	free(string2);

	string = from_cstring(" -hi1 hi2 hello3  ;  hi4!-!hi5- ", false);
	vec = string_split(string, " ;-", true);
	assert(vec->length == 5);
	assert(string_cmp_cstr(vector_at(vec,0), "hi1") == 0);
	assert(string_cmp_cstr(vector_at(vec,1), "hi2") == 0);
	assert(string_cmp_cstr(vector_at(vec,2), "hello3") == 0);
	assert(string_cmp_cstr(vector_at(vec,3), "hi4!") == 0);
	assert(string_cmp_cstr(vector_at(vec,4), "!hi5") == 0);

	delete_string(string);
	delete_vector(vec, delete_string);

}

static void test_bytearray(void)
{
	Bytearray* bt;
	char* tmpchar;

	bt = new_bytearray(1);
	bytearray_push(bt, "a");
	bytearray_push(bt, "b");
	bytearray_push(bt, "c");
	bytearray_push(bt, "d");
	bytearray_push(bt, "\0");

	assert(strcmp((char*)bt->items, "abcd") == 0);

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

	bytearray_push(bt, "a");
	tmpchar = bytearray_pop(bt, NULL);
	assert(*tmpchar == 'a');
	free(tmpchar);

	bytearray_push(bt, "a");
	bytearray_push(bt, "a");
	bytearray_push(bt, "a");
	assert(bt->length == 3);
	bytearray_remove_range(bt, 0, bt->length, NULL);
	assert(bt->length == 0);

	delete_bytearray(bt, NULL);
}
#if __STDC_VERSION__ >= 201112L
static void test_timespec(void)
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

	res = timespec_diff(&ts2, &ts1);
	assert(res.tv_sec == 10 && res.tv_nsec == 999999998);

	ts1.tv_sec = 0;
	ts1.tv_nsec = 999999999;
	ts2.tv_sec = 10;
	ts2.tv_nsec = 1;

	res = timespec_diff(&ts2, &ts1);
	assert(res.tv_sec == 9 && res.tv_nsec == 2);

	ts1.tv_sec = 0;
	ts1.tv_nsec = 1;
	ts2.tv_sec = 10;
	ts2.tv_nsec = 999999999;

	res = timespec_diff(&ts2, &ts1);
	assert(res.tv_sec == 10 && res.tv_nsec == 999999998);

	res = timespec_diff(&ts1, &ts2);
	assert(res.tv_sec == 0 && res.tv_nsec == 0);
}
#endif
static void test_ll(void)
{
	LinkedList* ll;
	struct test my_structa, my_structb, *my_structptr;
	int truth;
	my_structa.a = 5;
	my_structa.b = 5;
	my_structb.a = 7;
	my_structb.b = 7;

	for(truth = 0; truth<2; truth++)
	{
		ll = new_ll(truth,truth);

		ll_push(ll, &my_structa);
		my_structptr = ll_pop(ll);
		assert(my_structptr->a == 5 && my_structptr->b == 5);

		ll_push(ll, &my_structa);
		ll_push(ll, &my_structa);
		ll_push(ll, &my_structa);
		ll_push(ll, &my_structb);

		my_structptr = ll_at(ll, ll->length-1);
		assert(my_structptr->a == 7);

		ll_swap(ll, 0, ll->length-1);

		my_structptr = ll_at(ll, ll->length-1);
		assert(my_structptr->a == 5);


		ll_remove_range(ll, 0, ll->length-1, NULL);
		assert(ll->length == 1);

		delete_ll(ll, NULL);
	}
}

static void test_bitfuncs(void)
{
	byte tmp = 0;
	uintmax_t tmp2 = UINTMAX_MAX;

	setbit(tmp, 0);
	assert(tmp == 1);
	setbitc(tmp, 1, byte);
	assert(tmp == 3);
	setbit(tmp, 2);
	assert(tmp == 7);

	clearbit(tmp2, numbits(uintmax_t)-1);
	assert(tmp2 == UINTMAX_MAX/2);

	assert(getbit(tmp, 0) == 1);
	assert(getbit(tmp, 5) == 0);
}

int main(int argc, char** argv)
{
	/* memswap tests */
	int a = 5;
	int b = 2;
	Bytearray* bt;
	void* tmp =  malloc(sizeof(int));

	memswap(&a, &b, sizeof(int));
	assert(a == 2 && b == 5);
	#if __STDC_VERSION__ >= 199901L
	memqswap_stack(&a, &b, sizeof(int));
	assert(a == 5 && b == 2);
	memqswap(&a, &b, tmp, sizeof(int));
	assert(a == 2 && b == 5);
	#else
	memqswap(&a, &b, tmp, sizeof(int));
	assert(a == 5 && b == 2);
	#endif
	free(tmp);
	/* memswap tests */

	test_vector();
	test_string();
	test_bytearray();
	#if __STDC_VERSION__ >= 201112L
	test_timespec();
	#endif
	test_ll();
	test_bitfuncs();

	/* misc tests */
	sleep_ms(250);
	assert(cutil_strcasecmp("ASD", "aSd") == 0);
	assert(cutil_strcasecmp("BSD", "asd") > 0);
	assert(cutil_strcasecmp("ASD", "bsd") < 0);
	assert(cutil_strncasecmp("ASDn", "asd", 3) == 0);
	assert(cutil_strncasecmp("ASDn", "asd", 4) >0);


	assert(ipow(2,32) == 4294967296);
	assert(isqrt(123123) == 350);
	bt = primesieve(100000000);
	assert(*(uintmax_t*)bytearray_at(bt, 312312) == 4444697);

	delete_bytearray(bt, NULL);
	puts(endianess_strings[check_endianess()]);

	return 0;
}
/* TODO: split up test files */
