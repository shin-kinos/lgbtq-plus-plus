
#include <algorithm> /* For max_element() */
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> str_split( const string& row, const char delimiter ) {

	string         col;
	vector<string> col_list;

	istringstream iss( row );
	while ( getline( iss, col, delimiter ) ) col_list.push_back( col );

	/*
	for ( int i = 0; i < col_list.size(); i++ ) {
		cout << col_list[ i ] << endl;
	}
	*/

	col_list.shrink_to_fit();
	return col_list;
}

class File {

	public :
		vector<int>    number;
		vector<string> level;
		vector<string> unit_name;
		vector<int>    unit_number;
		vector<string> word_jp;
		vector<string> word_en;
		void getFileData();
		void showData();
		void showUnitList();

};

void File::getFileData() {
	
	ifstream file_input( "./bio-word-list.data" );
	if ( !file_input ) {
		cout << "出題リストの読み込みに失敗しました." << endl;
		cout << "プログラムを中断します." << endl;

		exit( 1 );
	}

	string row;
	while ( getline( file_input, row ) ) {
		//cout << "#\t" << row << endl;
		if ( *row.begin() != '#' ) {

			vector<string> col_list = str_split( row, ',' );

			for ( int i = 0; i < col_list.size(); i++ ) {
				//cout << i << " # " << col_list[ i ] << endl;
				try {
					if      ( i == 0 ) number.push_back( stoi( col_list[ i ] )      );
					else if ( i == 1 ) level.push_back( col_list[ i ]               );
					else if ( i == 2 ) unit_name.push_back( col_list[ i ]           );
					else if ( i == 3 ) unit_number.push_back( stoi( col_list[ i ] ) );
					else if ( i == 4 ) word_jp.push_back( col_list[ i ]             );
					else if ( i == 5 ) word_en.push_back( col_list[ i ]             );
				}
				catch ( invalid_argument  error ) {
					cout << error.what() << endl;
				}
				catch ( out_of_range error ) {
					cout << error.what() << endl;
				}
				catch ( ... ) {
					cerr << "Unknown exeption" << endl;
				}
			}
		}
	}

	file_input.close();

}

void File::showData() {

	for ( int i = 0; i < ( number ).size(); i++ ) {
		cout << number[ i ]      << "\t";
		cout << level[ i ]       << "\t";
		cout << unit_name[ i ]   << "\t";
		cout << unit_number[ i ] << "\t";
		cout << word_jp[ i ]     << "\t";
		cout << word_en[ i ]     << "\n";
	}

}

void File::showUnitList() {

	cout << "\n出題範囲を設定して下さい (半角数字 0 - 32, 複数選択可). " << endl;
	cout << "例 : 1,2,3,12,15,28,9" << endl;

	int unit_num_max = *max_element( begin( unit_number ), end( unit_number ) );
	//cout << "The number of unit : " << unit_num_max << endl;

	vector<int> unit_num_idx;
	for ( int i = 1; i <= unit_num_max; i++ ) unit_num_idx.push_back( i );
	//for ( const auto& i : unit_num_idx ) cout << i << endl;

	cout << "\n" << "0\t#\t" << "全ての単元" << endl;
	for ( const auto& i : unit_num_idx ) {
		for ( int j = 0; j < unit_number.size(); j++ ) {
			if ( i == unit_number[ j ] ) {
				cout << i << "\t#\t" << unit_name[ j ] << endl;
				break;
			}
		}
	}

}