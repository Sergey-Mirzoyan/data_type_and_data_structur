#include <stdio.h>
#include <errno.h>
#include "CONSTANT.h"

struct technical_book {
	char* industry;
	char* country;
	char* language;
	int publ_date;
};

struct fiction_book {
	char* genre;
};

union type_book {
	struct technical_book tech_book;
	struct fiction_book fict_book;
};

struct book_t {
	short index_book;
	char* author_name;
	char* name_book;
	char* publ_office;
	unsigned pages;
	short bool_type_book;
	union type_book t_book;

};
/*
int Input_Info_book(FILE *f, struct book_t book) {
	//printf("test11\n");
	char* item;
	if ( fgets(f, 120, item) ) {
		printf("%s %s\n", book.author_name, book.name_book);
	//if ( fscanf(f, "%s %s %s %d %d", book.author_name, book.name_book, book.publ_office, book.pages, book.bool_type_book) == 5 ) {
		printf("test12\n");
		/*
		if ( !book.bool_type_book ) {
			if ( !(fscanf("%s", book.t_book.fict_book.genre) == 1) ) {
				return -1;
			}
		} else {
			if ( !(fscanf(f, "%s %s %s %d", book.t_book.tech_book.industry, book.t_book.tech_book.country, book.t_book.tech_book.language, book.t_book.tech_book.publ_date) == 4) ) {
				return -1;
			}
		}

	}
	return 0;
}
*/

int main(void) {
	FILE* file = fopen("file.txt", "r");

	if ( !file ) {
		printf("%s", strerror(errno));
		return errno;
	}

	struct book_t books;//[40];
	printf("test\n");
	int i = 0;
	char *str;
	char *str1;
	//fread(file, sizeof(char*), 128, str);
	printf("%d\n", fscanf(file, "%d", &books.index_book));
	//printf("%s\n", str);
	//printf("%d\n", fscanf(file, "%s", str));
	//printf("%s\n", str);
	//printf("%d\n", fscanf(file, "%s", str1));
	//printf("%s\n", str1);
	//printf("%d\n", fscanf(file, "%s", str1));
	//printf("%d\n", fscanf(file, "%d %s %s %s %d %d",  &books.index_book, books.author_name, books.name_book, books.publ_office, &books.pages, &books.bool_type_book));
	/*
	while ( (fscanf(file, "%d %s %s %s %d %d",  &books[i].index_book, books[i].author_name, books[i].name_book, books[i].publ_office, &books[i].pages, &books[i].bool_type_book)) == 6 ) {
		if ( books[i].bool_type_book ) {
			if( !(fscanf(file, "%s %s %s %d", books[i].t_book.tech_book.industry, books[i].t_book.tech_book.country ,books[i].t_book.tech_book.language, &books[i].t_book.tech_book.publ_date)) == 4 ){
				break;//return -1;
			}
		} else {
			if( !(fscanf(file, "%s", books[i].t_book.fict_book.genre) == 1) ){
				break;//return -1;
			}
		}
		++i;
	}
	*/
	/*
	printf("test2 %d\n", i);
	for ( int j = 0; j < i; ++j ) {
		printf("%d %s %s %s %d %d", books[j].index_book, books[j].author_name, books[j].name_book, books[j].publ_office, books[j].pages, books[j].bool_type_book);
		if ( books[j].bool_type_book ) {
			printf(" %s %s %s %d", books[j].t_book.tech_book.industry, books[j].t_book.tech_book.country ,books[j].t_book.tech_book.language, books[j].t_book.tech_book.publ_date);
		} else {
			printf(" %s", books[j].t_book.fict_book.genre);
		}
	}
	*/
	return OK;
}
