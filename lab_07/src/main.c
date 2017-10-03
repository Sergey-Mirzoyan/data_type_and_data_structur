#include <stdio.h>
#include <errno.h>
#include "CONSTANT.h"
#include "MyMath.h"
#include "Work_File.h"

void create_array_int(int **pa, const int count) {
	*pa = malloc(sizeof(*pa)*count);
}

int main(void) { //int argc, char** argv[]) {
	int rc = OK;

	char* argv[] = {".", "test.txt", "out.txt", 'f'};
	int argc = 4;

	int flag_filter = (argc < 4) ? 0 : 1;
	if ( argc != 3 && argc != 4 ) {
		printf("example.exe <name file> <name file> [f]\n");
		return rc;
	}
	FILE *f;
	if ( flag_filter ) {
		f = fopen(argv[2], "r");
	} else {
		f = fopen(argv[1], "r");
	}
	if (!f) {
		fprintf(stderr, "File %s not found! %s!\n", argv[1], strerror(errno));
		rc = ERROR_INPUT;
	}

	int count = 0;
	rc = int_count_scan(f, &count, flag_filter);

	if ( !rc ) {
		int* pa = NULL;
		create_array_int(&pa, count);
		int* pb = pa + count;

		scan_array(f, pa, pb);

		for ( int i = 0; i < count; ++i ) {
			printf("%d ", *(pa+i));
		}

		BubbleSort(pa, pb-pa, sizeof(*pa), compare_int_and_ch);

		for ( int i = 0; i < count; ++i ) {
			printf("%d ", *(pa+i));
		}
	free(pa);
	}

	fclose(f);

	/*
	double a = 2.5;
	double b = 1.5;
	int k = 1, g = 2;
	new_swap(8, a, b);
	printf("%f %f\n", a, b);
	*/
	/*
	double a[10] = {2.0, 2.5, -6.0, 1.1, 0.00003, 5, 8.1, 7.0, 9.0, 0.0};
	for ( int i = 0; i < 10; ++i ) {
		printf("%f ", a[i]);
	}
	printf("\n");
	//printf("%d\n", sizeof(a));
	BubbleSort(a, sizeof(a)/sizeof(a[0]), sizeof(a[0]), compare_double);
	for ( int i = 0; i < 10; ++i ) {
		printf("%f ", a[i]);
	}
	printf("\n");
	qsort(a, sizeof(a)/sizeof(a[0]), sizeof(a[0]), compare_double);
	for ( int i = 0; i < 10; ++i ) {
		printf("%f ", a[i]);
	}
	*/
	return rc;

		//char a[3] = "bda";
		//char a[10] = {'a', 'q', 'e', 'z', 'd', 'b', 'w', 'p', 'r', 'y'};
		//int a[10] = {2, 4, 6, 1, 3, 5, 8, 7, 9, 0};
		//BubbleSort(a, 3, sizeof(char), compare);
		//for (int i = 0; i < 2; ++i) {
		//	printf("%d\n", *pa);
		//}
		//printf("%d", *pb);

}
