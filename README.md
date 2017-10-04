# data_type_and_data_structur



/*
bool notInEx(int *lot, int v, int l){
    for(int i = 0; i < l; i++)
        if(v == lot[i]) return false;
    return true;
}
 
*/
 
int det(int **&meas, int &size, int *lot, int l){
	//int lot[size];
    int r = 0;
    int s = 1;
    for( int j = 0; j < size; ++j ){
        //if (notInEx(lot, j, l)){
            if(l == size - 1) return meas[l][j];
            else{
                lot[l] = j;
                r = r + s * meas[l][j] * det(meas, size, lot, l + 1);
                s = -s;
            }
        //}
    }
    return r;
}
