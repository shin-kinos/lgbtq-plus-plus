

#include <iostream>
#include <vector>

using namespace std;

vector<string> make_mark_list( 
const vector<int>& q_number_random,
const vector<int>& your_answers_index 
) {
	vector<string> mark_list;

	for ( int i = 0; i < your_answers_index.size(); i++ ) {
		int correct_answer_index = q_number_random[ i ];
		int your_answer_index    = your_answers_index[ i ];

		if ( correct_answer_index == your_answer_index ) mark_list.push_back( "\033[32m✔\033[39m" );
		else                                             mark_list.push_back( "\033[31m✖\033[39m" );
	}

	return mark_list;

}

void show_result(
	const vector<string>& word_jp,
	const vector<string>& word_en,
	const vector<int>&    q_number_random,
	const vector<int>&    your_answers_index,
	double                elapsed_time
) {

	cout << "\033[2J";
	cout << "\n結果発表 !!!\n" << endl;

	vector<string> mark_list = make_mark_list( q_number_random, your_answers_index );

	int num_correct = 0;
	for ( auto element : mark_list ) {
		if ( element == "\033[32m✔\033[39m" ) num_correct++;
	}

	cout << "正解数 : " << num_correct << " / " << mark_list.size();
	if ( num_correct == mark_list.size() ) {
		cout << " <= PERFECT !!!" << endl;
	} else if ( num_correct == 0 ) {
		cout << " <= LOL" << endl;
	} else {
		cout << '\n';
	}

	cout << "タイム : " << elapsed_time << " 秒" <<endl;


	cout << '\n';
	for ( int i = 0; i < q_number_random.size(); i++ ) {
		int correct_answer_index = q_number_random[ i ];
		int your_answer_index    = your_answers_index[ i ];

		cout << "問題 " << i + 1 << ". " << mark_list[ i ] << endl;
		cout << "=======================================" << endl;
		cout
		<< "単語 : " << word_jp[ correct_answer_index ] << '\n'
		<< "英訳 : " << word_en[ correct_answer_index ] << '\n'
		<< "解答 : " << word_en[ your_answer_index    ] << '\n';
		cout << "=======================================\n\n\n" << endl;
	}

}

void end_game() {

	cout << "\nEnter キーでゲームを終了します. : \n";

	getchar();
	getchar();

}
