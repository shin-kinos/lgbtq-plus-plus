
#include <algorithm> /* For sort(), random_shuffle(), sample() */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <unistd.h> /* For sleep(). */

#define MARGIN 500000
#define NUM_CHOICE 12

using namespace std;

class Question : public File
{
	public:
		//Question();
		vector<int>    q_number;
		vector<string> q_level;
		vector<string> q_unit_name;
		vector<int>    q_unit_number;
		vector<string> q_word_jp;
		vector<string> q_word_en;
		vector<int>    q_number_random;
		vector<int>    your_answers_index;
		//int            correct_num;
		void           pickUpLevel( int difficulty );
		void           makeQuestionList( const vector<int>& unit_list );
		void           showQuestionList();
		void           randomizeQlist();
		void           doQuiz();

};

/*
Question::Question() {
}
*/

void Question::pickUpLevel( int difficulty ) {

	string level_index;
	//cout << "difficulty : " << difficulty << endl;
	if      ( difficulty == 1 ) level_index = "applied";
	else if ( difficulty == 2 ) level_index = "basic";
	else if ( difficulty == 3 ) level_index = "all";
	//cout << "level_index : " << level_index << endl;

	int length = number.size();
	for ( int i = 0; i < length; i++ ) {
		//cout << level[ i ] << endl;
		if ( level_index != level[ i ] ) {
			//cout << "matched !" << endl;
			q_number.push_back( number[ i ]           );
			q_level.push_back( level[ i ]             );
			q_unit_name.push_back( unit_name[ i ]     );
			q_unit_number.push_back( unit_number[ i ] );
			q_word_jp.push_back( word_jp[ i ]         );
			q_word_en.push_back( word_en[ i ]         );
		} //else cout << "did not matched." << endl;
	}

}

void Question::makeQuestionList( const vector<int>& unit_list ) {

	/* Let temporary data. */
	vector<int>    temp_q_number;
	vector<string> temp_q_level;
	vector<string> temp_q_unit_name;
	vector<int>    temp_q_unit_number;
	vector<string> temp_q_word_jp;
	vector<string> temp_q_word_en;

	int vec_len = q_number.size();
	for ( auto unit_list_index : unit_list ) {
		for ( int i = 0; i < vec_len; i++ ) {
			if ( unit_list_index == q_unit_number[ i ] ) {
				//cout << "Matched : " << unit_list_index << endl;
				temp_q_number.push_back( q_number[ i ]           );
				temp_q_level.push_back( q_level[ i ]             );
				temp_q_unit_name.push_back( q_unit_name[ i ]     );
				temp_q_unit_number.push_back( q_unit_number[ i ] );
				temp_q_word_jp.push_back( q_word_jp[ i ]         );
				temp_q_word_en.push_back( q_word_en[ i ]         );
			}
		}
	}

	/*
	int length = temp_q_number.size();
	for ( int i = 0; i < length; i++ ) {
		cout << temp_q_number[ i ]      << "\t";
		cout << temp_q_level[ i ]       << "\t";
		cout << temp_q_unit_name[ i ]   << "\t";
		cout << temp_q_unit_number[ i ] << "\t";
		cout << temp_q_word_jp[ i ]     << "\t";
		cout << temp_q_word_en[ i ]     << "\n";
	}
	*/

	q_number.clear();      q_number.shrink_to_fit();
	q_level.clear();       q_level.shrink_to_fit();
	q_unit_name.clear();   q_unit_name.shrink_to_fit();
	q_unit_number.clear(); q_unit_number.shrink_to_fit();
	q_word_jp.clear();     q_word_jp.shrink_to_fit();
	q_word_en.clear();     q_word_en.shrink_to_fit();

	q_number      = temp_q_number;
	q_level       = temp_q_level;
	q_unit_name   = temp_q_unit_name;
	q_unit_number = temp_q_unit_number;
	q_word_jp     = temp_q_word_jp;
	q_word_en     = temp_q_word_en;

	/* //////////////////////////////////////////////////////////

	vector<int> unit_remove_list;
	for ( int i = 0; i < 33; i++ ) {
		bool find = false;
		for ( auto unit_element : unit_list ) {
			if ( i == unit_element ) {
				find = true;
				break;
			}
		}
		if ( find == false ) unit_remove_list.push_back( i );
	}

	//for ( auto element : unit_remove_list ) cout << element << endl;

	int vec_len = q_number.size();
	int i       = 0;

	for( auto unit_remove_index : unit_remove_list ) {
		cout << unit_remove_index << endl;
		while ( i < vec_len ) {
			if ( unit_remove_index == q_unit_number[ i ] ) {
				q_number.erase( q_number.begin() +  i           );
				q_level.erase( q_level.begin() +  i             );
				q_unit_name.erase( q_unit_name.begin() +  i     );
				q_unit_number.erase( q_unit_number.begin() +  i );
				q_word_jp.erase( q_word_jp.begin() +  i         );
				q_word_en.erase( q_word_en.begin() +  i         );
				vec_len--;
			} else {
				i++;
			}

			i++;
		}
	}

	*/ //////////////////////////////////////////////////////////

}

void Question::showQuestionList() {

	int num_question = q_number.size();

	cout << "\033[2J";
	cout << "\n以下の単元で問題を出題します ( 全 " << num_question << " 問 ) :" << endl;

	/*
	int length = q_number.size();
	for ( int i = 0; i < length; i++ ) {
		cout << q_number[ i ]      << "\t";
		cout << q_level[ i ]       << "\t";
		cout << q_unit_name[ i ]   << "\t";
		cout << q_unit_number[ i ] << "\t";
		cout << q_word_jp[ i ]     << "\t";
		cout << q_word_en[ i ]     << "\n";
	}
	*/

	vector<string> temp_uniq_list = q_unit_name;
	/* Sort and remove duplication the vector. */
	sort( temp_uniq_list.begin(), temp_uniq_list.end() );
	temp_uniq_list.erase( unique( temp_uniq_list.begin(), temp_uniq_list.end() ), temp_uniq_list.end() );

	cout << "===========================================" << endl;
	for ( auto element : temp_uniq_list ) {
		cout << "* " << element << endl;
	}
	cout << "===========================================" << endl;

}

void Question::randomizeQlist() {

	random_device seed_gen;
	mt19937 engine( seed_gen() );

	q_number_random = q_number;
	shuffle( q_number_random.begin(), q_number_random.end(), engine );

	/*
	for ( auto element : q_number_random ) {
		cout << element << endl;
	}
	*/

}

//////////////////////////////////////////////////////////////////////////
// ↓↓↓↓↓↓ FUNCTIONS USED IN doQuiz() MEMBER FUNCTION ↓↓↓↓↓↓ //
//////////////////////////////////////////////////////////////////////////

vector<int> sample_choices( const vector<int>& number, int choice_num ) {

	vector<int> sample_result;

	//random_device seed_gen;
	//mt19937 engine( seed_gen() );

	sample(
		number.begin(),
		number.end(),
		back_inserter( sample_result ),
		choice_num,
		mt19937{ random_device{}() }
	);

	/*
	for ( auto element : sample_result ) {
		cout << element << endl;
	}
	*/

	return sample_result;

}

void show_question(
	const vector<string>& word_jp,
	const vector<string>& unit_name,
	const vector<int>&    choices,
	const vector<string>& word_en,
	int                   question_number,
	int                   index
) {
	cout << "\033[2J";
	cout << "問題 " << question_number << ". ";
	cout << "次の単語の英訳を答えよ." << endl;

	cout
	<< '\n'
	<< "=> "
	<< "\033[7m" /* Under line. */
	<< word_jp[ index ]
	<< "\033[0m" /* Clear */
	<< " ( 単元 : "
	<< unit_name[ index ]
	<< " )"
	<< '\n'
	<< endl;

	for ( int i = 0; i < choices.size(); i++ ) {
		int q_index = choices[ i ];
		cout << i + 1 << '\t' << word_en[ q_index ] << endl;
		/*
		if      ( i == 0 )              cout << '\t';
		if      ( i == 1 )              cout << '\n';
		else if ( i > 1 && i % 2 != 0 ) cout << '\t';
		else if ( i > 1 && i % 2 == 0 ) cout << '\n';
		*/
	}

}

int set_answer( const vector<int>& choices, int answer_num ) {

	/*
	cout << "answer_num : " << answer_num << endl;
	for ( auto element : choices ) {
		cout << element << endl;
	}
	*/

	cout << ": ";

	int answer_index;

	for ( cin >> answer_index; !cin || !( answer_index >= 1 && answer_index <= NUM_CHOICE ) ; cin >> answer_index ) {
	cin.clear();
	cin.ignore();
	cout
	<< "範囲外の入力です. もう一度入力してください."
	<< " ( 半角数字 1 - "
	<< NUM_CHOICE
	<< " )"
	<< endl;
	cout << ": ";
	}

	answer_index--;
	if ( answer_num == choices[ answer_index ] ) {
		cout << "\033[32m";
		cout << "\n正解 !!!\n" << endl;
	} else {
		cout << "\033[31m";
		cout << '\a';
		cout << "\n不正解 ! w\n" << endl;
	}
	cout << "\033[39m";

	usleep( MARGIN );

	return choices[ answer_index ];

}

//////////////////////////////////////////////////////////////////////////
// ↑↑↑↑↑↑ FUNCTIONS USED IN doQuiz() MEMBER FUNCTION ↑↑↑↑↑↑ //
//////////////////////////////////////////////////////////////////////////

void Question::doQuiz() {

	for ( int i = 0; i < q_number_random.size(); i++ ) {

		/* vector<int> for question choise list. */
		vector<int> choices;

		while ( 1 ) {
			choices  = sample_choices( number, NUM_CHOICE - 1 );
			auto found_itr = find( choices.begin(), choices.end(), q_number_random[ i ] );
			if ( found_itr != ( choices.end() ) ) { /* cout << "Duplication was observed.\nRandomize again." << endl; */ }
			else { break; }
		}

		choices.push_back( q_number_random[ i ] );

		//random_device seed_gen;
		//mt19937 engine( seed_gen() );
		shuffle( choices.begin(), choices.end(), mt19937{ random_device{}() } );

		/*
		for ( int j = 0; j < choices.size(); j++ ) {
			cout << choices[ j ] << endl;
		}
		*/

		show_question(
			word_jp,
			unit_name,
			choices,
			word_en,
			i + 1,
			q_number_random[ i ]
		);

		/* Note player's answers. */
		int answer_index = set_answer( choices, q_number_random[ i ] );
		your_answers_index.push_back( answer_index );

	}

	/*
	for ( auto element : your_answers_index ) {
		cout << element << '\t';
		cout << word_en[ element ] << endl;
	}
	*/

}
