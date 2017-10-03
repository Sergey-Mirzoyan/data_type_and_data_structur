#include "CONSTANT.h"
#include "Work_File.h"

int int_count_scan(FILE* f, int* count, const int filter) {
	int item, minus = 0;

	if ( fscanf(f, "%d", &item) != 1 )
		return ERROR_EMPTY_FILE;
	*count = 1;
	if ( item < 0 ) minus = *count;
	 while ( fscanf(f, "%d", &item) == 1 ) {
		 *count += 1;
		 if ( item < 0 && filter )
			 minus = *count;
	 }
	 if ( minus ) {
		 *count = minus;
	 } else {
		 (*count)--;
	 }

	return OK;
}

void scan_array(FILE* f, int* pa, int* pb) {
	int item;
	fseek(f, 0, SEEK_SET);
	while ( pa < pb && fscanf(f, "%d", &item) == 1 ) {
		*pa = item;
		pa++;
	}
}
