#include "MyINT.h"

istream& operator>> (istream &stream, MyINT &number){
    int *item = NULL;
    char symbol;
    bool flag_sign = false;

    stream.get(symbol);
    if( symbol == '\n' )
        return stream >> number;

    while( symbol != '\n' && ((item - &number.data[0]) < MAX_COUNT) ) {
        if( !isdigit(symbol) ) {
            if ( (symbol == '+' || symbol == '-') && !item && !flag_sign ) {
                number.sign = (symbol == '-') ? true : false;
                flag_sign = true;
            } else if ( !isspace(symbol) ) {
            	cout << "Error Input(INT)";
                number.error_input = ERROR_INPUT_INT;
                while( symbol != '\n' )
                    stream.get(symbol);
                return stream;
            }
        } else {
            if(item == NULL) {
                item = &number.data[0];
            }
            *item = symbol - (int)'0'; // 48
            item++;
            number.count++;
        }
        stream.get(symbol);
    }

    if( !item && symbol == '\n' )
        return stream >> number;
    return stream;
}
