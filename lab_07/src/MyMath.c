#include "MyMath.h"
#include "CONSTANT.h"


void swap(void* a, void* b, int size) {
	char* f = a;
	char* g = b;
	for ( int i = 0; i < size; ++i ) {
		char tmp;

		tmp = *f;
		*f = *g;
		*g = tmp;

		f++;
		g++;
	}
}


int compare_int_and_ch (const void * first_item, const void * second_item) {
	return ( *(char*)second_item - *(char*)first_item );
}

int compare_double (const void * first_item, const void * second_item) {
	printf("%d\n", *(double*)first_item > *(double*)second_item);
	return (*(double*)first_item > *(double*)second_item) ? 1 : (*(double*)first_item < *(double*)second_item) ? -1:0 ;
  /*
	if (*(double*)first_item > *(double*)second_item) {
	  return 1;
  } else if (*(double*)first_item < *(double*)second_item) {
	  return -1;
  } else {
	  return 0;
  }
  */
}

void BubbleSort(void* basic, int count, int size, int(*comp)(const void*,const void*)) {
	char* a = basic;
	char* pa = (char*)basic;
	char* pb = (char*)basic + count*size;
	for ( ; pa < pb; pa += size ) {
		char* pc = (char*)basic;
		for ( ; pc < pb - size - ((pa - a)/size); pc += size ) {
			char* temp = pc;
			if ( comp(temp, pc+size) < 0 ) {
				//printf("abc%f\n", temp);
				printf("[dbg]%d\n", size);
				swap(temp,(pc+size), size);
			}
		}
	}
}
