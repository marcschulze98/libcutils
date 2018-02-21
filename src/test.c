#include <cutils/cutils.h>
#include <stdio.h>

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
	printf("%ld\n", test->length);

	vector_remove(test, 0,free);
	printf("%ld\n", test->length);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 8;
	my_struct->b = 8;
	vector_insert(test, 2, my_struct);
	printf("%ld\n", test->length);

	my_struct = malloc(sizeof(*my_struct));
	my_struct->a = 8;
	my_struct->b = 8;

	find = vector_find(test, my_struct, cmp_str);
	printf("pos: %lu\n", *find);
	free(find);

	free(my_struct);
	my_struct = vector_pop(test);
	printf("struct a: %d, b: %d\n", my_struct->a, my_struct->b);
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
	printf("%ld\n", test->length);

	cstring = to_cstring(test);
	printf("%s\n", cstring);
	free(cstring);

	string_remove(test, 3);
	cstring = to_cstring(test);
	printf("%s\n", cstring);
	free(cstring);
	printf("%ld\n", test->length);

	string_insert(test, 0,'a');
	cstring = to_cstring(test);
	printf("%s\n", cstring);
	free(cstring);

	test2 = from_cstring("xyz");

	string_concat(test,test2);
	cstring = to_cstring(test);
	printf("%s\n", cstring);
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
