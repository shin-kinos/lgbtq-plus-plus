
#include <algorithm> /* For sort() */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Settings {

	public:
		Settings();
		int         difficulty;
		string      unit_select;
		vector<int> unit_list;
		void        setDifficulty();
		int         getDifficulty();
		void        setUnitList();
		void        sortAndUniq();
		vector<int> getUnitList();

};

Settings::Settings() {

	//difficulty = 1;
	//unit_list = { 1 };

	//cout << difficulty << endl;

}

void Settings::setDifficulty() {

	cout << "\n出題リストを設定して下さい (半角数字 1, 2 or 3).\n" << endl;
	cout << "1. 高校生物・最重要用語 (改訂)" << endl;
	cout << "2. 高校生物・重要用語 (改訂)" << endl;
	cout << "3. 「高校生物・最重要用語 (改訂)」と「高校生物・重要用語 (改訂)」の両方" << endl;
	cout << ": ";

	//cin >> difficulty;

	for ( cin >> difficulty; !cin || !( difficulty >= 1 && difficulty <= 3 ) ; cin >> difficulty ) {

		cin.clear();
		cin.ignore();
		cout << "入力が間違っています. もう一度入力してください." << endl;
		cout << ": ";

	}

	//cout << " You entered: " << difficulty;

}

int Settings::getDifficulty() {

	return difficulty;

}

void Settings::setUnitList() {

	cout << ": ";

	char delimiter = ',';
	cin >> unit_select;
	string unit_num;
	stringstream sstream( unit_select );
	while ( getline( sstream, unit_num, delimiter ) ) {
		//cout << isdigit( stoi( unit_num ) ) << endl;

		try {
			//cout << stoi( unit_num ) << endl;
			unit_list.push_back( stoi( unit_num ) );
		}
		catch ( invalid_argument /* err */ ) {
			cout << unit_num << " <- 不適切な入力です. この入力は無視されます." << endl;
			//cout << err.what() << endl;
		}
		catch ( out_of_range /* err */ ) {
			cout << unit_num << " <- 範囲外の入力です. この入力は無視されます." << endl;
		}
		catch ( ... ) {
			cerr << "Unknown exeption" << endl;
			//cout << err.what() << endl;
		}
	}

	unit_list.shrink_to_fit();
	for ( auto iter = unit_list.begin(); iter != unit_list.end(); ) {
		if ( *iter < 0 || *iter > 33 ) {
			cout << *iter << " <- 範囲外の入力です. この入力は無視されます." << endl;
			iter = unit_list.erase( iter );
		} else {
			++iter;
		}
	}

	/*
	for ( const auto& element : unit_list ) {
		cout << element << endl;
	}
	*/

	unit_list.shrink_to_fit();

	if ( unit_list.empty() ) {
		cout << "\n!!! 警告 !!!" << endl;
		cout << "出題範囲がEmptyとなった為, '0 (全ての単元)' が選択されました." << endl;
		unit_list.push_back( 0 );
		//return unit_list;
	} else {
		//return unit_list;
	}

}

void Settings::sortAndUniq() {

	/* Sort and remove duplication the unit list. */
	sort( unit_list.begin(), unit_list.end() );
	unit_list.erase( unique( unit_list.begin(), unit_list.end() ), unit_list.end() );

	if ( unit_list.size() != 1 && unit_list[ 0 ] == 0 ) {
		cout << "!!! 警告 !!!" << endl;
		cout << "選択された出題範囲に '0 (全ての単元)' が含まれるため, 他の全ての引数は無視されます." << endl;
		unit_list.clear();
		unit_list.shrink_to_fit();
		unit_list.push_back( 0 );
	}

	//for ( const auto& element : unit_list ) cout << element << endl;

}

vector<int> Settings::getUnitList() {

	return unit_list;

}
