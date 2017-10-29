#include "MyINT.h"
#include "MyDOUBLE.h"

istream& operator>> (istream &stream, MyDOUBLE &number) {
	bool flag_sign = false;
	int *item = NULL, *point = NULL;
	char symbol;
    stream.get(symbol);

    if( symbol == '\n' )
        return stream >> number;

    while( tolower(symbol) != 'e' && symbol != '\n' ) {//&& ((item - &number.data[0]) < MAX_COUNT) ) {
        if( !isdigit(symbol) ) {
            if ( (symbol == '+' || symbol == '-') && !item && !flag_sign ) {
                number.sign = (symbol == '-') ? true : false;
                flag_sign = true;
            } else if (symbol == '.' and !point ) {
               point = (!item) ? &number.data[0] : item;
            } else if ( !isspace(symbol) ) {
                cout << "Error Input(DOUBLE)";
                while( symbol != '\n' )
                    stream.get(symbol);
                number.error_input = ERROR_INPUT_DOUBLE;
                return stream;
            }
        } else {
            if( !item ) {
                item = &number.data[0];
            }
            *item = symbol - 48;
            item++;
            number.count++;
        }
        stream.get(symbol);
    }

    int sum = 0;
    for(int i = 0; i < number.count; i++) {
    	sum += number.data[i];
    }
    if ( !sum ) {
    	cout << "Error division by zero";
		number.error_input = DIVISION_BY_ZERO;
		return stream;
    }
    if ( tolower(symbol) == 'e' ) {
    	stream.get(symbol);
    	int zn = 1;
    	while ( symbol != '\n' ) {
    		bool new_flag = false;
    		//cout << symbol;
    		if( !isdigit(symbol) ) {
    			if ( (symbol == '+' || symbol == '-') && !new_flag ) {
    				zn *= (symbol == '-') ? -1 : 1;
					new_flag = true;
    			}
    			else {
    				cout << "Error Input(ERROR input exp)";
					while( symbol != '\n' )
						stream.get(symbol);
					number.error_input = ERROR_INPUT_DOUBLE;
					return stream;
    			}
    		} else {
    			number.exp = number.exp*10 +((int)symbol-(int)'0');
    		}
    		stream.get(symbol);
    	}
    	//cout << number.exp << ' ';
    	number.exp *= zn;
    	//cout << number.exp;
    }
    //cout << number.exp;
    if( (abs(number.exp) > MAX_EXP) ) {
        cout << "Error Input(exp > 99999)";
        number.error_input = ERROR_INPUT_DOUBLE;
        return stream;
    }
    if( !item && symbol == '\n' )
        return stream >> number;

    if( !point )
        point = item;

    number.exp -= (item - point);

    reverse(&number.data[0], &number.data[number.count]);

    int i = number.count - 1;
    while(i > 0 && !number.data[i] ) {
        i--;
        number.count--;
    }

    return stream;
}

ostream& operator<<(ostream &stream, const MyDOUBLE &obj) {
	MyDOUBLE obj_copy = MyDOUBLE(obj);
    stream << ((obj_copy.sign) ? "-" : "") << "0.";
    for(int i = obj_copy.count - 1; i >= 0 && i >= (obj_copy.count - 31); i--)
        stream << obj_copy.data[i];
    stream << " E " << obj_copy.exp << endl;

    return stream;
}

void updateAsDividend(MyDOUBLE &b) {
	//cout << b.count << ' ' << b.data.size() << endl;
	b.data.resize(50+b.count, 0);
    for(int i = 0; i < b.count; i++) {
        b.data[i+50] = b.data[i];
    //    cout << i << ' ' << b.data[i+50] << endl;
    }
    for(int i = 0; i < 50; i++) {
        b.data[i] = 0;
    }
    //cout << b << endl;
    b.count += 50;
    b.exp -= 50;
    //cout << b.count << ' ' << b.data.size() << endl;
    //cout << b;
}

void extend(MyDOUBLE &b) {
	//cout << 'a' << b.data.size() << endl;
    for (int i = b.count; i >= 1; i--)
        b.data[i] = b.data[i-1];
    b.data[0] = 0;
    if (b.data[b.count])
        b.count++;
    //cout << 'b' << b.data.size() << endl;
}

void normalize(MyDOUBLE &b) {
    int i = 0;

    while(b.count > 0 && b.data[b.count-1] == 0) b.count--;
    b.exp += b.count;
    while(b.data[i] == 0 && i < b.count)
        i++;
    for(int j = i; j < b.count; j++) {
        b.data[j - i] = b.data[j];
    }
    b.count -= i;
    if(b.count <= 0) b.count = 1;
    reverse(&b.data[0], &b.data[b.count]);
    //exp += i;
    if(b.exp < 0 && abs(b.exp) > MAX_EXP) {
        int sdwig = MAX_EXP - b.exp;
        if(sdwig <= 30) {
            for (i = 0; i < b.count; i++) {
                b.data[i + sdwig] = b.data[i];
            }
            for(i = 0; i < sdwig; ++i) {
                b.data[i] = 0;
            }
        }
        else {
            for(i = 0; i < MAX_COUNT; i++)
                b.data[i] = 0;
        }
        b.exp = -MAX_EXP;
        b.count = MAX_COUNT;
    }
    while(1) {
    	//cout << b.exp;
        if ( abs(b.exp) >= MAX_EXP) {
            cout << "Out of range\n";
            b.error_input = true;
            return;
        }
        vector<int> arr_help(100, 0);
        for (i = 0; i <= MAX_COUNT + 1; i++) {
            arr_help[i] = b.data[i];
        }
        i = MAX_COUNT - 1;
        arr_help[i] += (arr_help[MAX_COUNT] >= 5) ? 1 : 0;
        while (i > 0 && arr_help[i] > 9) {
            arr_help[i--] %= 10;
            arr_help[i] += 1;
        }
        if (i == 0 && arr_help[i] > 9) {
            extend(b);
            b.exp += 1;
        }
        else {
            if ( abs(b.exp) > MAX_EXP) {
                cout << "Out of range\n";
                b.error_input = ERROR_EXP;
                return;
            }
            for (i = 0; i < MAX_COUNT; i++) {
                b.data[i] = arr_help[i];
            }
            b.count = MAX_COUNT;
            break;
        }

    }
    reverse(&b.data[0], &b.data[b.count]);
}

void MyINT_to_MyDOUBLE(MyDOUBLE &result, const MyINT obj) {
	result.count = obj.count;
    for(int i = 0; i < MAX_COUNT; ++i)
        result.data[i] = obj.data[i];
    result.exp = 0;
    result.error_input = obj.error_input;
    result.sign = obj.sign;
}

void BigDouble(MyDOUBLE &b, MyDOUBLE obj) {
	b.count = obj.count;
	for(int i = 0; i < MAX_LEN; ++i)
		b.data[i] = obj.data[i];
	b.exp = obj.exp;
	b.error_input = obj.error_input;
	b.sign = obj.sign;
}

MyDOUBLE operator*(const MyDOUBLE &a, const int b) {
	MyDOUBLE res;
    res.count = a.count;
    int r = 0;
    for (int i = 0; i < res.count || r; i++)
    {
        res.data[i] = a.data[i] * b + r;
        r = res.data[i] / 10;
        res.data[i] -= r * 10;
    }
    while (res.data[res.count])
        res.count++;
    return res;
}

bool operator <=(const MyDOUBLE & a, const MyDOUBLE & b) {
    if (a.count != b.count)
        return a.count < b.count;
    for (int i = a.count - 1; i >= 0; i--)
    {
        if (a.data[i] != b.data[i])
            return a.data[i] < b.data[i];
    }
    return true;
}

MyDOUBLE operator-(const MyDOUBLE &a, const MyDOUBLE &b) {
	MyDOUBLE res = a;
    for (int i = 0; i < res.count; i++) {
        res.data[i] -= b.data[i];
        if (res.data[i] < 0) {
            res.data[i] += 10;
            res.data[i + 1]--;
        }
    }
    int pos = res.count-1;
    while (pos && !res.data[pos])
        pos--;
    res.count = pos + 1;
    return res;
}

MyDOUBLE operator/(const MyINT &a, const MyDOUBLE &b) {
	//cout << "you are here /" << endl;
	MyDOUBLE res;
	MyDOUBLE tmp;
	MyDOUBLE a_copy;
	MyINT_to_MyDOUBLE(a_copy, a);
	//cout << a_copy << endl;
	reverse(&a_copy.data[0], &a_copy.data[a_copy.count]);
	updateAsDividend(a_copy);
	//cout << "you here";

	res.data.resize(a_copy.count, 0);

	tmp.count = 1;
    for (int i = a_copy.count - 1; i >= 0; i--) {
        extend(tmp);
        tmp.data[0] = a_copy.data[i];
        //cout << "you here";
        int x = 0;
        int l = 0, r = 9;

        while (l <= r)
        {
            int m = (l + r) >> 1;
            MyDOUBLE cur;
            //cout << "you here then";
            cur = (b*m);
            //cout << "you here now";
            if (cur <= tmp)
            {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        res.data[i] = x;
        MyDOUBLE mul;
        mul = (b*x);
        tmp = (tmp-mul);
    }

    res.count = a_copy.count;
    res.exp = a_copy.exp - b.exp;
    res.sign = (a_copy.sign + b.sign)%2;

    normalize(res);

    return res;
}
