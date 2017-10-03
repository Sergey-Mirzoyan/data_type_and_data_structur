#ifndef __MyMath__H__
#define __MyMath__H__

void swap(void* a, void* b, int size);
int compare_int_and_ch (const void * first_item, const void * second_item);
int compare_double(const void * first_item, const void * second_item);
void BubbleSort(void* basic, int count, int size, int(*comp)(const void*,const void*));

#endif //__MyMath__H__
